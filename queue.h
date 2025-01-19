#ifndef COLL_QUEUE_H
#define COLL_QUEUE_H

#include <ostream>
#include "error.h"

namespace coll {

template<class T>
class Queue
{
	struct Node {T data; Node *next;};
	Node *tail = nullptr;
	Node *head = nullptr;
	size_t count = 0;
public:
	Queue();
	Queue(Queue &&arg);
	Queue(const Queue &arg);
	virtual ~Queue();

	void operator=(Queue &&rhs);
	void operator=(const Queue &rhs);
	
	void enqueue(const T &elem);
	T dequeue();
	const T& peek() const;
	
	void clear();
	
	U64 size() const;
	bool empty() const;
	bool notEmpty() const;
};

template<class T>
Queue<T>::Queue() {}

template<class T>
Queue<T>::~Queue()
{
	clear();
}

template<class T>
Queue<T>::Queue(Queue<T> &&arg)
{
	this->head = arg.head;
	this->tail = arg.tail;
	this->count = arg.count;
	arg.head = nullptr;
	arg.tail = nullptr;
	arg.count = 0;
}

template<class T>
Queue<T>::Queue(const Queue<T> &arg)
{
	for (auto it = arg.head; it != nullptr; it = it->next)
		enqueue(it->data);
}

template<class T>
void Queue<T>::operator=(Queue<T> &&rhs)
{
	this->head = rhs.head;
	this->tail = rhs.tail;
	this->count = rhs.count;
	rhs.head = nullptr;
	rhs.tail = nullptr;
	rhs.count = 0;
}

template<class T>
void Queue<T>::operator=(const Queue<T> &rhs)
{
	if (this == &rhs) return;
	else clear();
	for (auto it = rhs.head; it != nullptr; it = it->next)
		enqueue(it->data);
}

template<class T>
void Queue<T>::enqueue(const T &elem)
{
	Node *node = new Node;
	node->data = elem;
	if (empty()) {
		head = tail = node;
	} else {
		tail->next = node;
		tail = node;
	}
	count++;
}

template<class T>
T Queue<T>::dequeue()
{
	if (empty()) Error::fatal("Queue underflow.");
	T retval = head->data;
	Node *node = head;
	head = head->next;
	delete node;
	count--;
	return retval;
}

template<class T>
const T& Queue<T>::peek() const
{
	if (empty()) Error::fatal("Queue underflow.");
	return head->data;
}

template<class T>
void Queue<T>::clear()
{
	Node *curr = head;
	while (curr != nullptr) {
		Node *next = curr->next;
		delete curr;
		curr = next;
	}
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template<class T>
size_t Queue<T>::size() const
{
	return count;
}

template<class T>
bool Queue<T>::empty() const
{
	return size() == 0;
}

template<class T>
bool Queue<T>::notEmpty() const
{
	return !empty();
}

template<class T>
std::ostream& operator<<(std::ostream &lhs, const Queue<T> &rhs)
{
	lhs << "[";
	Queue<T> a = rhs;
	for (int i = 0; i < rhs.size(); ++i) {
		if (i > 0) lhs << ", ";
		lhs << a.dequeue();
	}
	lhs << "]";
	return lhs;
}

}

#endif