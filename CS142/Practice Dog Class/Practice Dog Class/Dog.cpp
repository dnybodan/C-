#include "Dog.h"
#include <iostream>
#include <string>

using namespace std;

Dog::Dog()
{
	dogName = "No name";
	dogBreed = "No breed";
	dogAge = -1;
}


Dog::~Dog()
{
}

void Dog::SetName(string nameIn) {
	dogName = nameIn;
}
string Dog::GetName() {
	return dogName;
}
void Dog::SetBreed(string breedIn) {
	dogBreed = breedIn;
}
string Dog::GetBreed() {
	return dogBreed;
}
void Dog::SetAge(int ageIn) {
	dogAge = ageIn;
}
int Dog::GetAge() {
	return dogAge;
}
void Dog::Print() {
	cout << "dog age: " << dogAge << endl;
	cout << "dog Name: " << dogName << endl;
	cout << "dog Breed: " << dogBreed << endl;
}
