#ifndef QUEUE_H
#define QUEUE_H
#include "Deque.h"

template <typename T>
class Queue
{
private:
	Deque<T> queue;
public:
	Queue() {}
	~Queue() {}
	string push(const T& i)
	{
		queue.push_back(i);
		return "OK";
	}
	void pop()
	{
		queue.pop_front();
	}
	T& top()
	{
		return queue.front();
	}
	size_t size()
	{
		return queue.size();
	}
	T& at(size_t i)
	{
		return queue.at(i);
	}
	string toString() const
	{
		return queue.toString();
	}
	int front_index()
	{
		return queue.getfrontIndex();
	}
	int getCap()
	{
		return queue.getCapacity();
	}
};
#endif
