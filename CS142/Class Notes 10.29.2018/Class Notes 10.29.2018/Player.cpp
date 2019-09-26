#include "pch.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

Player::Player() {
}

Player(string firstNameIn, string lastNameIn, int ageIn) {
	firstName = firstNameIn;
	lastName = lastNameIn;
	currentAge = ageIn;
}


Player::~Player() {
}


void Player::SetFirstName(string firstNameIn) {
	//if check? Admin maybe?
	firstName = firstNameIn;
}
void Player::SetLastName(string lastNameIn) {
	//if check? Admin?
	lastName = lastNameIn;
}
void Player::Print() {
	cout << firstName << " " << lastName << endl;
}
string Player::GetFirstName() {
	return firstName;
}
string Player::GetLastName() {
	return lastName;
}
