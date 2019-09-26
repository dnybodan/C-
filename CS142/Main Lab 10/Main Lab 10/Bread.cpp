#include "Bread.h"
#include <iomanip>

Bread::Bread(string breadVarietyIn) : BakedGood() {
	breadVariety = breadVarietyIn;
	basePrice = 4.50;
}

Bread::Bread() : BakedGood() {
	breadVariety = "none";
}

Bread::~Bread() {
}

string Bread::ToString() {
	ostringstream orderOSS;
	string basicDescription; 
	orderOSS << breadVariety << " Bread " << BakedGood::ToString();
	basicDescription = orderOSS.str();
	return basicDescription;
}


double Bread::DiscountedPrice(int itemQuantityIn) {
	int loavesToDiscount = 0;
	double discountValue = 0.0;
	loavesToDiscount = (itemQuantityIn / 3);
	discountValue = (loavesToDiscount * 4.50);
	discountedPrice = (basePrice * itemQuantityIn) - discountValue;
	return discountedPrice;
}


