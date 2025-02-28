/*Daniel Nybo
Section 8 Professor Wood 
dnybo.dan@gmail.com
Doveloped in Visual Studio

TEST CASE 1:
INPUTS: add, 1, add, hello, add, 2, remove, 1, remove, three kings, add, 1, add, 3, add, 4, cut, 2, display, shuffle, display, battle, 1, 1, 3, 2, quit.
EXPECTED OUTPUTS(abreviated): what to add?, 1 has been added, what to add?, cout an error, what to add, 2 has been added, what to remove?, 1 has been removed, what to remove?,
three kings not on list, add what, 1 is added, add what, 3  is added, add what, 4 is added, cut where?, 3421, 2314, option1/2?, option1/2?, round2: option1/2?, invalid input option 1/2?, winner is 1, Goodbye!.
Status: PASSED

TEST CASE 2:
INPUTS: restraunt 1, options, look, add, RESTRaNT1ONE, remove, RESTRaNT1ONE, remove, RESTRaNT1ONE, add, chinese, add, mexican, add, burgers, add, other food, add, homecooked meal, shuffle, 
remove, other food, shuffle, display, add, newrestraunt, battle, quit.
EXPTECTED OUTPUTS(abreviated): invalid input display menu, option menu, invalid input display menu, add what?, RESTRaNT1ONE is added, remove what?, RESTRaNT1ONE is removed, remove what?,
RESTRaNT1ONE is not on the list, add what?, chinese is added, add what?, mexican is added, add what?, burgers is added, add what?, other food is added, add what, homecooked meal is added,
cannot shuffle list is not power of two, remove what?, other food is removed, burgers chinese homcooked meal mexican, add what, newrestraunt is added, battle cannot comence list not a power of 2, 
Goodbye!
STATUS: PASSED

TEST CASE 3:
INPUTS: can I do this?, remove, can I do this?, add, "myfavrestraunt", add, "sisters, fav restraunt", lol, battle, "myfavrestraunt", "sisters, fav restraunt", -1, -2, 1, quit. 
EXPECTED OUTPUTS(abreviated): error show options menu., remove what?, can I do this? is not on the list, add what?, "myfavrestraunt" is added, add what?, "sisters, fav restraunt" is added, error show option menu,
option 1/2?, invalid input option1/2, invalid input option 1/2, invalid input option 1/2?, invalid input option 1/2?, "myfavrestraunt" is the winner, goodbye!
SATUS: PASSED
*/


#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>

using namespace std;

void GetLineNoSpace(string & stringIn) {

	getline(cin, stringIn);
	if (stringIn.find_first_not_of(" \t") == std::string::npos) {
		getline(cin, stringIn);
	}
}

void PrintMenuFunction() {
	cout << "Please select one of the following options: " << endl << endl;
	cout << "quit - Quit the program" << endl;
	cout << "display - Display all restaurants" << endl;
	cout << "add - Add a restaurant" << endl;
	cout << "remove - Remove a restaurant" << endl;
	cout << "cut - \"Cut\" the list of restaurants" << endl;
	cout << "shuffle - \"Shuffle\" the list of restaurants" << endl;
	cout << "battle - Begin the tournament" << endl;
	cout << "options - Print the options menu" << endl << endl;

	return;
}

void UserOptionChioceErrorCheck(string & inputString) {

	while (1 == 1) {
		if (inputString == "quit" || inputString == "display" || inputString == "add" || inputString == "remove" || inputString == "cut" || inputString == "shuffle" ||
			inputString == "battle" || inputString == "options") {
			inputString = inputString;
			break;
		}
		else {
			cout << "Invalid Selection" << endl << endl;
			PrintMenuFunction();
			cout << "Enter your selection: ";
			GetLineNoSpace(inputString);
			cout << endl << endl;
		}
	} 

	return;
}

void DisplayFunction(vector<string> restrauntNames) {
	cout << "Here are the current restaurants:" << endl << endl;
	for (unsigned int i = 0; i < restrauntNames.size(); i++) {
		cout  << "\t" << "\"" << restrauntNames.at(i) << "\"" << endl;
	}
}

bool FindRestrauntFunction(vector<string> restrauntNames, string restrauntIn) {
	bool isInVector = false;
	
	for (unsigned int i = 0; i < restrauntNames.size(); i++) {
		if (restrauntNames.at(i) == restrauntIn) {
			isInVector = true;
			break;
		}
		else {
			isInVector = false;
		}
	}
	return isInVector;
}

void AddFunction(vector<string> & restrauntNames) {
	string restrauntToAdd;
	string duplicateName;
	cout << "What is the name of the restaurant you want to add?" << endl;

	GetLineNoSpace(restrauntToAdd);

	if (FindRestrauntFunction(restrauntNames, restrauntToAdd) == true) {
		cout << "That restaurant is already on the list, you can not add it again." << endl << endl;
	}
	else {
		restrauntNames.push_back(restrauntToAdd);
		cout << restrauntToAdd << " has been added." << endl << endl;
	}
}

void RemoveFunction(vector<string> & restrauntNames) {
	string restrauntToRemove;
	cout << "What is the name of the restaurant you want to remove?" << endl;

	GetLineNoSpace(restrauntToRemove);

	if (FindRestrauntFunction(restrauntNames, restrauntToRemove) == true) {
		for (unsigned int i = 0; i < restrauntNames.size(); i++) {
			if (restrauntNames.at(i) == restrauntToRemove) {
				int indexErasePosition = i;
				restrauntNames.erase(restrauntNames.begin() + indexErasePosition);
				cout << restrauntToRemove << " has been removed." << endl;
			}
		}
	}
	else {
		cout << "That restaurant is not on the list, you can not remove it." << endl;
	}
}

