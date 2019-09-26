#ifndef STATION_H
#define STATION_H
#include "Vector.h"
#include "Queue.h"
#include "Stack.h"

template<typename T>
class Station

{
private:
	Vector<T> train;
	Stack<T> stack;
	Queue<T> queue;
	T turnTableCar = 0;
	bool empty = true;
public:
	Station() {}
	~Station() {}
	string addCar(const T& newCar)
	{
		if (empty == true)
		{
			turnTableCar = newCar;
			empty = false;
			return "OK";
		}
		else
		{
			return "Turntable occupied!";
		}
	}
	string removeCar()
	{
		if (empty == false)
		{
			train.push_back(turnTableCar);
			empty = true;
			return "OK";
		}
		else
		{
			return "Turntable empty!";
		}
	}
	string topCar()
	{
		if (empty == false)
		{
			ostringstream os;
			os << turnTableCar;
			return os.str();
		}
		else
		{
			return "Turntable empty!";
		}
	}
	string addStack()
	{
		if (empty == false)
		{
			stack.push(turnTableCar);
			empty = true;
			return "OK";
		}
		else
		{
			return "Turntable empty!";
		}
	}
	string removeStack()
	{
		if (stack.size() != 0)
		{
			turnTableCar = stack.top();
			empty = false;
			stack.pop();
			return "OK";
		}
		else
		{
			return "Stack empty!";
		}
	}
	string topStack()
	{
		if (stack.size() != 0)
		{
			ostringstream os;
			os << stack.top();
			return os.str();
		}
		else
		{
			return "Stack empty!";
		}
	}
	string sizeStack()
	{
		ostringstream os;
		os << stack.size();
		return os.str();
	}
	string addQueue()
	{
		if (empty == false)
		{
			queue.push(turnTableCar);
			empty = true;
			return "OK";
		}
		else
		{
			return "Turntable empty!";
		}
	}
	string removeQueue()
	{
		if (queue.size() != 0)
		{
			turnTableCar = queue.top();
			empty = false;
			queue.pop();
			return "OK";
		}
		else
		{
			return "Queue empty!";
		}
	}
	string topQueue()
	{
		if (queue.size() != 0)
		{
			ostringstream os;
			os << queue.top();
			return os.str();
		}
		else
		{
			return "Queue empty!";
		}
	}
	string sizeQueue()
	{
		ostringstream os;
		os << queue.size();
		return os.str();
	}
	string find(T check)
	{
		ostringstream os;
		if (turnTableCar == check)
		{
			if (empty == false)
			{
				return "Turntable";
			}
		}
		for (size_t i = 0; i < stack.size(); i++)
		{
			if (stack.at(i) == check)
			{
				os << "Stack[" << i << "]";
				return os.str(); 
			}
		}
		for (size_t i = queue.front_index(); i < queue.getCap(); i++)
		{
			if (queue.at(i) == check)
			{
				os << "Queue[" << (i - queue.front_index())  << "]";
				return os.str();
			}
		}
		for (size_t i = 0; i < train.size(); i++)
		{
			if (train.at(i) == check)
			{
				os << "Train[" << i << "]";
				return os.str();
			}
		}
		return "Not Found!";
	}
	string toString()
	{
		return train.toString();
	}
};
#endif
