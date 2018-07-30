
#ifndef __HUFFMAN_HPP__
#define __HUFFMAN_HPP__

#include"Huffman.h"
#include"Heap.hpp"

template <typename T>
HuffmanTree<T>::HuffmanTree() : _root(NULL) {}

template <typename T>
HuffmanTree<T>::HuffmanTree(const T* array, size_t size, int vailed): _root(NULL)
{
	_root = _CreateHuffmanTree(array,size,vailed);
}

//构建huffman树
template <typename T>
HuffmanNode<T>* HuffmanTree<T>::_CreateHuffmanTree(const T* array, size_t size, int vailed)
{
	// 选最小的，建小堆
	Heap<Node*, Less> heap;
	Node* parent = NULL;
	for (int i = 0; i < size; ++i)
	{
		if (array[i] != vailed)
		{
			heap.Push(new Node(array[i]));
		}
	}
	while (heap.Size() > 1)
	{
		Node* minfirst = heap.Top();
		heap.Pop();
		Node* minsecond = heap.Top();
		heap.Pop();
		parent = new Node(minfirst->_weight + minsecond->_weight);
		parent->_left = minfirst;
		parent->_right = minsecond;
		heap.Push(parent);
	}
	return parent;
}

template <typename T>
HuffmanNode<T>* HuffmanTree<T>::GetHuffmanNode()
{
	return _root;
}

template <typename T>
HuffmanTree<T>::~HuffmanTree()
{
	if (_root)
		_Clear(_root);
}

template <typename T>
void HuffmanTree<T>::_Clear(HuffmanNode<T>* root)
{
	if (root)
	{
		_Clear(root->_left);
		_Clear(root->_right);
		delete root;
	}
	root = NULL;
}



#endif