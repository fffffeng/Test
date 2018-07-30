
#ifndef __HEAP_H__
#define __HEAP_H__


#include<assert.h>
#include<vector>
#include<iostream>
#include"Huffman.h"
#include "FileCompress.h"
#include "Huffman.hpp"

using namespace std;

template <typename T>
struct Less
{
	bool operator()(const T& left,const T& right) const
	{
		return left < right;
	}
};

template <typename K>	//模板的偏特化
struct Less<HuffmanNode<K>*>
{
	bool operator()(const HuffmanNode<K>* left,const HuffmanNode<K>* right) const
	{
		return left->_weight < right->_weight;
	}
};

template <typename T>
struct Greater
{
	bool operator()(const T& left, const T& right) const
	{
		return left > right;
	}
};

template <typename T,template<class> class Compare = Greater>
class Heap{
	friend std::ostream& operator<<(std::ostream& out, const Heap<T, Compare>& heap);
public:
	Heap();
	Heap(const T* array, size_t size);
	Heap(const Heap<T, Compare>& heap);
	Heap<T, Compare>& operator=(const Heap<T, Compare>& heap);
	~Heap();

	void Push(const T& x);
	void Pop();
	T Top();
	bool Empty();
	size_t Size();

private:
	void _Adjustdown(int parent);
	void _Adjustup(int child);

private:
	vector<T> _array;
};


//以下函数可以提供对外访问

//堆排序
template <typename T, template<class> class Compare = Greater>
void HeapSort(T* array, size_t size, const Compare<T>& com = Compare<T>());

//建初堆
template <typename T, template<class> class Compare = Greater>
void CreatHeap(T* array, size_t size, const Compare<T>& com = Compare<T>());

//下调
template <typename T, template<class> class Compare = Greater>
void Adjustdown(T* array, size_t size, int parent = 0, Compare<T>& com = Compare<T>);

template <typename T, template<class> class Compare = Greater>
std::ostream& operator<<(std::ostream& out, const Heap<T, Compare>& heap);

template <typename T,template<class> class Compare = Greater>
void GetTopk(T* array, const vector<T>& money, const size_t& k, const Compare<T>& com = Compare<T>());


#endif