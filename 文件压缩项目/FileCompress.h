
#ifndef __FILECOMPRESS_H__
#define __FILECOMPRESS_H__

#include<string>
#include"Huffman.h"
#include"Huffman.hpp"

typedef unsigned long long Type;
struct CharInfor
{
	unsigned char _ch;//字符
	Type _count;	//字符出现的次数
	string _code;	//字符编码

	CharInfor(Type count = 0)
		:_ch(0)
		, _count(count)
	{}

	bool operator!=(const CharInfor& info)const
	{
		return _count != info._count;
	}

	bool operator<(const CharInfor& info)const
	{
		return _count < info._count;
	}
	CharInfor operator+(const CharInfor& info)const
	{
		return CharInfor(_count + info._count);
	}
};

class FileCompress
{
public:
	FileCompress();
	void CompressHuffmanCode(const char* filename);
	void UnCompressHuffmanCode(const char* filename);
	//void PrintCode()const;

private:
	void GenerateCode(HuffmanNode<CharInfor>* root, FileCompress& file, string& code);

private:
	CharInfor _info[256];
};


#endif