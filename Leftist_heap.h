#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#include "Leftist_node.h"
#include "Node_struct.h"


class Leftist_heap {
private:
	Leftist_node *root_node;
	int heap_size;

public:
	Leftist_heap();
	~Leftist_heap();

	void swap(Leftist_heap &heap);

	bool empty() const;
	int size() const;
	int null_path_length() const;
	Node_struct top() const;
	int count(Node_struct const &) const;

	void push(Node_struct const &);
	Node_struct pop();
	Node_struct getRoot();
	Node_struct getLeftNode();
	Node_struct getRightNode();
	void clear();

	friend std::ostream &operator<<(std::ostream &, Leftist_heap const &);
};

//Constructor
Leftist_heap::Leftist_heap() :
	root_node(0),
	heap_size(0) {
	// does nothing
}


//Deconstructor
Leftist_heap::~Leftist_heap() {
	clear();
}

//Swapfunction??
void Leftist_heap::swap(Leftist_heap &heap) {
	std::swap(root_node, heap.root_node);
	std::swap(heap_size, heap.heap_size);
}

//Output function
std::ostream &operator<<(std::ostream &out, Leftist_heap const &heap) {
	return out;
}

bool Leftist_heap::empty() const{
	if (heap_size==0) {
		return 1;
	}
	else {
		return 0;
	}
}

int Leftist_heap::size() const{
	return heap_size;
}

int Leftist_heap::null_path_length() const{
//	int length= root_node.null_path_length();
	if ((root_node != 0)&&(heap_size!=0)) {
		return root_node->null_path_length();
	}
	else {
		return -1;
	}
}

int Leftist_heap::count(const Node_struct &obj) const{
	//Branch through the tree to find the number of instances within the entire tree
	int instances=root_node->count(obj);
	return instances;

}

Node_struct Leftist_heap::top() const{
	if (root_node != 0) {
		return root_node->retrieve();
	}
	else {
		throw underflow();
	}
}

//Create new leftist node
//insert element by calling node.push(
//use root_node as second argument
//use Root? as first argument
void Leftist_heap::push(const Node_struct & obj) {
	Leftist_node * myNode= new Leftist_node (obj);
	root_node->push(myNode, root_node);
	heap_size++;
}

//Delete last element in heap and node
//If tree empty throw underflow excpetion
//if not empty
	//Left subtree of root is made the root
	//right subtree of origional root node if pushed into the new node
Node_struct Leftist_heap::pop() {
	if ((root_node != 0) && (empty() == 0)) {
		Node_struct leastElement = root_node->retrieve();
		Leftist_node * temp_node = root_node;
		root_node = root_node->left();
		root_node->push(temp_node->right(), root_node);
		delete temp_node;
		heap_size--;
		return leastElement;
	}
	else {
		throw underflow();
	}
}

Node_struct Leftist_heap::getRoot() {
	if ((root_node != 0) && (empty() == 0)) {
		Node_struct leastElement = root_node->retrieve();
		return leastElement;
	}
	else {
		throw underflow();
	}
}
Node_struct Leftist_heap::getLeftNode() {

	if ((root_node->left() != 0) && (empty() == 0)) {
		Node_struct leftElement = root_node->left()->retrieve();
		return leftElement;
	}
	else {
		Node_struct tempStruct = Node_struct(-1, 0);
		return tempStruct;
	}
}
Node_struct Leftist_heap::getRightNode() {
	if ((root_node->right() != 0) && (empty() == 0)) {
		Node_struct rightElement = root_node->retrieve();
		return rightElement;
	}
	else {
		Node_struct tempStruct = Node_struct(-1, 0);
		return tempStruct;
	}
}

//Call clear on the root node and reset the root node and heap size
void Leftist_heap::clear() {
	if (heap_size != 0) {
		root_node->clear();
		heap_size = 0;
	}
}
#endif