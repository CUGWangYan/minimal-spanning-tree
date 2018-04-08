#pragma once
#include <iostream>
using namespace std;
//const int DefaultSize = 50;
class UFSets {
private:
	int size;
	int *parent;
public:
	UFSets(int sz = DefaultSize);
	~UFSets() { delete[]parent; }
	void Union(int Root1, int Root2);
	int Find(int x);
};
UFSets::UFSets(int sz) {
	size = sz;
	parent = new int[size];
	for (int i = 0; i < size; i++) parent[i] = -1;
}
int UFSets::Find(int x) {
	while (parent[x] >= 0) x = parent[x];
	return x;
}
void UFSets::Union(int Root1, int Root2) {
	parent[Root1] += parent[Root2];
	parent[Root2] = Root1;
}

