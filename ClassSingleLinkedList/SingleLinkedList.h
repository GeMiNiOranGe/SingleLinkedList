#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H
#pragma once

#include <iostream>

template<class data_type> class SingleLinkedList;
template<class data_type> class Node {
public:
	friend class SingleLinkedList<data_type>;
	Node(data_type);
	Node<data_type> * get_next();
	data_type get_data();
private:
	Node<data_type> * ptr_next;
	data_type data;
};
template<class data_type> class SingleLinkedList {
public:
	SingleLinkedList();
	~SingleLinkedList();

	int get_size();
	Node<data_type> * get_head();
	Node<data_type> * get_tail();
	bool is_empty();

	void add_head(data_type);
	void add_tail(data_type);
	void add_previous(Node<data_type> *, data_type);
	void add_next(Node<data_type> *, data_type);
	void insert_at(int, data_type);

	Node<data_type> * search(data_type);
	Node<data_type> * search_previous(Node<data_type> *);

	void remove_head();
	void remove_tail();
	void remove_after(Node<data_type> *);
	void remove_first_of(data_type);
	void remove_elements_of(data_type);

	Node<data_type> * find_middle_node();

	void reverse();
	void selection_sort();
	void clear();
	void show_elements_from(Node<data_type> * ptr_node);
	void show_list();
private:
	Node<data_type> * ptr_head;
	Node<data_type> * ptr_tail;
	int size;
};
#endif 

template<class data_type> inline Node<data_type>::Node(data_type _data) {
	this->data = _data;
	this->ptr_next = nullptr;
}
template<class data_type> inline Node<data_type> * Node<data_type>::get_next() {
	return this->ptr_next;
}
template<class data_type> inline data_type Node<data_type>::get_data() {
	return this->data;
}
template<class data_type> inline SingleLinkedList<data_type>::SingleLinkedList() {
	this->ptr_head = nullptr;
	this->ptr_tail = nullptr;
	this->size = 0;
}
template<class data_type> inline SingleLinkedList<data_type>::~SingleLinkedList() {
	clear();
}

template<class data_type> inline int SingleLinkedList<data_type>::get_size() {
	return this->size;
}
template<class data_type> inline Node<data_type> * SingleLinkedList<data_type>::get_head() {
	return this->ptr_head;
}
template<class data_type> inline Node<data_type> * SingleLinkedList<data_type>::get_tail() {
	return this->ptr_tail;
}
template<class data_type> inline bool SingleLinkedList<data_type>::is_empty() {
	return this->ptr_head == nullptr;
}

template<class data_type> inline void SingleLinkedList<data_type>::add_head(data_type _data) {
	Node<data_type> * ptr_add = new Node<data_type>(_data);
	if (is_empty()) {
		this->ptr_head = ptr_add;
		this->ptr_tail = ptr_add;
	}
	else {
		ptr_add->ptr_next = this->ptr_head;
		this->ptr_head = ptr_add;
	}
	this->size++;
}
template<class data_type> inline void SingleLinkedList<data_type>::add_tail(data_type _data) {
	Node<data_type> * ptr_add = new Node<data_type>(_data);
	if (is_empty()) {
		this->ptr_head = ptr_add;
		this->ptr_tail = ptr_add;
	}
	else {
		this->ptr_tail->ptr_next = ptr_add;
		this->ptr_tail = ptr_add;
	}
	this->size++;
}
template<class data_type> inline void SingleLinkedList<data_type>::add_previous(Node<data_type> * position, data_type _data) {
	Node<data_type> * ptr_add = new Node<data_type>(_data);
	if (is_empty())
		add_head(ptr_add);
	else {
		Node<data_type> * ptr_temp = search_previous(position);
		add_next(ptr_temp, position->data);
	}
}
template<class data_type> inline void SingleLinkedList<data_type>::add_next(Node<data_type> * position, data_type _data) {
	Node<data_type> * ptr_add = new Node<data_type>(_data);
	if (position != nullptr) {
		ptr_add->ptr_next = position->ptr_next;
		position->ptr_next = ptr_add;
		if (position == this->ptr_tail)
			this->ptr_tail = ptr_add;
	}
	else add_head(ptr_add);
	this->size++;
}
template<class data_type> inline void SingleLinkedList<data_type>::insert_at(int position, data_type _data) {
	if (is_empty() || position <= 0)
		add_head(_data);
	else if (position > get_size())
		add_tail(_data);
	else {
		Node<data_type> * ptr_temp = this->ptr_head;
		for (int i = 0; i < position - 1; i++)
			ptr_temp = ptr_temp->ptr_next;
		Node<data_type> * ptr_add = new Node<data_type>(_data);
		ptr_add->ptr_next = ptr_temp->ptr_next;
		ptr_temp->ptr_next = ptr_add;
		this->size++;
	}
}

template<class data_type> inline Node<data_type> * SingleLinkedList<data_type>::search(data_type _data) {
	Node<data_type> * ptr_search = this->ptr_head;
	for (; ptr_search != nullptr && ptr_search->data != _data; ptr_search = ptr_search->ptr_next);
	return ptr_search;
}
template<class data_type> inline Node<data_type> * SingleLinkedList<data_type>::search_previous(Node<data_type> * ptr_node) {
	Node<data_type> * ptr_search = this->ptr_head;
	if (ptr_search == ptr_node)
		return nullptr;
	for (; ptr_search != nullptr && ptr_search->ptr_next != ptr_node; ptr_search = ptr_search->ptr_next);
	return ptr_search;
}

