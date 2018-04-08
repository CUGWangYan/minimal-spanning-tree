#pragma once
#include <iostream>
using namespace std;
const int DefaultSize = 50;
template<class T, class E>
struct MSTEdgeNode {
	int tail, head;
	E key;
	MSTEdgeNode() :tail(-1), head(-1), key(0) {};
	bool operator<=(MSTEdgeNode<T, E>&R) { return key <= R.key; }
	bool operator>(MSTEdgeNode<T, E>&R) { return key > R.key; }
};
template<class T, class E>
class MinSpanTree {
protected:
	MSTEdgeNode<T, E> *edgevalue;
	int maxSize, n;
public:
	MinSpanTree(int sz = DefaultSize - 1) :maxSize(sz), n(0) {
		edgevalue = new MSTEdgeNode<T, E>[sz];
	}
	void Insert(MSTEdgeNode<T, E>& item) {
		edgevalue[n++] = item;
	}
	friend ostream& operator<<(ostream&out, MinSpanTree<T, E>&tree) {
		for (int i = 0; i < tree.n; i++) {
			out << tree.edgevalue[i].head + 1 << "-->" << tree.edgevalue[i].tail + 1 << endl;
		}
		return out;
	}
};