bool GetIntegerFunction(const vector<string> restrauntNames, int & userInput) {

	while (cin.fail()) {

		cin.clear();

		cin.ignore(200, '\n');
		cout << "The cut number must be between 0 and " << restrauntNames.size() << endl;
		cout << "How many restaurants should be taken from the top and put on the bottom?";
		cin >> userInput;
	}

	return true;
}

void CutFunction(vector<string> & restrauntNames) {
	int cutPosition;
	bool stopLoop = false;
	cout << "How many restaurants should be taken from the top and put on the bottom?";
	cin >> cutPosition;
	cin.ignore(200, '\n');
	GetIntegerFunction(restrauntNames, cutPosition);
	cout << endl << endl;
	
	do {
		if (cutPosition < restrauntNames.size() || cutPosition >= 0) {
			vector<string> tempVec;

			for (unsigned int i = 0; i < cutPosition; i++) {
				tempVec.push_back(restrauntNames.at(0));
				restrauntNames.erase(restrauntNames.begin());
			}
			for (unsigned int i = 0; i < cutPosition; i++) {
				restrauntNames.push_back(tempVec.at(i));
			}
			stopLoop = true;
		}
		else {
			while (cutPosition > restrauntNames.size() || cutPosition < 0) {
				cout << "The cut number must be between 0 and " << restrauntNames.size() << endl;
				cout << "How many restaurants should be taken from the top and put on the bottom?";
				cin >> cutPosition;
				GetIntegerFunction(restrauntNames, cutPosition);
			}
		}
	} while (stopLoop == false);

	return;
}

bool PowerOfTwo(int numberToCheck) {

	if ((numberToCheck != 0) && ((numberToCheck &(numberToCheck - 1)) == 0)) {
		return true;
	}
	else {
		return false;
	}
}

void ShuffleFunction(vector<string> & restrauntNames) {
	vector<string> tempVec;
	bool stopLoop = false;
	int indexPosition = 0;
	indexPosition = restrauntNames.size() / 2;
	

	do {
		if (PowerOfTwo(restrauntNames.size()) == true) {
			for (unsigned int i = 0; i < indexPosition; i++) {
				tempVec.push_back(restrauntNames.at(0));
				restrauntNames.erase(restrauntNames.begin());
			}
			for (unsigned int i = 0; i < restrauntNames.size(); i++) {
				tempVec.insert(tempVec.begin() + (i * 2), restrauntNames.at(i));
			}
			restrauntNames = tempVec;
			stopLoop = true;
		}
		else {
			cout << "The current tournament size (" << restrauntNames.size() << ") is not a power of two (2, 4,8...)." << endl;
			cout << "A shuffle is not possible.Please add or remove restaurants." << endl;
			stopLoop = true;
		}
	} while (stopLoop == false);

	return;
}

void BattleFunction(vector<string> restrauntNames) {
	if (PowerOfTwo(restrauntNames.size()) == false || restrauntNames.size() == 1) {
		cout << "The current tournament size (" << restrauntNames.size() << ") is not a power of two (2, 4, 8...)." << endl;
		cout << "A battle is not possible. Please add or remove restaurants." << endl;
	}
	else {
		int numRounds = 0;
		string userChoice;
		int roundCounter = 0;
		int j = 0;
		roundCounter = restrauntNames.size() / 2;
		vector<string> winningVec;

		while (restrauntNames.size() != 1) {
			j += 1;
			cout << "Round: " << j << endl;
			while (restrauntNames.size() != 0) { 
				cout << "Type \"1\" if you prefer " << restrauntNames.at(0) << " or" << endl;
				cout << "type \"2\" if you prefer " << restrauntNames.at(1) << endl;
				GetLineNoSpace(userChoice);
				cout << "Choice: " << endl;
				if (userChoice == "1") {
					winningVec.push_back(restrauntNames.at(0));
					restrauntNames.erase(restrauntNames.begin());
					restrauntNames.erase(restrauntNames.begin());
				}
				else if (userChoice == "2") {
					winningVec.push_back(restrauntNames.at(1));
					restrauntNames.erase(restrauntNames.begin());
					restrauntNames.erase(restrauntNames.begin());
				}
				else {
					cout << "Invalid choice" << endl;
				}
			}
			restrauntNames = winningVec;
			winningVec.clear();
		}
		cout << "The winning restaurant is " << restrauntNames.at(0) << "." << endl;
	}
	


	return;
}


int main() {
	string userOptionChoice;
	vector<string> restrauntNames;


	cout << "Welcome to the restaurant battle!Enter \"options\" to see options." << endl << endl;

	do {

		cout << "Enter your selection: ";
		GetLineNoSpace(userOptionChoice);
		cout << endl;
		UserOptionChioceErrorCheck(userOptionChoice);

		if (userOptionChoice == "options") {
			PrintMenuFunction();
		}
		if (userOptionChoice == "display") {
			DisplayFunction(restrauntNames);
		}
		if (userOptionChoice == "add") {
			AddFunction(restrauntNames);
		}
		if(userOptionChoice == "remove") {
			RemoveFunction(restrauntNames);
		}
		if (userOptionChoice == "cut") {
			CutFunction(restrauntNames);
		}
		if (userOptionChoice == "shuffle") {
			ShuffleFunction(restrauntNames);
		}
		if (userOptionChoice == "battle") {
			BattleFunction(restrauntNames);
		}



		
	} while (userOptionChoice != "quit");
	cout << "Goodbye!";
	
	return 0;
}
