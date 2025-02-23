/*Daniel Nybo
Section 8: Professor Wood.
dnybo.dan@gmail.com
doveloped in VisualStudio

I was able to make it work by just changing 3 constants

*/

//#include "pch.h"
#include <string>
#include <iostream>
#include <cmath>
#include <cctype>
#include <iomanip>

using namespace std;

const int NUM_SLOTS = 8;
const int NUM_ROWS = 12;

double ComputeWinnings(int slot) {
	double prizeSlot[NUM_ROWS];

	prizeSlot[0] = 300.00;
	prizeSlot[1] = 200.00;
	prizeSlot[2] = -600.42;
	prizeSlot[3] = 20000.00;
	prizeSlot[4] = 0.01;
	prizeSlot[5] = 800.00;
	prizeSlot[6] = -1400.00;
	prizeSlot[7] = 500.00;
	prizeSlot[8] = 100.00;

	for (int i = 0; i < NUM_ROWS; i++) {
		if (i == slot) {
			return prizeSlot[i];
		}
	}
}

double DropSingleChip(double chipSlot, bool printOutput = true) {
	int leftOrRight = 0;
	for (int j = 0; j < NUM_ROWS; j++) {
		if (chipSlot != 0 && chipSlot != NUM_SLOTS) {
			leftOrRight = rand() % 2;
			if (leftOrRight == 1) {
				chipSlot = chipSlot + 0.5;
			}
			else {
				chipSlot = chipSlot - 0.5;
			}
		}
		else if (chipSlot == NUM_SLOTS) {
			chipSlot = NUM_SLOTS - 0.5;
		}
		else if (chipSlot == 0) {
			chipSlot = 0.5;
		}
		if (j < NUM_ROWS - 1) {
			if (printOutput) {
				cout << fixed << setprecision(1) << chipSlot << ", ";
			}
		}
		if (j == NUM_ROWS - 1) {
			if (printOutput) {
				cout << fixed << setprecision(1) << chipSlot;
			}
		}
	}
	return ComputeWinnings(chipSlot);
}

double DropMultipleChips(int numChips, int chipSlot) {
	double totalWinnings = 0.00;
	for (int i = 0; i < numChips; i++) {
		totalWinnings = totalWinnings + DropSingleChip(chipSlot, false);
	}
	return totalWinnings;
}

int UserMenuChoice() {
	int userMenuChoice;

	cin >> userMenuChoice;
	cout << endl;

	while (cin.fail() || (userMenuChoice < 0) || (userMenuChoice > NUM_SLOTS)) {
		if (cin.fail() || (userMenuChoice < 0)) {
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Invalid selection.  Enter 4 to see options." << endl << endl;

			cout << "Enter your selection now: ";

			cin >> userMenuChoice;
			cout << endl;
		}

		if ((userMenuChoice < 0) || (userMenuChoice > NUM_SLOTS)) {
			cout << "Invalid selection.Enter 4 to see options." << endl << endl;

			cout << "Enter your selection now: ";

			cin >> userMenuChoice;
			cout << endl;
		}
	}

	return userMenuChoice;
}

int ChipSlot() {
	int chipSlot = 0;

	do {
		cout << "Which slot do you want to drop the chip in (0-" << NUM_SLOTS << ")? ";

		cin >> chipSlot;
		cout << endl;

		while (cin.fail() || (chipSlot < 0) || (chipSlot > NUM_SLOTS)) {
			if (cin.fail() || (chipSlot < 0)) {
				cin.clear();
				cin.ignore(10, '\n');
				cout << "Invalid slot." << endl << endl;

				cout << "Which slot do you want to drop the chip in (0-" << NUM_SLOTS - 1 << ")? ";

				cin >> chipSlot;
				cout << endl;
			}

			if ((chipSlot < 0) || (chipSlot > NUM_SLOTS)) {
				cout << "Invalid slot." << endl << endl;

				cout << "Which slot do you want to drop the chip in (0-" << NUM_SLOTS - 1 << ")? ";

				cin >> chipSlot;
				cout << endl;
			}
		}


	} while ((chipSlot < 0) || (cin.fail()));

	return chipSlot;
}

