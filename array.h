#ifndef COLL_ARRAY_H
#define COLL_ARRAY_H

#include <ostream>
#include "error.h"

namespace coll {

template<class T>
class Array
{
	T *data = nullptr;
	size_t count = 0;
	size_t total = 0;
	
public:
	Array(size_t sz = 2);
	Array(size_t sz, const T &val);

	Array(Array &&arg);
	Array(const Array &arg);
	
	virtual ~Array();
	
	void operator=(Array &&rhs);
	void operator=(const Array &rhs);
	
	bool operator==(const Array &rhs);

	Array operator+(const T &rhs);
	Array operator+(const Array &rhs);
	
	Array operator-(const T &rhs);
	Array operator-(const Array &rhs);
	
	void operator+=(const T &rhs);
	void operator+=(const Array &rhs);
	
	void operator-=(const T &rhs);
	void operator-=(const Array &rhs);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	void add(const T &elem);
	void add(const Array &array);

	void erase(const T &elem);
	void erase(const Array &array);
	
	void insert(size_t index, const T &elem);
	void remove(size_t index);
	bool contains(const T &elem);
	void reserve(size_t sz);
	void clear();

	size_t size() const;
	bool empty() const;
	bool notEmpty() const;
};

template<class T>
Array<T>::Array(size_t sz)
{
	this->count = 0;
	this->total = sz;
	this->data = new T[sz];
}

template<class T>
Array<T>::Array(size_t sz, const T &val)
{
	this->count = sz;
	this->total = sz;
	this->data = new T[sz];
	for (size_t it(0); it < count; it++)
		this->data[it] = val;
}

template<class T>
Array<T>::Array(Array &&arg)
{
	operator=(arg);
}

template<class T>
Array<T>::Array(const Array &arg)
{
	operator=(arg);
}

template<class T>
Array<T>::~Array()
{
	if (data != nullptr)
		delete[] data;
}

template<class T>
void Array<T>::operator=(Array<T> &&rhs)
{
	this->data = rhs.data;
	this->total = rhs.total;
	this->count = rhs.count;
	rhs.data = nullptr;
	rhs.count = 0;
	rhs.total = 0;
}

template<class T>
void Array<T>::operator=(const Array<T> &rhs)
{
	if (this == &rhs) return;
	this->count = rhs.count;
	this->total = rhs.total;
	delete[] this->data;
	this->data = new T[total];
	for (size_t it(0); it < count; it++)
		this->data[it] = rhs.data[it];
}

template<class T>
bool Array<T>::operator==(const Array<T> &rhs)
{
	if (this->count != rhs.count) return false;
	for (size_t it(0); it < count; it++)
		if (this->data[it] != rhs.data[it])
			return false;
	return true;
}

template<class T>
Array<T> Array<T>::operator+(const T &rhs)
{
	Array<T> array(*this);
	array += rhs;
	return array;
}

template<class T>
Array<T> Array<T>::operator+(const Array<T> &rhs)
{
	Array<T> array(*this);
	array += rhs;
	return array;
}

template<class T>
Array<T> Array<T>::operator-(const T &rhs)
{
	Array<T> array(*this);
	array -= rhs;
	return array;
}

template<class T>
Array<T> Array<T>::operator-(const Array<T> &rhs)
{
	Array<T> array(*this);
	array -= rhs;
	return array;
}

template<class T>
void Array<T>::operator+=(const T &rhs)
{
	add(rhs);
}

template<class T>
void Array<T>::operator+=(const Array<T> &rhs)
{
	add(rhs);
}

template<class T>
void Array<T>::operator-=(const T &rhs)
{
	erase(rhs);
}

template<class T>
void Array<T>::operator-=(const Array<T> &rhs)
{
	erase(rhs);
}

template<class T>
void Array<T>::add(const T &elem)
{
	if (count == total)
		reserve(total * 2);
	data[count++] = elem;
}

template<class T>
void Array<T>::add(const Array<T> &array)
{
	for (size_t it(0); it < array.size(); it++)
		add(array[it]);
}

template<class T>
void Array<T>::erase(const T &elem)
{
	for (size_t it(0); it < count; it++)
		if (data[it] == elem) {
			erase(it);
			break;
		}
}

template<class T>
void Array<T>::erase(const Array<T> &array)
{
	for (size_t it(0); it < array.size(); it++)
		erase(array[it]);
}

template<class T>
void Array<T>::insert(size_t index, const T &elem)
{
	if (index >= count) Error::fatal("Array index out of bound.");
	if (count == total) reserve(total * 2);
	for (size_t it = count; it > index; it--)
		data[it] = std::move(data[it - 1]);
	data[index] = elem;
	count++;
}

template<class T>
void Array<T>::remove(size_t index)
{
	if (index >= count) Error::fatal("Array index out of bound.");
	count--;
	for (size_t it = index; it < count; it++)
		data[it] = std::move(data[it + 1]);
}

template<class T>
bool Array<T>::contains(const T &elem)
{
	for (size_t it(0); it < count; it++)
		if (data[it] == elem)
			return true;
	return false;
}

template<class T>
void Array<T>::reserve(size_t sz)
{
	T *temp = data;
	data = new T[sz];
	for (size_t it(0); it < count; it++)
		data[it] = std::move(temp[it]);
	total = sz;
	delete[] temp;
}

template<class T>
void Array<T>::clear()
{
	if (data != nullptr) delete[] data;
	count = 0;
	total = 0;
}

template<class T>
T& Array<T>::operator[](size_t index)
{
	if (index >= count) Error::fatal("Array index out of bound.");
	return data[index];
}

template<class T>
const T& Array<T>::operator[](size_t index) const
{
	if (index >= count) Error::fatal("Array index out of bound.");
	return data[index];
}

template<class T>
size_t Array<T>::size() const
{
	return count;
}

template<class T>
bool Array<T>::empty() const
{
	return size() == 0;
}

template<class T>
bool Array<T>::notEmpty() const
{
	return !empty();
}

template<class T>
std::ostream& operator<<(std::ostream &lhs, const Array<T> &rhs)
{
	lhs << "[";
	for (int i = 0; i < rhs.size(); i++) {
		if (i > 0) lhs << ", ";
		lhs << rhs[i];
	}
	lhs << "]";
	return lhs;
}

}

#endif