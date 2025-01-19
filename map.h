#ifndef COLL_MAP_H
#define COLL_MAP_H

#include <iostream>
#include "hash.h"

namespace coll {

template<class K, class V>
class Map
{
	struct Node
	{
		K key;
		V val;
		Node *next;
		Node(K key, V val) {
			this->key = key;
			this->val = val;
			this->next = nullptr;
		}
	};
	Node** lists = nullptr;
	size_t listCount = 0;
	size_t count = 0;
public:
	Map();
	void put(const K &key, const V &val);
	bool hasKey(const K &key);
	void erase(const K &key);

	V get(const K &key);
	V getOrDefault(const K &key, const V &val);
	
	size_t size() const;
	bool empty() const;
	bool notEmpty() const;
};

template<class K, class V>
Map<K, V>::Map()
{
	listCount = 8;
	lists = new Node*[listCount];
	for (size_t it(0); it < listCount; it++)
		lists[it] = nullptr;
}

template<class K, class V>
void Map<K, V>::put(const K &key, const V &val)
{
	size_t h = hash(key) % listCount;
	Node *node = new Node(key, val);
	if (lists[h] == nullptr) lists[h] = node;
	else node->next = lists[h], lists[h] = node;
	count++;
}

template<class K, class V>
bool Map<K, V>::hasKey(const K &key)
{
	size_t h = hash(key) % listCount;
	for (auto it = lists[h]; it != nullptr; it = it->next)
		if (it->key == key) return true;
	return false;
}

template<class K, class V>
void Map<K, V>::erase(const K &key)
{
	size_t h = hash(key) % listCount;
	if (lists[h] == nullptr) return;
	if (lists[h]->next == nullptr) {
		delete lists[h];
		lists[h] = nullptr;
		return;
	}
	Node *curr = lists[h], *prev = nullptr;
	while (curr != nullptr) {
		Node *next = curr->next;
		if (curr->key == key) {
			prev->next = curr->next;
			delete curr;
			count--;
			break;
		}
		curr = next;
		prev = curr;
	}
}

template<class K, class V>
V Map<K, V>::get(const K &key)
{
	size_t h = hash(key) % listCount;
	for (auto it = lists[h]; it != nullptr; it = it->next)
		if (it->key == key) return it->val;
	return V();
}

template<class K, class V>
V Map<K, V>::getOrDefault(const K &key, const V &val)
{
	size_t h = hash(key) % listCount;
	for (auto it = lists[h]; it != nullptr; it = it->next)
		if (it->key == key) return it->val;
	return val;
}

template<class K, class V>
size_t Map<K, V>::size() const
{
	return count;
}

template<class K, class V>
bool Map<K, V>::empty() const
{
	return size() == 0;
}

template<class K, class V>
bool Map<K, V>::notEmpty() const
{
	return !empty();
}

}

#endif