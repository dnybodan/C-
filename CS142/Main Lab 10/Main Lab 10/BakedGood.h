#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class BakedGood {

public:
	virtual string ToString() = 0;
	virtual double DiscountedPrice(int itemQuantityIn) = 0;
	BakedGood();
	~BakedGood();

protected:
	double basePrice = 0;
	double discountedPrice = 0.0;
	int itemQuantity = 0;

};

