#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include "LinkedList.h"
#include "LinkedListInterface.h"
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

using namespace std;

int main(int argc, char * argv[]) 
{
	VS_MEM_CHECK;

	LinkedList<int>* iLL = nullptr;
	LinkedList<string>* sLL = nullptr;

	//opening files
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

	//parsing inputs 
	string line;
	
	string userInput;
	string command;
	string stringData;
	string stringMatch;
	int intData;
	int intMatch;
	int index;
	bool isString = false;

	while (getline(in, line)) //read until eof
	{
		stringstream ss(line);
		ss >> userInput;
		out << ss.str() << " ";
		
		if (userInput == "INT") 
		{
			iLL = new LinkedList<int>();
			isString = false;
			out << "true" << endl;
		}
		else if (userInput == "STRING")
		{
			sLL = new LinkedList<string>();
			isString = true;
			out << "true" << endl;
		}
		else if (userInput == "insertHead")
		{
			if (isString == true) 
			{
				ss >> stringData;
				if (sLL->insertHead(stringData))
				{
					out << "true" << endl;
				}
				else
				{
					out << "false" << endl;
				}
			}
			else
			{
				ss >> intData;
				
				if (iLL->insertHead(intData))
				{
					out << "true" << endl;
				}
				else
				{
					out << "false" << endl;
				}
			}
		}
		else if (userInput == "insertTail")
		{
			if (isString == true)
			{
				ss >> stringData;
				if (sLL->insertTail(stringData))
				{
					out << "true" << endl;
				}
				else
				{
					out << "false" << endl;
				}
			}
			else
			{
				ss >> intData;
				if (iLL->insertTail(intData))
				{
					out << "true" << endl;
				}
				else
				{
					out << "false" << endl;
				}
			}
		}
		else if (userInput == "insertAfter")
		{
			if (isString == true)
			{
				ss >> stringMatch;
				ss >> stringData;
				if (sLL->insertAfter(stringMatch, stringData))
				{
					out << "true" << endl;
				}
				else
			 	{
					out << "false" << endl;
				}
			}
			else
			{
				ss >> intMatch;
				ss >> intData;
				if (iLL->insertAfter(intMatch, intData))
				{
					out << "true" << endl;
				}
				else
				{
					out << "false" << endl;
				}
			}
		}
		else if (userInput == "remove")
		{
			if (isString == true)
			{
				ss >> stringData;
				if (sLL->remove(stringData))
				{
					out << "true" << endl;
				}
				else
				{
					out << "false" << endl;
				}
			}
			else
			{
				ss >> intData;
				if (iLL->remove(intData))
				{
					out << "true" << endl;
				}
				else
				{
					out << "false" << endl;
				}
		
			}
		}
		else if (userInput == "at")
		{
			ss >> index;
			if (isString == true) 
			{
				try 
				{
					sLL->at(index, stringData);
					out << stringData << " true" << endl;
				}
				catch (std::out_of_range) {// if index is out of range catch the thrown exeption
					out << "Invalid Index" << std::endl;
				}
			}
			else
			{
				try
				{
					iLL->at(index, stringData);
					out << stringData << " true" << endl;
				}
				catch (std::out_of_range) {// if index is out of range catch the thrown exeption
					
					out << "Invalid Index" << endl;
				}
				
			}
		}
		else if (userInput == "size")
		{
			if (isString == true)
			{
				 out << sLL->size() << endl;
			}
			else
			{
				out << iLL->size() << endl;
			}
		}
		else if (userInput == "clear")
		{
			if (isString == true)
			{	
				sLL->clear();
				out << "true " << endl;
			}
			else
			{
				iLL->clear();
				out << "true " << endl;
			}
		}
		else if (userInput == "printList")
		{
			if (isString == true)
			{
				if (sLL->listSize == 0)
				{
					out << " Empty" << endl;
				}
				else
				{
					out << *sLL << endl; //outputs strings list via overloaded << operator
				}
			}
			else
			{
				if (iLL->listSize == 0)
				{
					out << " Empty" << endl;
				}
				else
				{
					out << *iLL << endl; //outputs int list via overloaded << operator
				}
				
			}
		}
		else
		{
			out << "Invalid Input: Error" << endl;
		}
	}

	//cleanup
	if (!(iLL == nullptr)) 
	{
		delete iLL;
	}
	if (!(sLL == nullptr))
	{
		delete sLL;
	}
	in.close();
	out.close();


	return 0; 
}