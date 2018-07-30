#define _CRT_SECURE_NO_DEPRECATE 1

#include<iostream>
using namespace std;
#include<string>
#include<time.h>
#include"Huffman.hpp"
#include"FileCompress.h"


void test()
{
	string str = "文本.txt";
	clock_t start_time = clock();
	FileCompress fc;
	fc.CompressHuffmanCode(str.c_str());
	clock_t end_time = clock();
	cout << "压缩时间：" << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}
void untest()
{
	string str = "文本.huff";
	clock_t start_time = clock();
	FileCompress fc;
	fc.UnCompressHuffmanCode(str.c_str());
	clock_t end_time = clock();
	cout << "解压时间：" << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}

int main()
{
	//test();
	untest();

	system("pause");
	return 0;
}