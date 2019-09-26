#pragma once
#include <iostream>
#include <string>

using namespace std;

class Animal
{
public:
	Animal();
	virtual void SetAnimalSay(string animalSayIn) = 0;
	virtual void Do();
	

protected:
	
	string animalDo = "eat";
	string animalSay = "bszzssh";
	~Animal();
};

