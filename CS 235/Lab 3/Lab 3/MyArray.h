#ifndef MYARRAY_H
#define MYARRAY_H
#define MAX_ARRAY_SIZE	1000
#include <sstream>
#include <string>

template<typename T>
class MyArray
{
private:
	T* array; // Points to the first memeber of our container, also is array representative pointer
	size_t size = 0; // Size of my container
public:
	MyArray(const size_t maxSize) : size(0)
	{
		array = static_cast<T*>(malloc(maxSize * sizeof(T)));
	}  

	~MyArray() 
	{ 
		free(array); 
	}

	void push_back(T item) 
	{ 
		array[size++] = item; //add an item to container
	}

	int size()
	{
		return maxSize * sizeof(T); //return size of array
	}

	T& operator[](size_t i) const  //bonus [] opperator
	{
		return array[i];
	}

	class Iterator
	{
	private:
		T* pos;  // pointer to position in array
		size_t iterSize = 0;
		size_t iterIndex = 0;
		size_t firstIndex = 0;
		size_t lastIndex = 0;
	public:
		Iterator(T* array, size_t size, size_t index) : pos(array) , iterSize(size), iterIndex(index) 
		{
			firstIndex = 0;
			lastIndex = size;
		} 
		~Iterator() {}
		bool operator!= (const Iterator& other) const 
		{ 
			return iterIndex != other.iterIndex; // not-equal 
		}        
		Iterator& operator++ () // pre-increment 
		{ 
			++iterIndex;
			return *this;
		}           
		Iterator& operator++ (int) // bonus function postfix ++ operator
		{
			Iterator tmp(*this);
			operator++();
			return tmp;
		}
		T& operator*() const 
		{ 
			return pos[iterIndex]; // derefrences the pos which is the position in MyArray to which it points 
		}  
		std::string toString() const 
		{
			std::ostringstream os;
			os << "ITERATORS:" << "\n";
			os << "begin(): size=" << iterSize << " index=" << firstIndex << "\n";  
			os << "end(): size=" << iterSize << " index=" << lastIndex << "\n";
			return os.str();
		}
		friend std::ostream& operator<< (std::ostream& os, const Iterator& iter) 
		{ 
			os << iter.toString();
			return os;
		}
	};
	Iterator begin() 
	{
		return MyArray<T>::Iterator(array, size, 0);
		// pointer to first element
	}             
	Iterator end() 
	{ 
		return  MyArray<T>::Iterator(array, size, size);
		 // pointer AFTER last element
	}  
	std::string toString() const 
	{
		std::ostringstream os;
		os << "myArray:";
		for (size_t i = 0; i < size; ++i)
		{
			os << ((i % 10) ? " " : "\n") << array[i];
		}
		return os.str();
	}
	friend std::ostream& operator<< (std::ostream& os, const MyArray<T>& myArray) 
	{ 
		os << myArray.toString();
		return os;
	};
};
#endif // MYARRAY_H
