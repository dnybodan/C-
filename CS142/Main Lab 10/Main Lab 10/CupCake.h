#pragma once
#include "Cake.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class CupCake : public Cake {
public:
	
	CupCake(string cakeFlavorIn, string cakeFrostingIn, string sprinkleColorIn);
	CupCake();
	~CupCake();
	virtual string ToString();
	double DiscountedPrice(int itemQuantityIn);
private:
	string sprinkleColor;
};

