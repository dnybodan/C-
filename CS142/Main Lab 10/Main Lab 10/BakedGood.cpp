#include "BakedGood.h"
#include <iomanip>


string BakedGood::ToString() {
	ostringstream orderOSS;
	string basePriceOnly;
	orderOSS << fixed << setprecision(2) << " ($" << basePrice << ")";
	basePriceOnly = orderOSS.str();
	return basePriceOnly;
}

double BakedGood::DiscountedPrice(int itemQuantityIn) {
	return 0;
}


BakedGood::BakedGood() { 
}



BakedGood::~BakedGood() {
}
