#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Station.h"

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
	Station<size_t> myStation;

	string line;
	string command;
	size_t value = 0;
	while (getline(in, line)) //read untill eof
	{
		if (line == "")
		{
			continue;
		}
		stringstream ss(line);
		out << line << " ";
		ss >> command;
		if (command == "Add:station")
			{
				ss >> value;
				out << myStation.addCar(value);
			}
		else if (command == "Add:queue")
			{
				out << myStation.addQueue();
			}
		else if (command == "Add:stack")
			{
				out << myStation.addStack();
			}
		else if (command == "Remove:queue")
			{
				out << myStation.removeQueue();
			}
		else if (command == "Remove:stack")
			{
				out << myStation.removeStack();
			}
		else if (command == "Remove:station")
			{
				out << myStation.removeCar();
			}
		else if (command == "Top:station")
			{
				out << myStation.topCar();
			}
		else if (command == "Top:queue")
			{
				out << myStation.topQueue();
			}
		else if (command == "Top:stack")
			{
				out << myStation.topStack();
			}
		else if (command == "Size:queue")
			{
				out << myStation.sizeQueue();
			}
		else if (command == "Size:stack")
			{
				out << myStation.sizeStack();
			}
		else if ((command.substr(0, command.find(":") + 1)) == "Find:")
			{
				string sValue;
				sValue = command.substr(command.find(":") + 1, 1);
				stringstream newInt(sValue);
				newInt >> value;
				out << myStation.find(value);
			}
		else if (command == "Train:")
		{
			out << myStation.toString();
		}
		out << endl;

		}
	return 0;
}