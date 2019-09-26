#include "Song.h"
#include <string>

using namespace std;

Song::Song(string songNameIn, string songFirstLineIn, int numPlaysIn) {
	songName = songNameIn;
	songFirstLine = songFirstLineIn;
	numPlays = numPlaysIn;
}

string Song::GetSongName() {
	return songName;
}

string Song::GetFirstLine() {
	return songFirstLine;
}

int Song::GetNumPlays() {
	return numPlays;
}

void Song::IncrementNumPlays() {
	numPlays += 1;
}


int Song::ReturnNumPlays() {
	return numPlays;
}

Song::~Song() {
}
