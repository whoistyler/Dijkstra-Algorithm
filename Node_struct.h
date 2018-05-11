#ifndef NODE_STRUCT_H
#define NODE_STRUCT_H

struct Node_struct
{
	double Dist;
	int Key;
	Node_struct(int key, double dist) {
		Key = key;
		Dist = dist;
	}
};

#endif