int NumberOfChips() {
	int chipAmount = 0;

	do {

		cout << "How many chips do you want to drop (>0)? ";

		cin >> chipAmount;
		cout << endl;


		if (cin.fail()) {
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Invalid number of chips." << endl << endl;

			cout << "How many chips do you want to drop (>0)? ";

			cin >> chipAmount;
			cout << endl;
		}
		else if (chipAmount <= 0) {
			cout << "Invalid number of chips." << endl << endl;
		}

	} while ((chipAmount <= 0) || (cin.fail()));

	return chipAmount;
}

int  OptionMenu(int userMenuChoice) {

	cout << "Menu: Please select one of the following options:" << endl << endl;
	cout << "1 - Drop a single chip into one slot" << endl;
	cout << "2 - Drop multiple chips into one slot" << endl;
	cout << "3 - Drop multiple chips into each slot" << endl;
	cout << "4 - Show the options menu" << endl;
	cout << "5 - Quit the program" << endl << endl;

	return userMenuChoice;
}

int main() {
	int userMenuChoice = 0;
	const int SINGLE_CHIP = 1;
	const int MULTIPLE_CHIP = 2;
	const int MULTIPLE_CHIP_EACH_SLOT = 3;
	const int OPTION_MENU = 4;
	const int QUIT_PROGRAM = 5;
	double chipSlot = 0.0;
	int chipAmount = 0;
	long double totalWinnings = 0.00;
	long double chipAverage = 0.00;
	const int RANDOM_SEED = 42;

	srand(RANDOM_SEED);

	cout << "Welcome to the Plinko simulator! Enter 4 to see options." << endl << endl;

	do {
		cout << "Enter your selection now: ";
		userMenuChoice = UserMenuChoice();

		if (userMenuChoice == OPTION_MENU) {

			cout << "Menu: Please select one of the following options:" << endl << endl;
			cout << "1 - Drop a single chip into one slot" << endl;
			cout << "2 - Drop multiple chips into one slot" << endl;
			cout << "3 - Drop multiple chips into each slot" << endl;
			cout << "4 - Show the options menu" << endl;
			cout << "5 - Quit the program" << endl << endl;
		}

		if (userMenuChoice == SINGLE_CHIP) {

			cout << "*** Drop a single chip ***" << endl << endl;

			chipSlot = ChipSlot();


			cout << "*** Dropping chip into slot " << static_cast<int>(chipSlot) << "***" << endl;
			cout << "Path: [";
			cout << fixed << setprecision(1) << chipSlot << ", ";

			double oneChipWinnings = 0.00;
			oneChipWinnings = DropSingleChip(chipSlot, true);

			cout << "]" << endl;
			cout << "Winnings: $" << fixed << setprecision(2) << oneChipWinnings << endl << endl;

		}

		else if (userMenuChoice == MULTIPLE_CHIP) {
			cout << "*** Drop multiple chips ***" << endl << endl;

			chipAmount = NumberOfChips();
			chipSlot = ChipSlot();

			totalWinnings = DropMultipleChips(chipAmount, chipSlot);
			cout << fixed << setprecision(2) << "Total winnings on " << chipAmount << " chips: $" << totalWinnings << endl;
			chipAverage = totalWinnings / chipAmount;
			cout << fixed << setprecision(2) << "Average winnings per chip: $" << chipAverage << endl << endl;


		}

		if (userMenuChoice == MULTIPLE_CHIP_EACH_SLOT) {
			cout << "*** Sequentially drop multiple chips ***" << endl;
			chipAmount = NumberOfChips();

			for (int i = 0; i < NUM_SLOTS + 1; i++) {
				totalWinnings = DropMultipleChips(chipAmount, i);
				cout << "Total Winnings on " << chipAmount << " chips in slot " << i << ": $" << fixed << setprecision(2) << totalWinnings << endl;
				cout << "Average winnings per chip: $" << fixed << setprecision(2) << totalWinnings / static_cast<double>(chipAmount) << endl << endl;
			}
		}


		else if ((userMenuChoice != SINGLE_CHIP) && (userMenuChoice != MULTIPLE_CHIP) && (userMenuChoice != OPTION_MENU) && (userMenuChoice != QUIT_PROGRAM)) {
			cout << "Invalid selection. Enter 4 to see options." << endl << endl;
		}


	} while (userMenuChoice != QUIT_PROGRAM);

	cout << "Goodbye!" << endl;
	return 0;
}
