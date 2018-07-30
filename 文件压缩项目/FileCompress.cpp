#define _CRT_SECURE_NO_DEPRECATE 1

#ifndef __HUFFMAN_C0DE_CPP__
#define __HUFFMAN_CODE_CPP__
#include"FileCompress.h"

FileCompress::FileCompress()
{
	size_t size = sizeof(_info) / sizeof(_info[0]);
	for (int i = 0; i < size; ++i)
	{
		_info[i]._ch = i;
		_info[i]._count = 0;
	}
}

//++++++++++++++++ѹ���ļ�+++++++++++
void FileCompress::CompressHuffmanCode(const char* filename)
{
	assert(filename);
	//	1,���ļ���ͳ���ַ����ֵĴ���
	FILE* fout = fopen(filename, "rb");
	assert(fout);
	char ch = fgetc(fout);
	while (!feof(fout))
	{
		this->_info[(unsigned char)ch]._count++;
		ch = fgetc(fout);
	}

	//	2������Huffman��
	HuffmanTree<CharInfor> tree(this->_info, sizeof(this->_info)/sizeof(this->_info[0]),0);

	//	3������Huffman����
	string code;
	HuffmanNode<CharInfor>* root = tree.GetHuffmanNode();
	GenerateCode(root, *this, code);

	//	4������ѹ���ļ����������ļ���
	string fileInName = (string)filename;
	string configfilename = fileInName;
	size_t last = fileInName.find_last_of('.');
	if (last < fileInName.size())
	{
		fileInName.erase(last);
		configfilename.erase(last);
	}
	fileInName += ".huff";
	configfilename += ".config";

	string tmp;

	//	5�����������ļ�
	FILE* fconfig = fopen(configfilename.c_str(), "wb");
	char buff[20] = { 0 };
	for (int i = 0; i < sizeof(_info) / sizeof(_info[0]); ++i)
	{
		if (_info[i]._count > 0)
		{
			tmp += _info[i]._ch;
			tmp += ':';
			tmp += (string)_itoa(_info[i]._count, buff, 10);
			tmp += '\n';
			//fputs(tmp.c_str(), fconfig);
			fwrite(tmp.c_str(), 1, tmp.size(), fconfig);
			tmp.clear();
		}
	}

	//	6������ѹ���ļ�
	FILE* fIn = fopen(fileInName.c_str(), "wb");
	assert(fIn);
	fseek(fout, 0, SEEK_SET);
	int pos = 0;
	unsigned char putch = 0;
	ch = fgetc(fout);
	while (!feof(fout))
	{
		tmp = _info[(unsigned char)ch]._code;
		for (int i = 0; i < tmp.size(); ++i)
		{
			putch <<= 1;
			putch |= (tmp[i] - '0');
			if (++pos == 8)
			{
				fputc(putch, fIn);
				putch = 0;
				pos = 0;
			}
		}
		ch = fgetc(fout);
	}
	if (pos > 0)	//��󲻹�8λ�����
	{
		putch << (8 - pos);
		fputc(putch, fIn);
	}
	fclose(fout);
	fclose(fIn);
	fclose(fconfig);
}

void FileCompress::GenerateCode(HuffmanNode<CharInfor>* root, FileCompress& file, string& code)
{
	//��Ϊ0����Ϊ1
	if (root == NULL)
		return;
	if (root->_left == NULL &&root->_right == NULL)
	{
		file._info[root->_weight._ch]._code = code;
		return;
	}
	code.push_back('0');
	GenerateCode(root->_left, file, code);
	code.pop_back();
	code.push_back('1');
	GenerateCode(root->_right, file, code);
	code.pop_back();
}


//********************��ѹ��******************************
//�������ѹ���ļ����������ļ�ֻ��Ҫ��ѹ���ļ�����׺���˾͵��ˣ�
void FileCompress::UnCompressHuffmanCode(const char* filename)
{
	assert(filename);
	FILE* fout = fopen(filename, "rb");
	assert(fout);
	//���ļ�
	string file_config = filename;
	string file_InName = file_config;
	size_t _last = file_config.find_last_of('.');
	if (_last < file_config.size())
	{
		file_config.erase(_last);
		file_InName.erase(_last);
	}
	file_config += ".config";//����ѹ���ļ��������������ļ�
	file_InName += "Com.txt";//��ѹ����ļ���

	FILE* fconfig = fopen(file_config.c_str(), "rb");
	assert(fconfig);
	FILE* fIn = fopen(file_InName.c_str(), "wb");
	assert(fIn);

	//��ȡ�����ļ�,�����ַ������ֵĴ���
	char buf[20] = { 0 };
	unsigned char ch = fgetc(fconfig);
	while (!feof(fconfig))
	{
		fgetc(fconfig);//��ȡð�ţ�����
		fgets(buf, 20, fconfig);
		_info[ch]._count = (Type)atoi(buf);
		ch = fgetc(fconfig);
	}

	//���¹���Huffman��
	HuffmanTree<CharInfor> tree(_info, sizeof(_info) / sizeof(_info[0]), 0);
	HuffmanNode<CharInfor> *root = tree.GetHuffmanNode();
	HuffmanNode<CharInfor> *cur = root;
	Type sum_count = root->_weight._count;//�����ַ����ֵ��ܴ���

	//��ȡѹ���ļ���ѹ���ļ����Դ�ļ��ַ���Ӧ�ı��룬��ȡ���룬����Huffman����ԭ�ַ�.
	ch = fgetc(fout);
	int pos = 7;
	while ( sum_count > 0 )
	{
		while (pos >= 0)
		{
			if ((ch &(1 << pos)) == 0)//0��������
			{
				cur = cur->_left;
			}
			else
				cur = cur->_right;
			if (cur->_left == NULL&&cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fIn);//���ַ�д�뻹ԭ�ļ�
				if (--sum_count == 0)
					break;
				cur = root;
			}
			--pos;
		}
		pos = 7;
		ch = fgetc(fout);
	}
	fclose(fout);
	fclose(fconfig);
	fclose(fIn);
}

#endif