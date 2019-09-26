#pragma once
#include <iostream>
#include <string>

using namespace std;

class Song {
public:
	Song(string songNameIn, string songFirstLineIn, int numPlaysIn);
	string GetSongName();
	string GetFirstLine();
	int GetNumPlays();
	void IncrementNumPlays();
	int ReturnNumPlays();
	~Song();
private:
	string songName;
	string songFirstLine;
	int numPlays = 0;
};

