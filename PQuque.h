#pragma once
#include <assert.h>
#include <iostream>
#include <stdlib.h>
const int DefaultPQSize = 50;
template<class T>
class PQueue {
protected:
	T *pqelements;
	int count;
	int maxSize;
	void Adjust();
public:
	PQueue(int sz = DefaultPQSize);
	~PQueue() { delete[]pqelements; }
	bool Insert(const T&x);
	bool RemoveMin(T&x);
	bool getFront(T&x)const;
	void makeEmpty() { count = 0; }
	bool IsEmpty()const {
		return(count == 0) ? true : false;
	}
	bool IsFull()const {
		return(count == maxSize) ? true : false;
	}
	int getSize()const {
		return count;
	}
};
template<class T>
PQueue<T>::PQueue(int sz) :maxSize(sz), count(0) {
	pqelements = new T[maxSize];
	assert(pqelements != nullptr);
}
template<class T>
bool PQueue<T>::Insert(const T&x) {
	if (count == maxSize)return false;
	pqelements[count] = x;
	count++;
	Adjust();
}
template<class T>
void PQueue<T>::Adjust() {
	T temp = pqelements[count - 1];
	int j;
	for (j = count - 2; j >= 0; j--) {
		if (pqelements[j] <= temp)break;
		else pqelements[j + 1] = pqelements[j];
		pqelements[j + 1] = temp;
	}
}
template<class T>
bool PQueue<T>::RemoveMin(T&x) {
	if (count == 0) return false;
	x = pqelements[0];
	for (int i = 1; i < count; i++) {
		pqelements[i - 1] = pqelements[i];
	}
	count--;
	return true;
}
template<class T>
bool PQueue<T>::getFront(T&x)const {
	if (count == 0)return false;
	else { x = pqelements[0]; return true; }
}