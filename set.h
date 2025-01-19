#ifndef COLL_SET_H
#define COLL_SET_H

#include <math.h>
#include "array.h"

namespace coll {

template<class T>
class Set
{
	struct TreeNode
	{
		T data;
		size_t height = 0;
		size_t factor = 0;
		TreeNode *left = nullptr;
		TreeNode *right = nullptr;
		TreeNode(T data) : data(data) {}
	};
	
	TreeNode *root = nullptr;
	size_t count = 0;

	bool contains(TreeNode *node, const T &data) const
	{
		if (node == nullptr) return false;
		if (data < node->data) return contains(node->left, data);
		else if (data > node->data) return contains(node->right, data);
		else return true;
	}

	void update(TreeNode *node)
	{
		size_t lh = (node->left == nullptr) ? -1 : node->left->height;
		size_t rh = (node->right == nullptr) ? -1 : node->right->height;
		node->height = (lh > rh ? lh : rh) + 1;
		node->factor = rh - lh;
	}

	TreeNode* balance(TreeNode *root)
	{
		if (root->factor == -2) {
			if (root->left->factor <= 0)
	    		return leftLeftCase(root);
	    	return leftRightCase(root);
		} else if (root->factor == +2) {
			if (root->right->factor >= 0)
				return rightRightCase(root);
			return rightLeftCase(root);	
		}
		return root;
	}

	TreeNode* insert(TreeNode *root, const T &data)
	{
		if (root == nullptr)
			return new TreeNode(data);
		if (data > root->data)
			root->right = insert(root->right, data);
		else root->left = insert(root->left, data);
		update(root);
		return balance(root);
	}

	TreeNode* erase(TreeNode *root, const T &data)
	{
		if (root == nullptr) return root;
		if (data < root->data)
			root->left = erase(root->left, data);
		else if (data > root->data) 
			root->right = erase(root->right, data);
		else {
			if (root->left == nullptr and root->right == nullptr) {
				delete root;
				return nullptr;
			} else if (root->left == nullptr) {
				delete root;
				return root->right;
			} else if (root->right == nullptr) {
				delete root;
				return root->left;
			} else {
				TreeNode *minNode = findMin(root->right);
				root->data = minNode->data;
				root->right = erase(root->right, minNode->data);
			}
		}
		update(root);
		return balance(root);
	}

	TreeNode* leftLeftCase(TreeNode *node)
	{
		return rightRotation(node);
	}

	TreeNode* rightRightCase(TreeNode *node)
	{
		return leftRotation(node);
	}
	
	TreeNode* leftRightCase(TreeNode *node)
	{
		node->left = leftRotation(node->left);
		return rightRotation(node);
	}

	TreeNode* rightLeftCase(TreeNode *node)
	{
		node->right = rightRotation(node->right);
		return leftRotation(node);
	}

	TreeNode* leftRotation(TreeNode *node)
	{
		TreeNode *parent = node->right;
		node->right = parent->left;
		parent->left = node;
		update(node);
		update(parent);
		return parent;
	}

	TreeNode* rightRotation(TreeNode *node)
	{
		TreeNode *parent = node->left;
		node->left = parent->right;
		parent->right = node;
		update(node);
		update(parent);
		return parent;
	}

	TreeNode* findMin(TreeNode *root) const
	{
		while (root->left != nullptr)
			root = root->left;
		return root;
	}

	TreeNode* findMax(TreeNode *root) const
	{
		while (root->right != nullptr)
			root = root->right;
		return root;	
	}
public:
	Set();
	Set(Set &&arg);
	Set(const Set &arg);

	virtual ~Set();
	
	void operator=(Set &&rhs);
	void operator=(const Set &rhs);

	Set operator+(const T &rhs);
	Set operator+(const Set &rhs);
	
	Set operator-(const T &rhs);
	Set operator-(const Set &rhs);
	
	void operator+=(const T &rhs);
	void operator+=(const Set &rhs);
	
	void operator-=(const T &rhs);
	void operator-=(const Set &rhs);

	bool contains(const T &data) const;
	void insert(const T &data);
	void erase(const T &data);

	T findMin() const;
	T findMax() const;

	void clear();
	Array<T> traverse() const;

	size_t size() const;
	size_t height() const;
	
