#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
#include <limits>
#include "Leftist_heap.h"
#include "Node_struct.h"

class Weighted_graph {
private:
	double** graph;
	int graphSize;
	int *nodeDegree;//Stores the degree of each node
	int nodeEdgeCount;

	static const double INF;

public:
	Weighted_graph(int = 50);
	~Weighted_graph();

	int degree(int) const;
	int edge_count() const;
	double adjacent(int, int) const;
	double distance(int, int);

	void insert(int, int, double);

	friend std::ostream &operator<<(std::ostream &, Weighted_graph const &);
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

//Constructor
Weighted_graph::Weighted_graph(int n) {
	//Initialize the adjacency matrix
	graphSize = n;
	nodeEdgeCount = 0;


	nodeDegree= new int[graphSize];
	for (int i = 0; i < graphSize; i++) {
		nodeDegree[i] = 0;
	}

	graph = new double*[graphSize];
	for (int i = 0; i < graphSize; ++i)
		graph[i] = new double[graphSize];

	//Set the adjaceny matric
	for (int i = 0; i < graphSize; i++) {
		for (int j = 0; j < graphSize; j++) {
			if (i == j) {
				graph[i][j] = 0;
			}
			else {
				graph[i][j] = INF;
			}
		}
	}
}

//Deconstructor
Weighted_graph::~Weighted_graph() {
	//Delete the adjacency matrix
	for (int i = 0; i < graphSize; i++) {
		delete[] graph[i];
	}
	delete[] graph;
	delete[] nodeDegree;
}

//Accessors
int Weighted_graph::degree(int n) const{
	if ((n > graphSize) || (n < 0)) {
		throw illegal_argument();
	}
	return nodeDegree[n];
}
int Weighted_graph::edge_count() const{
	return nodeEdgeCount;
}

double Weighted_graph::adjacent(int m, int n) const{
	if ((m >= graphSize)||(n >= graphSize)||(m<0)||(n<0)) {
		throw illegal_argument();
	}
	else{
		return graph[m][n];
	}
}
double Weighted_graph::distance(int startNode, int endNode){
	
	if ((startNode >= graphSize) || (endNode >= graphSize) || (startNode<0) || (endNode<0)) {
		throw illegal_argument();
	}
	else if (startNode == endNode) {
		return 0;
	}

	Leftist_heap MyHeap;
	//create the leftist heap using adjacency matrix
	//run djekstra on the leftist heap
	//Store the heap in cache to be used later as long as new insert is not called
	//dijkstra(graph, n);
	double *dist = new double[graphSize];
	dist[startNode] = 0;

	for (int v = 0; v < graphSize; v++) {
		if (v != startNode) {
		dist[v] = INF;
		}

		Node_struct myStruct = Node_struct(v, dist[v]);
		MyHeap.push(myStruct);
	}

	while (!MyHeap.empty()) {
		
		Node_struct rootStruct=MyHeap.pop();//remove top note and return root
		//std::cout << rootStruct.Key<<"\n";
		//std::cout << rootStruct.Dist << "\n";
		//std::cout << MyHeap->size() <<"\n";
		//std::cout <<"\n";

		if ((rootStruct.Key == endNode)) {
			delete[] dist;
			return rootStruct.Dist;
		}

		for (int i = 0; i < graphSize; i++) {
			double val = dist[rootStruct.Key]+ graph[rootStruct.Key][i];
			if (val < dist[i]) {
				dist[i] = val;
				Node_struct myStruct = Node_struct(i, val);
				MyHeap.push(myStruct);
			}
		}
	}
	int distance = dist[endNode];
	delete[] dist;
	return distance;
}

void Weighted_graph::insert(int m, int n, double w) {
	if ((w <= 0)||(m>=graphSize)||(n>=graphSize)||(m<0)||(n<0)||(m==n)){
		throw illegal_argument();
	}
	else if (graph[m][n] == INF) {
		graph[m][n] = w;
		graph[n][m] = w;
		nodeDegree[m] += 1;
		nodeDegree[n] += 1;
		nodeEdgeCount += 1;
	}
	else {
		graph[m][n] = w;
		graph[n][m] = w;
	}
}

std::ostream &operator<<(std::ostream &out, Weighted_graph const &graph) {
	return out;
}
#endif