#pragma once

#include<iostream>
#include"Exception.h"
using namespace std;

template<class T>
class Node {
public:
	T data;
	Node<T>* link;
};

template<class T>
class LinkedQueue {
public:
	LinkedQueue() { front = rear = 0; }
	~LinkedQueue();
	bool IsEmpty()const
	{
		return ((front) ? false : true);
	}
	bool IsFull()const;
	T First()const;
	T Last()const;
	LinkedQueue<T>& Add(const T& x);
	LinkedQueue<T>& Delete(T& x);
	int QueueSize();
private:
	Node<T>* front;
	Node<T>* rear;
};

template<class T>
LinkedQueue<T>::~LinkedQueue()
{
	Node<T>* next;
	while (front)
	{
		next = front->link;
		delete front;
		front = next;
	}
}

template<class T>
bool LinkedQueue<T>::IsFull()const
{
	Node<T>* p;
	try
	{
		p = new Node<T>;
		delete p;
		return false;
	}
	catch (NoMem)
	{
		return true;
	}
}

template<class T>
T LinkedQueue<T>::First()const
{
	if (IsEmpty())
		throw OutOfBounds();
	return front->data;
}

template<class T>
T LinkedQueue<T>::Last()const
{
	if (IsEmpty())
		throw OutOfBounds();
	return rear->data;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x)
{
	Node<T>* p = new Node<T>;
	p->data = x;
	p->link = 0;
	if (front)
		rear->link = p;
	else
		front = p;
	rear = p;
	return *this;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Delete(T& x)
{
	if (IsEmpty())
		throw OutOfBounds();
	x = front->data;
	Node<T>* p = front;
	front = front->link;
	delete p;
	return *this;
}

template<class T>
int LinkedQueue<T>::QueueSize()
{
	if (IsEmpty())
		return 0;
	int queuesize = 1;
	Node<T>* p = front;
	while (p)
	{
		p = p->link;
		queuesize++;
	}
	return queuesize;
}
