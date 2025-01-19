#ifndef COLL_LIST_H
#define COLL_LIST_H

#include <ostream>
#include "error.h"

namespace coll {

template<class T>
class List
{
	struct Node {T data; Node *prev, *next;};	
	Node *tail = nullptr;
	Node *head = nullptr;
	size_t count = 0;
public:
	List();
	List(List &&arg);
	List(const List &arg);
	
	virtual ~List();
	
	void operator=(List &&rhs);
	void operator=(const List &rhs);
	
	void operator+=(const T &rhs);
	void operator+=(const List &rhs);

	void operator-=(const T &rhs);
	void operator-=(const List &rhs);
	
	void addFirst(const T &elem);
	void addLast(const T &elem);
	
	T removeFirst();
	T removeLast();
	
	const T& first() const;
	const T& last() const;
	
	bool contains(const T &elem);
	void erase(const T &elem);
	void clear();
	void reverse();
	
	size_t size() const;
	bool empty() const;
	bool notEmpty() const;
};

template<class T>
List<T>::List() {}

template<class T>
List<T>::List(List<T> &&arg)
{
	operator=(arg);
}

template<class T>
List<T>::List(const List<T> &arg)
{
	operator=(arg);
}

template<class T>
List<T>::~List()
{
	clear();
}

template<class T>
void List<T>::operator=(List<T> &&rhs)
{
	this->head = rhs.head;
	this->tail = rhs.tail;
	this->count = rhs.count;
	rhs.head = nullptr;
	rhs.tail = nullptr;
	rhs.count = 0;
}

template<class T>
void List<T>::operator=(const List<T> &rhs)
{
	if (this == &rhs) return;
	else clear();
	for (auto it = rhs.head; it != nullptr; it = it->next)
		addLast(it->data);
}

template<class T>
void List<T>::operator+=(const T &rhs)
{
	addLast(rhs);
}

template<class T>
void List<T>::operator+=(const List<T> &rhs)
{
	for (auto it = rhs.head; it != nullptr; it = it->next)
		addLast(it->data);
}

template<class T>
bool List<T>::contains(const T &elem)
{
	for (auto iter = head; iter != nullptr; iter = iter->next)
		if (iter->data == elem)
			return true;
	return false;
}

template<class T>
void List<T>::erase(const T &elem)
{
	Node *curr = head;
	while (curr != nullptr) {
		if (curr->data == elem) {
			Node *prev = curr->prev;
			Node *next = curr->next;
			prev->next = next;
			next->prev = prev;
			delete curr;
			break;
		} else curr = curr->next;
	}
	count--;
}

template<class T>
void List<T>::addFirst(const T &elem)
{
	Node *node = new Node;
	node->data = elem;
	node->prev = nullptr;
	node->next = nullptr;
	if (empty()) {
		head = tail = node;
	} else {
		node->next = head;
		head->prev = node;
		head = node;
	}
	count++;
}

template<class T>
void List<T>::addLast(const T &elem)
{
	Node *node = new Node;
	node->data = elem;
	node->prev = nullptr;
	node->next = nullptr;
	if (empty()) {
		head = tail = node;
	} else {
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
	count++;
}

template<class T>
T List<T>::removeFirst()
{
	if (empty()) Error::fatal("List is empty.");
	T retval = first();
	Node *node = head;
	head = head->next;
	if (head != nullptr)
		head->prev = nullptr;
	delete node;
	count--;
	return retval;
}

template<class T>
T List<T>::removeLast()
{
	if (empty()) Error::fatal("List is empty.");
	T retval = last();
	Node *prev = tail->prev;
	prev->next = nullptr;
	delete tail;
	tail = prev;
	count--;
	return retval;
}

template<class T>
void List<T>::clear()
{
	while (notEmpty())
		removeFirst();
}

template<class T>
const T& List<T>::first() const
{
	if (empty()) Error::fatal("List is empty.");
	return head->data;
}

template<class T>
const T& List<T>::last() const
{
	if (empty()) Error::fatal("List is empty.");
	return tail->data;
}

template<class T>
size_t List<T>::size() const
{
	return count;
}

template<class T>
bool List<T>::empty() const
{
	return size() == 0;
}

template<class T>
bool List<T>::notEmpty() const
{
	return !empty();
}

template<class T>
std::ostream& operator<<(std::ostream &lhs, const List<T> &rhs)
{
	lhs << "[";
	List<T> coll = rhs;
	size_t count = 0;
	while (coll.notEmpty()) {
		if (count++ > 0) lhs << ", ";
		lhs << coll.removeFirst();
	}
	lhs << "]";
	return lhs;
}

}

#endif
