#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "MyArray.h"
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;

#endif

/*********************************************************************
*********************************************************************/

bool isPrime(int number)
{
	int i;
	if (number < 2) return false;
	for (i = 2; i < number; ++i)
	{
		if (number % i == 0) return false;
	}
	return true;
}


int main(int argc, char * argv[])
{
	VS_MEM_CHECK

	//opening files
	if (argc < 3) {
		cerr << "Please provide name of input and output files";
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out) {
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	MyArray<int> numbers(MAX_ARRAY_SIZE);

	int currValue;
	while (in >> currValue) //read until eof
	{

		numbers.push_back(currValue);
	}

	out << numbers << endl << endl;

	MyArray<int>::Iterator iter1 = numbers.begin();
	out << iter1 << endl;

	out << "SEQUENTIAL:" << endl;
	int count = 0;
	for (MyArray<int>::Iterator iter1 = numbers.begin(); iter1 != numbers.end(); ++iter1)
	{
		++count;
		out << *iter1 << ((count % 10) ? " " : "\n");
	}
	out << endl << endl;

	//Prime numbers
	out << "PRIME (Bonus)" << endl;
	for (size_t i = 0; i < numbers.size(); i++)
	{
		if (isPrime(numbers[i])) out << numbers[i] << " ";
	}
	out << endl << endl;

	out << "FIBONACCI (Bonus)" << endl;
	MyArray<int>::Iterator iter2 = numbers.begin();
	int n1 = *iter2++;
	int n2 = *iter2++;
	while (iter2 != numbers.end())
	{
		if ((n1 + n2) == *iter2)
		{
			out << *iter2 << "=" << n1 << "+" << n2 << " ";
		}
		n1 = n2;
		n2 = *iter2++;
	}
	out << endl << endl;

	return 0;
}