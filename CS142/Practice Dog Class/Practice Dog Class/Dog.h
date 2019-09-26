#pragma once
#include <iostream>
#include <string>

using namespace std;


class Dog
{
public:
	Dog();
	~Dog();
	void SetName(string nameIn);
	string GetName();
	void SetBreed(string breedIn);
	string GetBreed();
	void SetAge(int ageIn);
	int GetAge();
	void Print();
private:
	string dogName;
	string dogBreed;
	int dogAge;
};

