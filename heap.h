#ifndef COLL_BINARY_HEAP_H
#define COLL_BINARY_HEAP_H

#include "error.h"
#include "array.h"

namespace coll {

template<class T>
class BinaryHeap
{
	Array<T> data;

	void moveUP();
	void moveDown();
	void swap(size_t i, size_t j);
	bool hasParent(size_t i) const;
	bool hasLeft(size_t i) const;
	bool hasRight(size_t i) const;
	size_t left(size_t i) const;
	size_t right(size_t i) const;
	size_t parent(size_t i) const;
public:
	BinaryHeap();
	virtual ~BinaryHeap();

	void insert(const T &elem);
	const T& getMin() const;
	T deleteMin();
	
	size_t size() const;
	bool empty() const;
	bool notEmpty() const;
};


template<class T>
BinaryHeap<T>::BinaryHeap() {}

template<class T>
BinaryHeap<T>::~BinaryHeap() {}

template<class T>
void BinaryHeap<T>::insert(const T &elem)
{
	data.add(elem);
	moveUP();
}

template<class T>
T BinaryHeap<T>::deleteMin()
{
	T result = getMin();
	data[0] = data[data.size() - 1];
	data.remove(data.size() - 1);
	moveDown();
	return result;
}

template<class T>
const T& BinaryHeap<T>::getMin() const
{
	if (empty()) Error::fatal("Heap underflow.");
	return data[0];
}

template<class T>
void BinaryHeap<T>::moveUP()
{
	size_t index = data.size() - 1;
	while (hasParent(index) && data[index] < data[parent(index)]) {
		swap(index, parent(index));
		index = parent(index);
	}
}

template<class T>
void BinaryHeap<T>::moveDown()
{
	size_t index = 0;
	while (hasLeft(index)) {
		size_t lhs = left(index);
		size_t rhs = right(index);
		size_t smaller = lhs;
		if (hasRight(index) && data[rhs] < data[lhs])
			smaller = rhs;
		if (data[smaller] < data[index])
			swap(smaller, index);
		else break;
		index = smaller;
	}
}

template<class T>
void BinaryHeap<T>::swap(size_t i, size_t j)
{
	T temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}

template<class T>
bool BinaryHeap<T>::hasParent(size_t i) const
{
	return i > 0;
}

template<class T>
bool BinaryHeap<T>::hasLeft(size_t i) const
{
	return left(i) < data.size();
}

template<class T>
bool BinaryHeap<T>::hasRight(size_t i) const
{
	return right(i) < data.size();
}

template<class T>
size_t BinaryHeap<T>::left(size_t i) const
{
	return 2 * i + 1;
}

template<class T>
size_t BinaryHeap<T>::right(size_t i) const
{
	return 2 * i + 2;
}

template<class T>
size_t BinaryHeap<T>::parent(size_t i) const
{
	return (i - 1) / 2;
}

template<class T>
size_t BinaryHeap<T>::size() const
{
	return data.size();
}

template<class T>
bool BinaryHeap<T>::empty() const
{
	return data.size() == 0;
}

template<class T>
bool BinaryHeap<T>::notEmpty() const
{
	return !empty();
}

}

#endif