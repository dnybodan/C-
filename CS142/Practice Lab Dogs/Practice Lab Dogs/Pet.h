#pragma once
#include "Animal.h"

#include <iostream>
#include <string>

using namespace std;

class Pet : public Animal
{
public:

	virtual void SetAnimalName(string animalNameIn) = 0;
	virtual void SetAnimalSay(string animalSayIn) = 0;
	virtual void SetAnimalDo(string animalDoIn) = 0;
	string GetName();
	Pet();
	~Pet();

protected:
	string animalName = "none";
};

