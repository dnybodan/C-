#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ios>
#include "BST.h"
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif
using namespace std;

int main(int argc, char * argv[])
{
	VS_MEM_CHECK
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


	BST<int> intBST;
	BST<string> stringBST;
	string line;
	int value = 0;
	string sValue;
	bool isString = false;
	string command;
	while (getline(in, line))
	{
		stringstream ss(line);
		out << line << " ";
		ss >> command;
		if (line == "INT")
		{
			out << "true";
			isString = false;
		}
		else if (line == "STRING")
		{
			out << "true";
			isString = true;
		}
		else if (line == "clear")
		{
			if (isString == false)
			{
				if (intBST.clearTree())
				{
					out << "true";
				}
			}
			else
			{
				if (stringBST.clearTree())
				{
					out << "true";
				}
			}
		}
		else if (command == "add")
		{
			if (isString == false)
			{
				ss >> value;
				if (intBST.addNode(value))
				{
					out << "true";
				}
				else
				{
					out << "false";
				}
			}
			else
			{
				ss >> sValue;
				if (stringBST.addNode(sValue))
				{
					out << "true";
				}
				else
				{
					out << "false";
				}
			}
		}
		else if (line.substr(0, 6) == "remove")
		{
			if (isString == false)
			{
				ss >> value;
				if (intBST.removeNode(value))
				{
					out << "true";
				}
				else
				{
					out << "false";
				}
			}
			else
			{
				ss >> sValue;
				if (stringBST.removeNode(sValue))
				{
					out << "true";
				}
				else
				{
					out << "false";
				}
			}
		}
		else if (line.substr(0, 4) == "find")
		{
			
			if (isString == false)
			{
				ss >> value;
				if (intBST.find(value))
					out << "found";
				else
				{
					out << "not found";
				}
			}
			else
			{
				ss >> sValue;
				if (stringBST.find(sValue))
					out << "found";
				else
				{
					out << "not found";
				}
			}
		}
		else if (line == "size")
		{
			if (isString == false)
			{
				out << intBST.size();
			}
			else
			{
				out << stringBST.size();
			}
		}
		else if (line == "print")
		{
			out << ": ";
			if (isString == false)
			{
				if (intBST.toString() == "")
				{
					out << "empty";
				}
				out << intBST.toString();
			}
			else
			{
				if (stringBST.toString() == "")
				{
					out << "empty";
				}
				out << stringBST.toString();
			}
		}
		out << endl;
	}
	system("pause");
	return 0;
}