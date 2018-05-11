#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
#include "Node_struct.h"

#ifndef nullptr
#define nullptr 0
#endif

class Leftist_node {
private:
	Node_struct element;
	Leftist_node *left_tree;
	Leftist_node *right_tree;
	int heap_null_path_length;
	int tempCount;

public:
	Leftist_node(Node_struct);

	Node_struct retrieve() const;
	int retrieveKey() const;
	double retrieveDist() const;
	bool empty() const;
	Leftist_node *left() const;
	Leftist_node *right() const;
	int count(Node_struct) const;
	int null_path_length() const;

	void push(Leftist_node *, Leftist_node *&);
	void clear();
};

//Constructor
Leftist_node::Leftist_node(Node_struct myNode) :
	element(myNode),
	left_tree(nullptr),
	right_tree(nullptr),
	heap_null_path_length(0) {
}


bool Leftist_node::empty() const {
	return (this == nullptr);
}

Node_struct Leftist_node::retrieve() const{
	return element;
}
double Leftist_node::retrieveDist() const {
	return element.Dist;
}
int Leftist_node::retrieveKey() const {
	return element.Key;
}

Leftist_node* Leftist_node::left() const {
	return this->left_tree;
}

Leftist_node* Leftist_node::right() const {
	return this->right_tree;
}

int Leftist_node::null_path_length() const {
	if (this != nullptr) {
		return heap_null_path_length;
	}
	else {
		return -1;
	}
}

int Leftist_node::count(Node_struct obj) const{
	int count = 0;
	if(this == NULL) {
		return count;
	}
	else {
		if (left_tree != nullptr) {
			count+= left_tree->count(obj);
		}
		if (right_tree != nullptr) {
			count += right_tree->count(obj);
		}
		if (element.Dist == obj.Dist) {
			count++;
		}
	}
	return count;
}

void Leftist_node::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this) {
	if (new_heap == nullptr) {
		return;
	}
	else {//If node is not null insert
		if (this == nullptr) {
			ptr_to_this = new_heap;
			return;
		}
		if (ptr_to_this->element.Dist <= new_heap->element.Dist) {
			right_tree->push(new_heap, right_tree);

			if ((left_tree == nullptr) && (right_tree != nullptr)) {
				std::swap(ptr_to_this->right_tree, ptr_to_this->left_tree);
			}
			else if ((left_tree != nullptr) && (right_tree != nullptr)) {
				heap_null_path_length = std::min(1 + left_tree->null_path_length(), right_tree->null_path_length() + 1);
				if ((ptr_to_this->left_tree->null_path_length()) < (ptr_to_this->right_tree->null_path_length())) {
					std::swap(ptr_to_this->right_tree, ptr_to_this->left_tree);
				}
			}
		}
		else {
			ptr_to_this = new_heap;
			new_heap->push(this, ptr_to_this);

		}
	}
}

void Leftist_node::clear() {
	if (this == nullptr) {
		return;
	}
	else {
		left_tree->clear();

		right_tree->clear();
		delete this;
	}
}
#endif