//Daniel Nybo 
//dnybo.dan@gmail.com
//11/26/2018
//Professor Wood Section 8
//Main lab 9 Doveloped in Visual Studio

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Song.h"
#include "Playlist.h"

using namespace std;

void PrintMenu() {
	cout << endl;
	cout << "add      Adds a list of songs to the library" << endl;
	cout << "list     Lists all the songs in the library" << endl;
	cout << "addp     Adds a new playlist" << endl;
	cout << "addsp    Adds a song to a playlist" << endl;
	cout << "listp    Lists all the playlists" << endl;
	cout << "play     Plays a playlist" << endl;
	cout << "delp     Deletes a playlist" << endl;
	cout << "delsp    Deletes a song from a playlist" << endl;
	cout << "delsl    Deletes a song from the library(and all playlists)" << endl;
	cout <<	"options  Prints this options menu" << endl;
	cout << "quit     Quits the program" << endl << endl;
}

void AddSongs(vector<Song*> & listOfSongs) {
	string userInput;
	string currSong;
	string currFirstLine;
	Song * newSong;

	cout << "Read in Song names and first lines (type \"STOP\" when done): " << endl;

	do {
		cout << "Song Name: " << endl;
		getline(cin, currSong);
		if (currSong != "STOP") {
			cout << "Song's first line: " << endl;
			getline(cin, currFirstLine);
			int numPlays = 0;

			newSong = new Song(currSong, currFirstLine, numPlays);
			listOfSongs.push_back(newSong);
		}

	} while (currSong != "STOP");



}

void Delete(vector<Song*> & listOfSongs) {
	int iterationCount = 0;
	iterationCount = listOfSongs.size();
	for (int i = 0; i < iterationCount; i++) {
		delete listOfSongs.at(i);
	}
	listOfSongs.clear();
}

void PrintListOfSongs(vector<Song*> listOfSongs) {
	for (int i = 0; i < listOfSongs.size(); i++) {
		cout << (*listOfSongs.at(i)).GetSongName() << ": \"" << (*listOfSongs.at(i)).GetFirstLine() << "\", " << (*listOfSongs.at(i)).GetNumPlays() << " play(s)." << endl;
	}
	cout << endl;
}

void PrintSongsWithIndex(vector<Song*> listOfSongs) {
	for (int i = 0; i < listOfSongs.size(); i++) {
		cout << i << ": " << (*listOfSongs.at(i)).GetSongName() << endl;
	}
}

void PrintPlaylists(vector<Playlist> listOfPlaylists) {
	for (int i = 0; i < listOfPlaylists.size(); i++) {
		cout << i << ": " << (listOfPlaylists.at(i)).GetPlaylistName() << endl;
	}
}

void AddSongToPlaylist(vector<Playlist> & listOfPlaylists, vector<Song*> & listOfSongs) {
	int userPlaylistChoice = 0;
	int userSongChoice = 0;

	PrintPlaylists(listOfPlaylists);
	cout << "Pick a playlist index number: " << endl;
	cin >> userPlaylistChoice;
	cin.ignore();

	PrintSongsWithIndex(listOfSongs);
	cout << "Pick a song index number: " << endl;
	cin >> userSongChoice;
	cin.ignore();

	(listOfPlaylists.at(userPlaylistChoice)).AddSongToPlaylist(listOfSongs.at(userSongChoice));
}

void PlaySongs(vector<Song*> & listOfSongs, vector<Playlist> & listOfPlaylists) {
	int userPlaylistChoice = 0;
	
	PrintPlaylists(listOfPlaylists);
	cout << "Pick a playlist index number: " << endl;
	cin >> userPlaylistChoice;
	cin.ignore();
	
	int numSongs = listOfPlaylists.at(userPlaylistChoice).GetNumberOfSongs();

	listOfPlaylists.at(userPlaylistChoice).PrintFirstLines(listOfPlaylists.at(userPlaylistChoice).GetPlaylistName());
	listOfPlaylists.at(userPlaylistChoice).IncrementNumPlays();
}

void DeletePlaylist(vector<Playlist> & listOfPlaylists, int indexLocation) {
	listOfPlaylists.erase(listOfPlaylists.begin() + indexLocation);
}

void DeleteSongInPlaylist(int playlistIndexIn, int songIndexIn, vector<Playlist> & listOfPlaylists) {
	listOfPlaylists.at(playlistIndexIn).DeleteSongInPlaylist(songIndexIn);
}

int main() {
	string userInput;
	vector<Song*> listOfSongs;
	vector<Playlist> listOfPlaylists;

	cout << "Welcome to the Firstline Player!  Enter options to see menu options." << endl << endl;

	do {
		cout << "Enter your selection now:" << endl;
		getline(cin, userInput);

		if (userInput == "options") {
			PrintMenu();
		}

		else if (userInput == "add") {
			AddSongs(listOfSongs);
		}
		
		else if (userInput == "list") {
			PrintListOfSongs(listOfSongs);
		}

		else if (userInput == "addp") {
			string newPlaylist;
			cout << "Playlist name:" << endl;
			getline(cin, newPlaylist);
			Playlist newPlayList(newPlaylist);
			listOfPlaylists.push_back(newPlaylist);
		}

		else if (userInput == "listp") {
			PrintPlaylists(listOfPlaylists);
		}

		else if (userInput == "addsp") {
			AddSongToPlaylist(listOfPlaylists, listOfSongs);
		}

		else if (userInput == "play") {
			PlaySongs(listOfSongs, listOfPlaylists);
		}

		else if (userInput == "delp") {
			int playlistIndexToDelete = 0;
			PrintPlaylists(listOfPlaylists);
			cout << "Pick a playlist index number to delete:" << endl;
			cin >> playlistIndexToDelete;
			cin.ignore();
			DeletePlaylist(listOfPlaylists, playlistIndexToDelete);
		}

		else if (userInput == "delsp") {
			int playlistIndex;
			int songIndex;
			PrintPlaylists(listOfPlaylists);
			cout << "Pick a playlist index number:" << endl;
			cin >> playlistIndex;
			cin.ignore();
			listOfPlaylists.at(playlistIndex).PrintSongsInPlaylist();
			cout << "Pick a song index number to delete:" << endl;
			cin >> songIndex;
			cin.ignore();
			DeleteSongInPlaylist(playlistIndex, songIndex, listOfPlaylists);
		}

		else if (userInput == "delsl") {
			int songIndex;
			string songName;
			PrintSongsWithIndex(listOfSongs);
			cout << "Pick a song index number:" << endl;
			cin >> songIndex;
			cin.ignore();

			songName = (*listOfSongs.at(songIndex)).GetSongName();

			for (int i = 0; i < listOfPlaylists.size(); i++) {
				if (listOfPlaylists.at(i).GetSongIndex(songName) > -1) {
					listOfPlaylists.at(i).DeleteSongInPlaylist((listOfPlaylists.at(i)).GetSongIndex(songName));
				}
			}

			delete listOfSongs.at(songIndex);
			listOfSongs.erase(listOfSongs.begin() + songIndex);
			
		}

		else if (userInput == "quit") {
			Delete(listOfSongs);
			cout << "Goodbye!" << endl;
		}

		else {
			PrintMenu();
		}

	} while (userInput != "quit");


	return 0;
}