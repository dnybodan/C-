#include "Playlist.h"
#include "Song.h"


Playlist::Playlist(string playlistNameIn) {
	playlistName = playlistNameIn;
}

string Playlist::GetPlaylistName() {
	return playlistName;
}

void Playlist::AddSongToPlaylist(Song * songIn) {
	songsInPlaylist.push_back(songIn);
}

int Playlist::GetNumberOfSongs() {
	return songsInPlaylist.size();
}

void Playlist::PrintFirstLines(string playlistNameIn) {
	cout << "Playing first lines of playlist: " << playlistNameIn << endl;
	for (int i = 0; i < songsInPlaylist.size(); i++) {
		cout << (*songsInPlaylist.at(i)).GetFirstLine() << endl;
	}
}

void Playlist::PrintSongsInPlaylist() {
	for (int i = 0; i < songsInPlaylist.size(); i++) {
		cout << i << ": " << (*songsInPlaylist.at(i)).GetSongName() << endl;
	}
}

void Playlist::DeleteSongInPlaylist(int songIndexIn) {
	songsInPlaylist.erase(songsInPlaylist.begin() + songIndexIn);
}

void Playlist::IncrementNumPlays() {
	for (int i = 0; i < songsInPlaylist.size(); i++) {
		(*songsInPlaylist.at(i)).IncrementNumPlays();
	}
}

int Playlist::GetSongIndex(string songName) {
	for (int i = 0; i < songsInPlaylist.size(); i++) {
		if ((*songsInPlaylist.at(i)).GetSongName() == songName) {
			return i;
		}
	}
	return -1;
}

Playlist::~Playlist() {
}
