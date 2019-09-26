#ifndef STACK_H
#define STACK_H
#include "Deque.h"

template<typename T>
class Stack
{
private:
	Deque<T> stack;
public:
	Stack() {}
	~Stack() {}
	string push(const T& i)
	{
		stack.push_back(i);
		return "OK";
	}
	void pop()
	{
		stack.pop_back();
	}
	T& top()
	{
		return stack.back();
	}
	size_t size()
	{
		return stack.size();
	}
	T& at(size_t i)
	{
		return stack.at(i);
	}
	string toString() const
	{
		return stack.toString();
	}
};
#endif
