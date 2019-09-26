#if (1)
#include <iostream>
#include <sstream>
#include <fstream>
#include "Maze.h"
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif
using namespace std;
#endif

int main(int argc, char * argv[])
{
	VS_MEM_CHECK
	//opening files
#if (1)
	if (argc < 3)
	{
		cerr << "Please provide name of input and output files\n";
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input\n";
		return 1;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output\n";
	}
#endif

	int height = 0;
	int width = 0;
	int numLayers = 0;
	string line;
	getline(in, line);
	stringstream ss(line);
	ss >> height;
	ss >> width;
	ss >> numLayers;
	Maze myMaze(height, width, numLayers);
	
	int layerCount = -1;
	int heightCount = 0;
	int currCell = 0;

	while (getline(in, line)) //read and parse input file
	{
		stringstream ns(line);

		if (line == "")
		{
			layerCount += 1;
			heightCount = 0;
		}

		else 
		{
			for (int j = 0; j < width; j++) //load array
			{
				ns >> currCell;
				myMaze.setValue(heightCount, j, layerCount, currCell);
			}
			heightCount += 1;
		}
	}

	out << "Solve Maze:" << endl;
	out << myMaze.toString() << endl;

	if (myMaze.find_maze_path() == true)
	{
		out << "Solution:" << endl;
		out << myMaze.toString();
	}
	else
	{
		out << "No Solution Exists!" << endl;
	}

	return 0;
}



 