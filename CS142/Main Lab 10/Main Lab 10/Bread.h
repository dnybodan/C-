#pragma once
#include "BakedGood.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Bread : public BakedGood {

public:
	Bread(string breadVarietyIn);
	Bread();
	~Bread();
	virtual string ToString();
	virtual double DiscountedPrice(int itemQuantityIn);

private:
	string breadVariety;

};

