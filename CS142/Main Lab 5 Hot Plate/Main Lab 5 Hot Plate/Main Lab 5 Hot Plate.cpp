



#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <fstream>

using namespace std;


int main() {

	ofstream file;
	ifstream inFile;

	const int NUM_ROWS = 10;
	const int NUM_COLS = 10;
	int i = 0;
	int j = 0;
	int u = 0;
	double hotPlateArrayOld[NUM_ROWS][NUM_ROWS];
	double hotPlateArrayNew[NUM_ROWS][NUM_COLS];
	double fileArray[NUM_ROWS][NUM_ROWS];
	double fileArrayNew[NUM_ROWS][NUM_COLS];
	double maxVal = 0.000;

	cout << "Hotplate simulator" << endl << endl;
	cout << "Printing initial plate..." << endl;



	for (i = 0; i < NUM_ROWS; ++i) {
		for (j = 0; j < NUM_COLS; ++j) {
			if (i == 0 && j != 0 && j != 9) {
				hotPlateArrayOld[i][j] = 100.000;
			}
			else if (i == 9 && j != 0 && j != 9) {
				hotPlateArrayOld[i][j] = 100.000;
			}
			else {
				hotPlateArrayOld[i][j] = 0.000;
			}
		}
	}

	//initial hotPlateArray


	for (i = 0; i < NUM_ROWS; ++i) {
		for (j = 0; j < NUM_COLS; ++j) {
			if (j == 9) {
				cout << fixed << setprecision(3) << setw(8) << right << hotPlateArrayOld[i][j] << endl;
			}
			else if (j == 0) {
				cout << fixed << setprecision(3) << setw(9) << right << hotPlateArrayOld[i][j] << ", ";
			}
			else {
				cout << fixed << setprecision(3) << setw(8) << right << hotPlateArrayOld[i][j] << ", ";
			}
		}
	}

	//first iteration of the 'averaging'

	cout << endl << "Printing plate after one iteration..." << endl;

	for (i = 0; i < NUM_ROWS; ++i) {
		for (j = 0; j < NUM_COLS; ++j) {
			if (i != 0 && i != 9 && j != 0 && j != 9) {
				hotPlateArrayNew[i][j] = ((hotPlateArrayOld[i - 1][j]) + (hotPlateArrayOld[i + 1][j]) + (hotPlateArrayOld[i][j - 1]) + (hotPlateArrayOld[i][j + 1])) / 4;
			}
			else {
				hotPlateArrayNew[i][j] = hotPlateArrayOld[i][j];
			}
		}
	}

	for (i = 0; i < NUM_ROWS; ++i) {
		for (j = 0; j < NUM_COLS; ++j) {
			if (j == 9) {
				cout << fixed << setprecision(3) << setw(8) << right << hotPlateArrayNew[i][j] << endl;
			}
			else if (j == 0) {
				cout << fixed << setprecision(3) << setw(9) << right << hotPlateArrayNew[i][j] << ", ";
			}
			else {
				cout << fixed << setprecision(3) << setw(8) << right << hotPlateArrayNew[i][j] << ", ";
			}
		}
	}

	for (i = 0; i < NUM_ROWS; ++i) {
		for (j = 0; j < NUM_COLS; ++j) {
			hotPlateArrayOld[i][j] = hotPlateArrayNew[i][j];
		}
	}

	//calculating the stable state

	cout << endl << endl << "Printing final plate..." << endl;

	//reseting hotPlateArrayOld to avoid repeating the first iteration 

	for (i = 0; i < NUM_ROWS; ++i) {
		for (j = 0; j < NUM_COLS; ++j) {
			hotPlateArrayOld[i][j] = hotPlateArrayNew[i][j];
		}
	}

	//looping until plate is stable

	do {
		maxVal = 0.000;
		for (i = 0; i < NUM_ROWS; ++i) {
			for (j = 0; j < NUM_COLS; ++j) {
				if (i != 0 && i != 9 && j != 0 && j != 9) {
					hotPlateArrayNew[i][j] = ((hotPlateArrayOld[i - 1][j]) + (hotPlateArrayOld[i + 1][j]) + (hotPlateArrayOld[i][j - 1]) + (hotPlateArrayOld[i][j + 1])) / 4;
					if (abs(hotPlateArrayNew[i][j]) - abs(hotPlateArrayOld[i][j]) > maxVal) {
						maxVal = (abs(hotPlateArrayNew[i][j]) - abs(hotPlateArrayOld[i][j]));
					}
				}
				else {
					hotPlateArrayNew[i][j] = hotPlateArrayOld[i][j];
				}
			}
		}
		for (i = 0; i < NUM_ROWS; ++i) {
			for (j = 0; j < NUM_COLS; ++j) {
				hotPlateArrayOld[i][j] = hotPlateArrayNew[i][j];
			}
		}
	} while (maxVal > 0.100);

	//printing statement

	for (i = 0; i < NUM_ROWS; ++i) {
		for (j = 0; j < NUM_COLS; ++j) {
			if (j == 9) {
				cout << fixed << setprecision(3) << setw(8) << right << hotPlateArrayNew[i][j] << endl;
			}
			else if (j == 0) {
				cout << fixed << setprecision(3) << setw(9) << right << hotPlateArrayNew[i][j] << ", ";
			}
			else {
				cout << fixed << setprecision(3) << setw(8) << right << hotPlateArrayNew[i][j] << ", ";
			}
		}
	}

	file.open("Hotplate.csv");

	if (!file.is_open()) {
		cout << "File Not Opened";
	}
	else {
		for (i = 0; i < NUM_ROWS; ++i) {
			for (j = 0; j < NUM_COLS; ++j) {
				if (j == 9) {
					file << fixed << setprecision(3) << setw(8) << right << hotPlateArrayNew[i][j] << endl;
				}
				else if (j == 0) {
					file << fixed << setprecision(3) << setw(9) << right << hotPlateArrayNew[i][j] << ", ";
				}
				else {
					file << fixed << setprecision(3) << setw(8) << right << hotPlateArrayNew[i][j] << ", ";
				}
			}
		}

	}


	file.close();

	//input file array and averaging



	cout << endl << endl << endl;
	inFile.open("Inputplate.txt");
	if (!inFile.is_open()) {
		cout << endl << "Could not open Inputplate.txt" << endl;
		return 1;
	}
	else {
		for (i = 0; i < NUM_ROWS; ++i) {
			for (j = 0; j < NUM_COLS; ++j) {
				inFile >> fileArray[i][j];
			}
		}
		for (u = 0; u < 3; u++) {
			for (i = 0; i < NUM_ROWS; ++i) {
				for (j = 0; j < NUM_COLS; ++j) {
					if (i != 0 && i != 9 && j != 0 && j != 9) {
						fileArrayNew[i][j] = ((fileArray[i - 1][j]) + (fileArray[i + 1][j]) + (fileArray[i][j - 1]) + (fileArray[i][j + 1])) / 4;
					}
					else {
						fileArrayNew[i][j] = fileArray[i][j];
					}
				}
			}
			for (i = 0; i < NUM_ROWS; ++i) {
				for (j = 0; j < NUM_COLS; ++j) {
					fileArray[i][j] = fileArrayNew[i][j];
				}
			}
		}

		for (i = 0; i < NUM_ROWS; ++i) {
			for (j = 0; j < NUM_COLS; ++j) {
				if (j == 9) {
					cout << fixed << setprecision(3) << setw(8) << right << fileArrayNew[i][j] << endl;
				}
				else if (j == 0) {
					cout << fixed << setprecision(3) << setw(9) << right << fileArrayNew[i][j] << ", ";
				}
				else {
					cout << fixed << setprecision(3) << setw(8) << right << fileArrayNew[i][j] << ", ";
				}
			}
		}
	}

	inFile.close();


	system("pause");
	return 0;
}

