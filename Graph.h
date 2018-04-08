#pragma once
const int DefaultVertices = 50;
#include <iostream>
#include <limits>
using namespace std;
template<class T,class E>
class Graph {
protected:
	int maxVertices;
	int numEdges;
	int numVertices;
public:
	virtual int getVertexPos(const T vertex)=0;
	const E maxWeight =numeric_limits<E>::max();///无穷大
	Graph(int sz = DefaultVertices) {
		maxVertices = sz;
		numVertices = 0;
		numEdges = 0;
	}
	~Graph() {}
	bool GraphEmpty()const {
		if (numEdges == 0)return true;
		else return false;
	}
	bool GraphFull()const {
		if (numVertices == maxVertices || numEdges == = maxVertices*(maxVertices - 1) / 2) return true;
		else return false;
	}
	int NumberOfVertices() { return numVertices; }
	int NumberOfEdges() { return numEdges; }
	virtual T getValue(int i)=0;
	virtual E getWeight(int v1, int v2)=0;
	virtual int getFirstNeighbor(int v)=0;
	virtual int getNextNeighbor(int v, int w)=0;
	virtual bool insertVertex(const T&vertex)=0;
	virtual bool insertEdge(int v1, int v2, E cost)=0;
	virtual bool removeVertex(int v)=0;
	virtual bool removeEdge(int v1, int v2)=0;
};
template<class T,class E>
struct Edge {
	int dest;
	E cost;
	Edge<T, E> *link;
	Edge() {}
	Edge(int num, E weight) :dest(num), cost(weight), link(nullptr) {}
	bool operator!=(Edge<T, E>&R)const {
		return (dest != R.dest) ? true : false;
	}
};
template<class T,class E>
struct Vertex {
	T data;
	Edge<T, E> *adj;
};
template<class T,class E>
class Graphlnk :public Graph<T, E> {
	template<class T,class E> friend istream&operator >> (istream&in, Graphlnk<T, E>&G);
	template<class T, class E>friend ostream&operator<<(ostream&out, Graphlnk<T, E>&G);
private:
	Vertex<T, E> *NodeTable;
	int getVertexPos(const T vertex) {
		for (int i = 0; i < numVertices; i++)
			if (NodeTable[i].data == vertex) return i;
		return -1;
	}
public:
	Graphlnk(int sz = DefaultVertices);
	~Graphlnk();
	T getValue(int i) { return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0; }
	E getWeight(int v1, int v2);
	bool insertVertex(const T&vertex);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
	bool insertEdge(int v1, int v2, E cost);
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
};
template<class T,class E>
Graphlnk<T, E>::Graphlnk(int sz) {
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	NodeTable = new Vertex<T, E>[maxVertices];
	if (NodeTable == nullptr) { cerr << "wrong" << endl; exit(1); }
	for (int i = 0; i < maxVertices; i++) NodeTable[i].adj = nullptr;
}
template<class T,class E>
Graphlnk<T, E>::~Graphlnk() {
	for (int i = 0; i < numVertices; i++) {
		Edge<T, E> *p = NodeTable[i].adj;
		while(p != nullptr) {
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;
}
template<class T,class E>
int Graphlnk<T, E>::getFirstNeighbor(int v) {
	if (v != -1) {
		Edge<T, E> *p = NodeTable[v].adj;
		if (p != nullptr)return p->dest;
	}
	return -1;
}
template<class T,class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w) {
	if (v != -1) {
		Edge<T, E> *p = NodeTable[v].adj;
		while (p != nullptr&&p->dest != w)p = p->link;
		if (p != nullptr&&p->link != nullptr)
			return p->link->dest;
	}
	return -1;
}
template<class T,class E>
E Graphlnk<T, E>::getWeight(int v1, int v2) {
	if (v1 != -1 && v2 != -1) {
		Edge<T, E> *p = NodeTable[v1].adj;
		while(p != nullptr&&p->dest != v2)
			p = p->link;
		if (p != nullptr) return p->cost;
	}
	return 0;//表示边不存在
}
template<class T,class E>
bool Graphlnk<T, E>::insertVertex(const T&vertex) {
	if (numVertices == maxVertices)return false;
	NodeTable[numVertices].data = vertex;
	numVertices++;
	return true;
}
template<class T,class E>
bool Graphlnk<T, E>::removeVertex(int v) {
	if (numVertices == 1 || v < 0 || v >= numVertices)return false;
	Edge<T, E> *p, *s, *t;
	int k;
	while (NodeTable[v].adj != nullptr) {
		p = NodeTable[v].adj;
		k = p->dest;
		s = NodeTable[k].adj;
		t = nullptr;
		while (s != nullptr&&s->dest != v) {
			t = s;
			s = s->link;
		}
		if (s != nullptr) {
			if (t == nullptr) NodeTable[k].adj = s->link;
			else t->link = s->link;
			delete s;
		}
		NodeTable[v].adj = p->link;
		delete p;
		numEdges--;
	}
	numVertices--;
	NodeTable[v].data = NodeTable[numVertices].data;
	p = NodeTable[v].adj = NodeTable[numVertices].adj;
	while (p != nullptr) {
		s = NodeTable[p->dest].adj;
		while(s!=nullptr)
			if (s->dest == numVertices) { s->dest = v; break; }
			else s = s->link;
	}
	return true;
}
template<class T,class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight) {
	if (v1 >= 0 && v1 < numVertices&&v2>=0 && v2 < numVertices) {
		Edge<T, E> *q, *p = NodeTable[v1].adj;
		while (p != nullptr&&p->dest != v2)
			p = p->link;
		if (p != nullptr) return false;
		p = new Edge<T, E>;
		q = new Edge<T, E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
	return 0;
}
template<class T,class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2) {
	if (v1 != -1 && v2 != -1) {
		Edge<T, E>*p = NodeTable[v1].adj, *q = nullptr, *s = p;
		while (p != nullptr&&p->dest != v2) {
			q = p; p = p->link;
		}
		if (p != nullptr) {
			if (p == s)NodeTable[v1].adj = p->link;
			else q->link = p->link;
			delete p;
		}
		else return false;
		p = NodeTable[v2].adj;
		q = nullptr, s = p;
		while (p->dest != v1) {
			q = p; p = p->link;
		}
		if (p == s)NodeTable[v2].adj = p->link;
		else q->link = p->link;
		delete p;
	}
}
template<class T,class E>
istream& operator >> (istream& in, Graphlnk<T, E>&G) {
	int i, j, k, n, m;
	T e1, e2;
	E weight;
	in >> n >> m;
	for (i = 0; i < n; i++) {
		in >> e1;
		G.insertVertex(e1);
	}
	i = 0;
	while (i < m) {
		in >> e1 >> e2 >> weight;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if (j == -1 || k == -1)cout << "wrong" << endl;
		else {
			G.insertEdge(j, k, weight); i++;
		}
	}
	return in;
}
template<class T,class E>
ostream& operator<<(ostream& out, Graphlnk<T, E>&G) {
	int i, j, n, m;
	T e1, e2;
	E w;
	n = G.NumberOfVertices();
	m = G.NumberOfEdges();
	out << n << "," << m << endl;
	for (i = 0; i < n; i++) {
		w = G.getWeight(i, j);
		if (w > 0 && w < maxWeight) {
			e1 = G.getValue(i);
			e2 = G.getValue(j);
			out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
		}
	}
	return out;
}