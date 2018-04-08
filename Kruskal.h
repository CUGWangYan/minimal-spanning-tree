#pragma once
#include "MinHeap.h"
#include "UFsets.h"
#include "Graph.h"
#include "MinSpanTree.h"
template<class T,class E>
void Kruskal(Graph<T, E>&G, MinSpanTree<T, E>&MST) {
	MSTEdgeNode<T, E>ed;
	int u, v, count;
	int n = G.NumberOfVertices();
	int m = G.NumberOfEdges();
	MinHeap<MSTEdgeNode<T, E> > H(m);
	UFSets F(n);
	for(u=0;u<n;u++)
		for(v=u+1;v<n;v++)
			if (G.getWeight(u,v)!=0) {
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}
	count = 1;
	while (count < n) {
		H.RemoveMin(ed);
		u = F.Find(ed.tail);
		v = F.Find(ed.head);
		if (u != v) {
			F.Union(u, v);
			MST.Insert(ed);
			count++;
		}
	}
}
