#include <iostream>
#include <fstream>
#include <sstream>
#include "QuickSort.h"


using namespace std;

int main(int argc, char * argv[])
{

	//opening files
#if 1
	if (argc < 3)
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}
#endif

	string line;
	string command;
	size_t capacity;
	QuickSort<int> quickSort; //fixme

	while (getline(in, line))
	{
		stringstream iss(line);
		iss >> command;
		if (command != "Sort" && command != "Partition" && command != "MedianOfThree" && command != "AddToArray" )
			out << line << " ";

		
		if (command == "QuickSort")
		{
			iss >> capacity;
			quickSort.createArray(capacity);
			out << "OK";
		}
		else if (command == "AddToArray")
		{
			if (quickSort.capacity() == 0)
			{
				quickSort.createArray(1);
			}
			int newElement = 0;
			out << "AddToArray ";
			ostringstream os;
			iss >> newElement;
			out << newElement;
			quickSort.addElement(newElement);
			while (iss >> newElement)
			{
				quickSort.addElement(newElement);
				os << "," << newElement;
			}
			string s;
			s = os.str();
			s.erase(s.size(), 1);
			out << s << " ";
			out << "OK";
		}
		else if (command == "Capacity")
		{
			out << quickSort.capacity();
		}
		else if (command == "Clear")
		{
			quickSort.clear();
			out << "OK";
		}
		else if (command == "Size")
		{
			out << quickSort.size();
		}
		else if (command == "Sort")
		{
			size_t left = 0;
			size_t right = 0;
			iss >> left;
			iss >> right;
			out << "Sort " << left << "," << right << " ";
			quickSort.sort(left, right);
			out << "OK";
		}
		else if (command == "SortAll")
		{
			quickSort.sortAll();
			out << "OK";
		}
		else if (command == "MedianOfThree")
		{
			size_t left;
			size_t right;
			iss >> left;
			iss >> right;
			out << "MedianOfThree " << left << "," << right << " ";
			out << "= " << quickSort.medianOfThree(left, right);
		}
		else if (command == "Partition")
		{
			int left = 0;
			int right = 0;
			int pivot = 0;
			iss >> left;
			iss >> right;
			iss >> pivot;
			out << "Partition " << left << "," << right << "," << pivot << " ";
			out << "= " << quickSort.partition(left, right, pivot);
		}
		else if (command == "PrintArray")
		{
			if (quickSort.toString() == "")
			{
				out << "Empty";
			}
			else
			{
				out << quickSort.toString();
			}
		}
		else if (command == "Stats")
		{

		}
		out << endl;
	}

	system("pause");
	return 0;
}