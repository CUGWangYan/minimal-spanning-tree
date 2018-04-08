#pragma once
#include "MinHeap.h"
#include "MinSpanTree.h"
#include "Graph.h"
template<class T,class E>
void Prim(Graph<T, E>&G, const T u0, MinSpanTree<T, E>&MST) {
	MSTEdgeNode<T, E>ed;
	int i,v, count;
	int n = G.NumberOfVertices();
	int m = G.NumberOfEdges();
	int u = G.getVertexPos(u0);
	MinHeap<MSTEdgeNode<T, E> > H(m);
	bool *Vmst = new bool[n];
	for (i = 0; i < n; i++) Vmst[i] = false;
	Vmst[u] = true;
	count = 1;
	do {
		v = G.getFirstNeighbor(u);
		while (v != -1) {
			if (Vmst[v] == false) {
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u, v);
		}
		while (H.IsEmpty() == false && count < n) {
			H.RemoveMin(ed);
			if (Vmst[ed.head] == false) {
				MST.Insert(ed);
				u = ed.head;
				Vmst[u] = true;
				count++;
				break;
			}
	}
	} while (count < n);
};