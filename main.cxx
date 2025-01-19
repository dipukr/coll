#include <iostream>
#include "queue.h"
#include "stack.h"
#include "array.h"
#include "heap.h"
#include "list.h"
#include "deque.h"
#include "set_.h"

struct TreeNode
{
	int data;
	TreeNode *left, *right;
};

int treeSum(TreeNode *root)
{
	if (root == nullptr) return 0;
	int leftSum = treeSum(root->left);
	int rightSum = treeSum(root->right);
	return leftSum + rightSum + root->data;
}

bool findPath(TreeNode *root, int val, List<int> &path)
{
	if (root == nullptr) return false;
	if (root->data == val) return true;
	if (findPath(root->left, val, path)) {
		path.addLast(root->data);
		return true;
	}
	if (findPath(root->right, val, path)) {
		path.addLast(root->data);
		return true;
	}
	return false;
}

int main(const int argc, const char **argv)
{
	std::cout << "C++ Programming Language" << std::endl;
	Queue<int> queue;
	queue.enqueue(100);
	queue.enqueue(200);
	queue.enqueue(300);
	std::cout << queue << std::endl;
	while (queue.notEmpty()) {
		std::cout << queue.dequeue() << std::endl;
	}
	List<int> list;
	list.addLast(100);
	list.addLast(200);
	list.addLast(300);
	list.addFirst(400);
	list.addFirst(500);
	std::cout << list << std::endl;
	Set<int> set;
	set.insert(100);
	set.insert(200);
	set.insert(300);
	std::cout << set << std::endl;

	size_t xy = 100;


	return EXIT_SUCCESS;
}