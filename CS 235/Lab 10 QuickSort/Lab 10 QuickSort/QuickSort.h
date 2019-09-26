#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include "QSInterface.h"

#include <iostream>

using namespace std;

template<typename T>
class QuickSort : public QSInterface<T>
{
private:
	size_t numElements = 0;
	size_t totCapacity = 0;
	int* myArray;
	int* tempArray;
public:
	QuickSort() 
	{ 
		myArray = nullptr;
		numElements = 0;
		totCapacity = 0;
	}
	~QuickSort() 
	{
		int* temp = myArray;
		delete[] temp;
		myArray = nullptr;
		temp = nullptr;
	}

	/** Dynamically allocate an initial array to the QuickSort class. */
	bool createArray(size_t capacity); 

	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	bool addElement(T element);

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	bool sort(size_t left, size_t right);

	/** Sort all elements of the QuickSort array using median and partition functions. */
	bool sortAll() 
	{ 
		return sort(0, numElements); 
	}

	/** Removes all items from the QuickSort array. */
	bool clear();

	/** Return size of the QuickSort array. */
	size_t capacity() const { return totCapacity; }

	/** Return number of elements in the QuickSort array. */
	size_t size() const { return numElements; }

	/** The median of three pivot selection has two parts:
	1) Calculates the middle index by averaging the given left and right indices:
	middle = (left + right)/2
	2) Then bubble-sorts the values at the left, middle, and right indices.

	After this method is called, data[left] <= data[middle] <= data[right].

	@param left - the left boundary for the subarray from which to find a pivot
	@param right - the right + 1 boundary for the subarray from which to find a pivot
	@return the index of the pivot (middle index).
	Return -1 if	1) the array is empty,
	2) if either of the given integers is out of bounds,
	3) or if the left index is not less than the right index.
	*/
	int medianOfThree(size_t left, size_t right);

	/** Partitions a subarray around a pivot value selected according
	to median-of-three pivot selection. Because there are multiple ways
	to partition a list, follow the algorithm on page 611.

	The values which are smaller than the pivot should be placed to the left of the pivot;
	the values which are larger than the pivot should be placed to the right of the pivot.

	@param left - left index for the subarray to partition.
	@param right - right index + 1 for the subarray to partition.
	@param pivotIndex - index of the pivot in the subarray.
	@return the pivot's ending index after the partition completes:
	Return -1 if	1) the array is empty,
					2) if any of the given indexes are out of bounds,
					3) if the left index is not less than the right index.
	*/
	int partition(size_t left, size_t right, size_t pivotIndex);

	/** @return: comma delimited string representation of the array. */
	std::string toString() const;


};
#endif //QUICK_SORT_H

template<typename T>
inline bool QuickSort<T>::createArray(size_t capacity)
{
	int* temp = myArray;
	delete[] temp;
	myArray = nullptr;
	temp = nullptr;
	cout << "Creating array" << endl;
	if (capacity < 0)
	{
		return false;
	}
	/*else if (totCapacity > 0)
	{
		myArray = new int[totCapacity];
		numElements = 0;
		cout << "Array is created with same capacity" << endl;
		return true;
	}*/
	else
	{
		myArray = new int[capacity];
		totCapacity = capacity;
		numElements = 0;
		cout << "Array is created" << endl;
		return true;
	}
}

template<typename T>
inline bool QuickSort<T>::addElement(T element)
{
	if (myArray == nullptr)
	{
		return false;
	}
	else if (numElements == totCapacity)
	{
		//cout << "Creating bigger Array out of old array of size:" << totCapacity << endl;
		totCapacity = totCapacity * 2;
		tempArray = new int[totCapacity];
		size_t i = 0;
		while (i < numElements)
		{
			tempArray[i] = myArray[i];
			i++;
		}
		//cout << "Deleting old array and returning new array of size: " << totCapacity << endl;
		delete[] myArray;
		myArray = tempArray;
	}
	myArray[numElements] = element;
	numElements++;
	return true;
}

template<typename T>
inline bool QuickSort<T>::sort(size_t left, size_t right)
{
	if ((numElements == 0) || (left < 0) || (right < 0) || (left > numElements) || (right > numElements) || (left >= right)) {
		return false;
	}
	else {
		for (int i = left; i < (int)right - 1; i++) {
			int min = i;
			for (int j = i + 1; j < (int)right; j++)
				if (myArray[j] < myArray[min]) {
					min = j;
				}
			int temp = 0;
			temp = myArray[i];
			myArray[i] = myArray[min];
			myArray[min] = temp;
		}
		return true;
	}
}

template<typename T>
inline bool QuickSort<T>::clear()
{
	
	int* temp = myArray;
	delete[] temp;
	myArray = nullptr;
	temp = nullptr;
	//totCapacity = 0;
	numElements = 0;
	myArray = new int[totCapacity];
	return true;
}

template<typename T>
inline int QuickSort<T>::medianOfThree(size_t left, size_t right)
{
	if (totCapacity < 1) return -1;
	if (right > numElements) return -1;
	if (left > right) return -1;
	if (left < 0) return -1;
	int pivot = 0;
	pivot = (left + right) / 2;
	if (myArray[left] > myArray[pivot]) {
		swap(myArray[left], myArray[pivot]);
	}
	if (myArray[left] > myArray[right - 1]) {
		swap(myArray[left], myArray[right - 1]);
	}
	if (myArray[pivot] > myArray[right - 1]) {
		swap(myArray[pivot], myArray[right - 1]);
	}
	//cout << "Pivot is: " << myArray[pivot] << "  at index: " << pivot << endl;
	return pivot;
}

template<typename T>
inline int QuickSort<T>::partition(size_t left, size_t right, size_t pivotIndex)
{
	if ((numElements == 0) || (left < 0) || (right < 0) || (left > numElements) || (right > numElements) || (left >= right) || (pivotIndex >= right)) {
		return -1;
	}
	int pivot = pivotIndex;
	int pValue = 0;
	pValue = myArray[pivot];

	int iLeft = left;
	int iRight = right;

	int up = iLeft + 1;
	int down = iRight - 1;

	while (up < down) {
		if (myArray[up] > pValue && myArray[down] <= pValue) {
			swap(myArray[up], myArray[down]);
		}
		if (myArray[up] <= pValue) up++;
		if (myArray[down] > pValue) down--;
	}
	if (myArray[iLeft] > myArray[down]) swap(myArray[iLeft], myArray[down]);

	if (down != iRight - 1) pivot = down;
	return pivot;


	
}

template<typename T>
inline std::string QuickSort<T>::toString() const
{
	ostringstream os;
	for (size_t i = 0; i < numElements; i++)
	{
		os << myArray[i];
			if (i < numElements - 1)
			{
				os << ",";
			}
	}
	string stringOut;
	stringOut = os.str();
	return stringOut;
}
