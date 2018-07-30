
#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include<stdio.h>
#include<iostream>
using namespace std;

template <typename T>
struct HuffmanNode
{
	T _weight;//Ȩֵ
	HuffmanNode* _left;
	HuffmanNode* _right;

	HuffmanNode(T weight = 0)
		:_weight(weight)
		, _left(NULL)
		, _right(NULL)
	{}

};

template <typename T>
class HuffmanTree{
	typedef HuffmanNode<T> Node;
public:
	HuffmanTree();
	HuffmanTree(const T* array, size_t size, int vailed = 0);
	Node* GetHuffmanNode();
	~HuffmanTree ();

private:
	static Node* _CreateHuffmanTree(const T* array, size_t size, int vailed = 0);
	static void _Clear(Node* root);

private:
	Node* _root;
};


#endif