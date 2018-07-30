
#ifndef __HEAP_HPP__
#define __HEAP_HPP__

#include"Heap.h"

template <typename T,template<class> class Compare>
Heap<T, Compare>::Heap()
{}

template <typename T, template<class> class Compare>
Heap<T, Compare>::~Heap()
{}

template <typename T, template<class> class Compare>
Heap<T, Compare>::Heap(const T* array, size_t size)
{
	assert(array != NULL);
	_array.resize(size);
	for (int i = 0; i < size; ++i)
		_array[i] = array[i];
	
	//½¨¶Ñ
	for (int i = (_array.size() - 2) / 2; i >= 0; --i)
		_Adjustdown(i);
}

template <typename T,template<class> class Compare>
Heap<T, Compare>::Heap(const Heap<T, Compare>& heap)
{
	_array.resize(heap.Size());
	for (int i = 0; i < heap.Size(); ++i)
		_array[i] = heap._array[i];
}

template <typename T,template<class> class Compare>
Heap<T,Compare>& Heap<T, Compare>::operator=(const Heap<T, Compare>& heap)
{
	if (this != &heap)
	{
		_array = heap._array;
	}
	return *this;
}

template <typename T,template<class> class Compare>
void Heap<T, Compare>::Push(const T& x)
{
	_array.push_back(x);
	_Adjustup(_array.size() - 1);
}

template <typename T, template<class> class Compare>
void Heap<T, Compare>::Pop()
{
	assert(!_array.empty());
	swap(_array[0], _array[_array.size() - 1]);
	_array.pop_back();
	_Adjustdown(0);
}

template <typename T, template<class> class Compare>
T Heap<T, Compare>::Top()
{
	assert(!_array.empty());
	return _array[0];
}

template <typename T, template<class> class Compare>
size_t Heap<T, Compare>::Size()
{
	return _array.size();
}

template <typename T, template<class> class Compare>
bool Heap<T, Compare>::Empty()
{
	return _array.empty();
}

template <typename T,template<class> class Compare>
void Heap<T, Compare>::_Adjustdown(int parent)
{
	size_t child = parent * 2 + 1;
	size_t size = _array.size();

	Compare<T> com;
	while (child<size)
	{
		if (child + 1 < size && com(_array[child + 1], _array[child]))
			++child;
		if (com(_array[child], _array[parent]))
		{
			swap(_array[child], _array[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}

template <typename T, template<class> class Compare>
void Heap<T, Compare>::_Adjustup(int child)
{
	int parent = (child - 1) / 2;
	Compare<T> com;
	while (parent >= 0)
	{
		if (com(_array[child], _array[parent]))
		{
			swap(_array[child], _array[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break;
	}
}


template <typename T, template<class> class Compare>
std::ostream& operator<<(std::ostream& out, const Heap<T, Compare>& heap)
{
	for (int i = 0; i < heap._array.size(); ++i)
	{
		out << heap._array[i] << " ";
	}
	out << endl;
	return out;
}

template <typename T, template<class> class Compare>
void HeapSort(T* array, size_t size, const Compare<T>& com)
{
	CreatHeap(array, size, com);
	for (int i = size-1; i >= 0;--i)
	{
		swap(array[0], array[i]);
		Adjustdown(array, i, 0, com);
	}
}

template <typename T, template<class> class Compare>
void CreatHeap(T* array, size_t size, const Compare<T>& com)
{
	int parent = (size - 2) / 2;
	for (int i = parent; i >= 0; --i)
		Adjustdown(array,size,i,com);
}

template <typename T, template<class> class Compare>
void Adjustdown(T* array, size_t size, int parent, const Compare<T>& com)
{
	int child = 2 * parent + 1;
	while (child < (int)size)
	{
		if (child + 1 < size && com(array[child + 1], array[child]))
			++child;
		if (com(array[child], array[parent]))
		{
			swap(array[child], array[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}



#endif