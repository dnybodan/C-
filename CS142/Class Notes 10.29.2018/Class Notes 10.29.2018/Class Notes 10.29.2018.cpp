// Class Notes 10.29.2018.cpp 
//

#include "pch.h"
#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

int main() {

	Player myPlayer;
	myPlayer.SetFirstName("Stephen");
	myPlayer.SetLastName("Curry");
	myPlayer.Print();

	string currentFirstName = myPlayer.GetFirstName();
	cout << "first: " << currentFirstName << endl;
	string currentLastName = myPlayer.GetLastName();
	cout << "last: " << currentLastName << endl;




	return 0;
}

