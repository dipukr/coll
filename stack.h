#pragma once
#include <ostream>
#include "error.h"

namespace coll {

template<class T>
class Stack
{
	struct Node {T data; Node *next;};
	Node *head = nullptr;
	size_t count = 0;
public:
	Stack();
	Stack(Stack &&arg);
	Stack(const Stack &arg);
	
	virtual ~Stack();
	
	void operator=(Stack &&rhs);
	void operator=(const Stack &rhs);
	
	void push(const T &elem);
	const T& peek() const;
	T pop();
	
	void reverse();
	void clear();
	
	size_t size() const;
	bool empty() const;
	bool notEmpty() const;
};

template<class T>
Stack<T>::Stack() {}

template<class T>
Stack<T>::~Stack()
{
	clear();
}

template<class T>
Stack<T>::Stack(Stack<T> &&arg)
{
	this->head = arg.head;
	this->count = arg.count;
	arg.head = nullptr;
	arg.count = 0;
}

template<class T>
Stack<T>::Stack(const Stack<T> &arg)
{
	for (auto it = arg.head; it != nullptr; it = it->next)
		push(it->data);
	reverse();
}

template<class T>
void Stack<T>::operator=(Stack<T> &&rhs)
{
	this->head = rhs.head;
	this->count = rhs.count;
	rhs.head = nullptr;
	rhs.count = 0;
}

template<class T>
void Stack<T>::operator=(const Stack<T> &rhs)
{
	if (this == &rhs) return;
	else clear();
	for (auto it = rhs.head; it != nullptr; it = it->next)
		push(it->data);
	reverse();
}

template<class T>
void Stack<T>::push(const T &elem)
{
	Node *node = new Node;
	node->data = elem;
	node->next = head;
	head = node;
	count++;
}

template<class T>
T Stack<T>::pop()
{
	if (empty()) Error::fatal("Stack underflow.");
	T retval = head->data;
	Node *node = head;
	head = head->next;
	delete node;
	count--;
	return retval;
}

template<class T>
const T& Stack<T>::peek() const
{
	if (empty()) Error::fatal("Stack underflow.");
	return head->data;
}

template<class T>
void Stack<T>::clear()
{
	Node *curr = head;
	while (curr != nullptr) {
		Node *next = curr->next;
		delete curr;
		curr = next;
	}
	this->count = 0;
	this->head = nullptr;
}

template<class T>
void Stack<T>::reverse()
{
	Node *prev = nullptr, *curr = head;
	while (curr != nullptr) {
		Node *next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
}

template<class T>
size_t Stack<T>::size() const
{
	return count;
}

template<class T>
bool Stack<T>::empty() const
{
	return size() == 0;
}

template<class T>
bool Stack<T>::notEmpty() const
{
	return !empty();
}

template<class T>
std::ostream& operator<<(std::ostream &lhs, const Stack<T> &rhs)
{
	lhs << "[";
	Stack<T> a = rhs;
	a.reverse();
	for (int i = 0; i < rhs.size(); i++) {
		if (i > 0) lhs << ", ";
		lhs << a.pop();
	}
	lhs << "]";
	return lhs;
}

}