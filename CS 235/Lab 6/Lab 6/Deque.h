#ifndef DEQUE_H
#define DEQUE_H
#include "DequeInterface.h"
#include <sstream>

using namespace std;

template<typename T>
class Deque : public DequeInterface<T>

{
private:

	size_t capacity = 0;
	size_t num_items = 0;
	size_t front_index = 0;
	size_t rear_index = 0;
	T * the_data = nullptr;

public:

	Deque(void) : 
		capacity(DEFAULT_CAPACITY),
		num_items(0),
		front_index(0),
		rear_index(DEFAULT_CAPACITY - 1),
		the_data(new T[DEFAULT_CAPACITY]) {}

	~Deque() 
	{
		delete [] the_data;/*-*/
	}

	/** Insert item at front of deque */
	void push_front(const T& value) 
	{
		if (num_items == capacity)
		{
			reallocate();
		}
		num_items++;
		front_index = (front_index - 1) % capacity;
		the_data[front_index] = value;
	}

	/** Insert item at rear of deque */
	void push_back(const T& value) 
	{
		if (num_items == capacity)
		{
			reallocate();
		}
		num_items++;
		rear_index = (rear_index + 1) % capacity;
		the_data[rear_index] = value;
	}

	/** Remove the front item of the deque */
	void pop_front(void) 
	{
		front_index = (front_index + 1) % capacity;
		num_items--;
	}

	/** Remove the rear item of the deque */
	void pop_back(void) 
	{
		rear_index = (rear_index - 1) % capacity;
		num_items--;
	}

	/** Return the front item of the deque (Do not remove) */
	T& front(void) { return the_data[front_index]; }

	/** Return the rear item of the deque (Do not remove) */
	T& back(void) { return the_data[rear_index]; }

	/** Return the number of items in the deque */
	size_t size(void) const { return num_items; }

	/** Return true if deque is empty */
	bool empty(void) const { return num_items == 0; }

	/** Return item in deque at index (0 based) */
	T& at(size_t index) { return the_data[index]; }

	/** Return the deque items */
	string toString(void) const 
	{ 
		ostringstream os;
		for (size_t i = front_index; i < num_items; i++)
		{
			os << the_data[i % capacity] << " ";
		}
		return os.str(); 
	}

	void reallocate(void) 
	{
		size_t new_capacity = 2 * capacity;
		T* new_data = new T[new_capacity];
		size_t j = front_index;
		for (size_t i = 0; i < num_items; i++)
		{
			new_data[i] = the_data[j];
			j = (j + 1) % capacity;
		}
		front_index = 0;
		rear_index = num_items - 1;
		capacity = new_capacity;
		swap(the_data, new_data);
		delete[] new_data;
	}

	int getfrontIndex()
	{
		return front_index;
	}
	int getCapacity()
	{
		return capacity;
	}

};
#endif
