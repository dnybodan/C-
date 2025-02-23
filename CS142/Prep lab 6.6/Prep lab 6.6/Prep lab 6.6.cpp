// Prep lab 6.6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

int GetNumOfSpaces(string inputString) {
	int numSpaces = 0;

	for (int i = 0; i < inputString.size(); i++) {
		if (isspace(inputString.at(i))) {
			numSpaces = numSpaces + 1;
		}
	}
	return numSpaces;
}

string OutputWithoutWhitespace(string inputString) {
	for (int i = 0; i < inputString.size(); i++) {
		if (isspace(inputString.at(i))) {
			inputString.erase(i, 1);
		}
	}
	return inputString;
}

int main() {
	string userInitialString;

	cout << "Enter a sentence or phrase: " << endl;
	getline(cin, userInitialString);

	cout << "You entered: " << userInitialString << endl << endl;
	cout << "Number of spaces: " << GetNumOfSpaces(userInitialString) << endl;

	cout << "String with no whitespace: " << OutputWithoutWhitespace(userInitialString) << endl;


}