	bool empty() const;
	bool notEmpty() const;
};

template<class T>
Set<T>::Set() {}

template<class T>
Set<T>::~Set<T>()
{
	if (notEmpty())
		clear();
}

template<class T>
Set<T>::Set(Set &&arg)
{
	this->count = arg.count;
	this->root = arg.root;
	arg.count = 0;
	arg.root = nullptr;
}

template<class T>
Set<T>::Set(const Set &arg)
{
	if (this == &arg) return;
	Queue<TreeNode*> queue;
	queue.enqueue(arg.root);
	while (queue.notEmpty()) {
		TreeNode *node = queue.dequeue();
		insert(node->data);
		if (node->left != nullptr) queue.enqueue(node->left);
		if (node->right != nullptr) queue.enqueue(node->right);
	}
}

template<class T>
void Set<T>::operator=(Set<T> &&rhs)
{
	this->root = rhs.root;
	this->count = rhs.count;
	rhs.root = nullptr;
	rhs.count = 0;
}

template<class T>
void Set<T>::operator=(const Set<T> &rhs)
{
	if (this == &rhs) return;
	clear();
	Queue<TreeNode*> queue;
	queue.enqueue(rhs.root);
	while (queue.notEmpty()) {
		TreeNode *node = queue.dequeue();
		insert(node->data);
		if (node->left != nullptr) queue.enqueue(node->left);
		if (node->right != nullptr) queue.enqueue(node->right);
	}
}

template<class T>
Set<T> Set<T>::operator+(const T &rhs)
{
	Set<T> set(*this);
	set += rhs;
	return set;
}

template<class T>
Set<T> Set<T>::operator+(const Set<T> &rhs)
{
	Set<T> set(*this);
	set += rhs;
	return set;
}

template<class T>
Set<T> Set<T>::operator-(const T &rhs)
{
	Set<T> set(*this);
	set -= rhs;
	return set;
}

template<class T>
Set<T> Set<T>::operator-(const Set<T> &rhs)
{
	Set<T> set(*this);
	set -= rhs;
	return set;
}

template<class T>
void Set<T>::operator+=(const T &rhs)
{
	insert(rhs);
}

template<class T>
void Set<T>::operator+=(const Set<T> &rhs)
{
	Queue<TreeNode*> queue;
	queue.enqueue(rhs.root);
	while (queue.notEmpty()) {
		TreeNode *node = queue.dequeue();
		insert(node->data);
		if (node->left != nullptr) queue.enqueue(node->left);
		if (node->right != nullptr) queue.enqueue(node->right);
	}
}

template<class T>
void Set<T>::operator-=(const T &rhs)
{
	erase(rhs);
}

template<class T>
void Set<T>::operator-=(const Set<T> &rhs)
{
	Queue<TreeNode*> queue;
	queue.enqueue(rhs.root);
	while (queue.notEmpty()) {
		TreeNode *node = queue.dequeue();
		erase(node->data);
		if (node->left != nullptr) queue.enqueue(node->left);
		if (node->right != nullptr) queue.enqueue(node->right);
	}
}

template<class T>
void Set<T>::insert(const T &data)
{
	if (!contains(data)) {
		root = insert(root, data);
		count++;
	}
}

template<class T>
bool Set<T>::contains(const T &data) const
{
	return contains(root, data);
}

template<class T>
void Set<T>::erase(const T &data)
{
	if (contains(data)) {
		root = erase(root, data);
		count--;
	}
}

template<class T>
T Set<T>::findMin() const
{
	if (empty()) Error::fatal("Tree is empty.");
	return findMin(root)->data;	
}

template<class T>
T Set<T>::findMax() const
{
	if (empty()) Error::fatal("Tree is empty.");
	return findMax(root)->data;	
}

template<class T>
void Set<T>::clear()
{
	Queue<TreeNode*> queue;
	queue.enqueue(root);
	while (queue.notEmpty()) {
		TreeNode *node = queue.dequeue();
		if (node->left != nullptr) queue.enqueue(node->left);
		if (node->right != nullptr) queue.enqueue(node->right);
		delete node;
	}
	this->root = nullptr;
	this->count = 0;
}

template<class T>
Array<T> Set<T>::traverse() const
{
	Array<T> array(size());
	Queue<TreeNode*> queue;
	queue.enqueue(root);
	while (queue.notEmpty()) {
		TreeNode *node = queue.dequeue();
		array.add(node->data);
		if (node->left != nullptr) queue.enqueue(node->left);
		if (node->right != nullptr) queue.enqueue(node->right);
	}
	return array;
}

template<class T>
size_t Set<T>::size() const
{
	return count;
}

template<class T>
size_t Set<T>::height() const
{
	return root == nullptr ? -1 : root->height;
}

template<class T>
bool Set<T>::empty() const
{
	return size() == 0;
}

template<class T>
bool Set<T>::notEmpty() const
{
	return !empty();
}

template<class T>
std::ostream& operator<<(std::ostream &lhs, const Set<T> &rhs)
{
	lhs << "{";
	Array<T> array = rhs.traverse();
	for (int i = 0; i < array.size(); i++) {
		if (i > 0) lhs << ", ";
		lhs << array[i];
	}
	lhs << "}";
	return lhs;
}

}

#endif