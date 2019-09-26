#ifndef MAZE_H
#define MAZE_H

#include "MazeInterface.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

enum color { OPEN, BLOCKED, PATH, EXIT, TEMPORARY };

class Maze : public MazeInterface
{
	
private:
	int height = 0;
	int width = 0;
	int numLayers = 0;
	int ***myArray = nullptr;

public:
#if (1)
	Maze(int h, int w, int nL) : height(h), width(w), numLayers(nL)
	{
		myArray = new int**[height]();
		for (int i = 0; i < height; ++i)
		{
			myArray[i] = new int*[width]();
			for (int j = 0; j < width; ++j)
			{
				myArray[i][j] = new int[numLayers]();
			}
		}
	}
	~Maze() 
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; j++)
			{
				delete[] myArray[i][j];
			}
			delete[] myArray[i];
		}
		delete[] myArray;
	}

	/** Set maze value
	   @parm height
	   @parm width
	   @parm layer
	   @parm value
	*/
	void setValue(int height, int width, int layer, int value) 
	{
		myArray[height][width][layer] = value;
	}


	/** Solve maze
	   @return true if solveable, else false
	*/
	bool find_maze_path() 
	{ 
		return find_maze_path(0, 0, 0); 
	}

	/** Output maze (same order as input maze)
	  @return string of 2D layers
	*/
#endif

	bool find_maze_path(int h, int w, int nL)
	{
		
		if (h < 0 || w < 0 || nL < 0 || h >= height || w >= width || nL >= numLayers)
		{
			return false;
		}
		cout << myArray[h][w][nL] << endl;
		cout << h << endl;
		cout << w << endl;
		cout << nL << endl;

		if (myArray[h][w][nL] != OPEN)
		{
			return false;
		}
		else if (h == height - 1 && w == width - 1 && nL == numLayers - 1)
		{
			myArray[h][w][nL] = EXIT; //cell is on maze path and is maze exit
			return true;
		}
		else if (myArray[h][w][nL] == PATH)
		{
			return false;
		}
		else
		{
			//recursive case
			myArray[h][w][nL] = PATH;
			if (find_maze_path(h, w - 1, nL))
			{
				return true;
			}
			if (find_maze_path(h, w + 1, nL))
			{
				return true;
			}
			if (find_maze_path(h - 1, w, nL))
			{
				return true;
			}
			if (find_maze_path(h + 1, w, nL))
			{
				return true;
			}
			if (find_maze_path(h, w, nL - 1))
			{
				return true;
			}
			if (find_maze_path(h, w, nL + 1))
			{
				return true;
			}
			else
			{
				myArray[h][w][nL] = TEMPORARY; //dead end
				return false;
			}
		}
	}


	std::string toString() const
	{
		std::ostringstream os;

		for (int k = 0; k < numLayers; k++)
		{
			os << endl << "Layer " << k + 1 << endl;
			cout << endl << "Layer " << k + 1 << endl;
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (myArray[i][j][k] == 0 || myArray[i][j][k] == TEMPORARY)
					{
						os << "_" << " ";
						cout << "_" << " ";
					}
					else if (myArray[i][j][k] == 1)
					{
						os << "X" << " ";
						cout << "X" << " ";
					}
					else
					{
						cout << myArray[i][j][k] << " ";
						os << myArray[i][j][k] << " ";
					}
				}
				os << endl;
				cout << endl;
			}
		}
		return os.str();
	}



};
#endif
