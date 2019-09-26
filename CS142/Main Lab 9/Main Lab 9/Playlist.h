#pragma once
#include "Song.h"
#include <iostream>
#include <vector>

using namespace std;

class Playlist {
public:
	Playlist(string playlistNameIn);
	string GetPlaylistName();
	void AddSongToPlaylist(Song * songNameIn);
	int GetNumberOfSongs();
	void PrintFirstLines(string playlistNameIn);
	void IncrementNumPlays();
	void PrintSongsInPlaylist();
	void DeleteSongInPlaylist(int songIndexIn);
	int GetSongIndex(string songName);
	~Playlist();


private:
	string playlistName;
	vector<Song*> songsInPlaylist;
};