template<class data_type> inline void SingleLinkedList<data_type>::remove_head() {
	if (this->ptr_head != nullptr) {
		Node<data_type> * ptr_remove = this->ptr_head;
		this->ptr_head = this->ptr_head->ptr_next;
		delete ptr_remove;
		if (this->ptr_head == nullptr)
			this->ptr_tail = nullptr;
		this->size--;
	}
}
template<class data_type> inline void SingleLinkedList<data_type>::remove_tail() {
	if (this->ptr_head == nullptr)
		return;
	Node<data_type> * ptr_remove = this->ptr_tail;
	this->ptr_tail = search_previous(this->ptr_tail);
	delete ptr_remove;
	if (this->ptr_tail != nullptr)
		this->ptr_tail->ptr_next = nullptr;
	else
		this->ptr_head = nullptr;
	this->size--;
}
template<class data_type> inline void SingleLinkedList<data_type>::remove_after(Node<data_type> * ptr_node) {
	Node<data_type> * ptr_remove;
	if (ptr_node != nullptr) {
		ptr_remove = ptr_node->ptr_next;
		if (ptr_remove != nullptr) {
			if (ptr_remove == this->ptr_tail)
				this->ptr_tail = ptr_node;
			ptr_node->ptr_next = ptr_remove->ptr_next;
			delete ptr_remove;
		}
	}
	else
		remove_head();
	this->size--;
}
template<class data_type> inline void SingleLinkedList<data_type>::remove_first_of(data_type _data) {
	Node<data_type> * ptr_walker = this->ptr_head, * ptr_temp = nullptr;
	if (ptr_walker == this->ptr_head && ptr_walker != nullptr && ptr_walker->data == _data) {
		remove_head();
		return;
	}
	for (; ptr_walker != nullptr && ptr_walker->data != _data; ptr_walker = ptr_walker->ptr_next)
		ptr_temp = ptr_walker;
	if (ptr_walker == nullptr)
		return;
	if (ptr_temp != nullptr) {
		if (ptr_walker == this->ptr_tail) {
			this->ptr_tail = ptr_temp;
			this->ptr_tail->ptr_next = nullptr;
		}
		ptr_temp->ptr_next = ptr_walker->ptr_next;
		delete ptr_walker;
		this->size--;
	}
}
template<class data_type> inline void SingleLinkedList<data_type>::remove_elements_of(data_type _data) {
	Node<data_type> * ptr_previous = nullptr;
	for (Node<data_type> * ptr_walker = this->ptr_head; ptr_walker != nullptr; ) {
		if (ptr_walker->data == _data) {
			ptr_previous == nullptr ? this->ptr_head = ptr_walker->ptr_next : ptr_previous->ptr_next = ptr_walker->ptr_next;
			Node<data_type> * ptr_remove = ptr_walker;
			ptr_walker = ptr_walker->ptr_next;
			delete ptr_remove;
			this->size--;
		}
		else {
			ptr_previous = ptr_walker;
			ptr_walker = ptr_walker->ptr_next;
		}
		if (ptr_walker == nullptr)
			this->ptr_tail = ptr_previous;
	}
}

template<class data_type> inline Node<data_type> * SingleLinkedList<data_type>::find_middle_node() {
	// Check list with less than or equal to 1 node, return current node
	if (this->ptr_head == nullptr || this->ptr_head->ptr_next == nullptr)
		return ptr_head;

	Node<data_type> * ptr_hare = this->ptr_head;
	Node<data_type> * ptr_tortoise = this->ptr_head;

	while (ptr_hare != nullptr && ptr_hare->ptr_next != nullptr) {
		ptr_hare = ptr_hare->ptr_next->ptr_next; // 2 steps forward
		ptr_tortoise = ptr_tortoise->ptr_next;   // 1 step forward
	}

	return ptr_tortoise;
}

template<class data_type> inline void SingleLinkedList<data_type>::reverse() {
	// Check list with less than or equal to 1 node
	if (this->ptr_head == nullptr || this->ptr_head->ptr_next == nullptr)
		return;

	this->ptr_tail = this->ptr_head;
	this->ptr_head = this->ptr_head->ptr_next;
	this->ptr_tail->ptr_next = nullptr;

	Node<data_type> * ptr_walker = nullptr;
	Node<data_type> * ptr_previous = ptr_tail;

	while (this->ptr_head != nullptr) {
		ptr_walker = this->ptr_head;
		this->ptr_head = this->ptr_head->ptr_next;
		ptr_walker->ptr_next = ptr_previous;
		ptr_previous = ptr_walker;
	}
	this->ptr_head = ptr_walker;
}
template<class data_type> inline void SingleLinkedList<data_type>::selection_sort() {
	Node<data_type> * ptr_min, * ptr_first, * ptr_second;
	for (ptr_first = this->ptr_head; ptr_first != nullptr; ptr_first = ptr_first->ptr_next) {
		ptr_min = ptr_first;
		for (ptr_second = ptr_first->ptr_next; ptr_second != nullptr; ptr_second = ptr_second->ptr_next)
			if (ptr_second->data < ptr_min->data)
				ptr_min = ptr_second;
		swap(ptr_min->data, ptr_first->data);
	}
}
template<class data_type> inline void SingleLinkedList<data_type>::clear() {
	while (this->ptr_head != nullptr)
		remove_head();
}
template<class data_type> inline void SingleLinkedList<data_type>::show_elements_from(Node<data_type> * ptr_node) {
	for (Node<data_type> * ptr_walker = ptr_node; ptr_walker != nullptr; ptr_walker = ptr_walker->ptr_next)
		std::cout << ptr_walker->data << ' ';
}
template<class data_type> inline void SingleLinkedList<data_type>::show_list() {
	for (Node<data_type> * ptr_walker = this->ptr_head; ptr_walker != nullptr; ptr_walker = ptr_walker->ptr_next)
		std::cout << ptr_walker->data << ' ';
}
