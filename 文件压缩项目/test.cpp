#define _CRT_SECURE_NO_DEPRECATE 1

#include<iostream>
using namespace std;
#include<string>
#include<time.h>
#include"Huffman.hpp"
#include"FileCompress.h"


void test()
{
	string str = "�ı�.txt";
	clock_t start_time = clock();
	FileCompress fc;
	fc.CompressHuffmanCode(str.c_str());
	clock_t end_time = clock();
	cout << "ѹ��ʱ�䣺" << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}
void untest()
{
	string str = "�ı�.huff";
	clock_t start_time = clock();
	FileCompress fc;
	fc.UnCompressHuffmanCode(str.c_str());
	clock_t end_time = clock();
	cout << "��ѹʱ�䣺" << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}

int main()
{
	//test();
	untest();

	system("pause");
	return 0;
}