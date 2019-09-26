#pragma once
#include <string>
#include <iostream>

using namespace std;


class Player {
private:
	string firstName;
	string lastName;
	double totalPoints;
	int currentAge;
public:
	Player();
	Player(string firstNameIn, string LastNameIn, int AgeIn);
	~Player();
	void SetFirstName(string firstNameIn);
	void SetLastName(string lastNameIn);
	void SetCurrentAge(int currentAgeIn);
	string GetFirstName();
	string GetLastName();
	double GetTotalPoints(double pointsToSet);
	void Print();
};

