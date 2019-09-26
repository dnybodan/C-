#ifndef VECTOR_H
#define VECTOR_H
#include "Deque.h"

template<typename T>
class Vector
{
private: 
	Deque<T> vector;
public:
	Vector() {}
	~Vector() {}
	void push_back(const T& i)
	{
		vector.push_back(i);
	}
	void pop_back()
	{
		vector.pop_back();
	}
	T& back()
	{
		return vector.back();
	}
	size_t size()
	{
		return vector.size();
	}
	T& at(size_t i)
	{
		return vector.at(i);
	}
	string toString() const
	{
		return vector.toString();
	}
};
#endif
