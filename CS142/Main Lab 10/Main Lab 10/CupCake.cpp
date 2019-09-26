#include "CupCake.h"




CupCake::CupCake(string cakeFlavorIn, string cakeFrostingIn, string sprinkleColorIn) {
	cakeFlavor = cakeFlavorIn;
	cakeFrosting = cakeFrostingIn;
	sprinkleColor = sprinkleColorIn;

	if (cakeFrosting == "cream-cheese") {
		basePrice = 1.95 + .20;
	}
	else {
		basePrice = 1.95;
	}

}

string CupCake::ToString() {
	ostringstream orderOSS;
	string basicDescription;
	orderOSS << cakeFlavor << " cupCake with " << cakeFrosting << " frosting and " << sprinkleColor << " sprinkles" << BakedGood::ToString();
	basicDescription = orderOSS.str();
	return basicDescription;
}

double CupCake::DiscountedPrice(int itemQuantityIn) {
	if (itemQuantityIn > 1 && itemQuantityIn < 4) {
		discountedPrice = (basePrice - .3) * itemQuantityIn;
	}
	else if (itemQuantityIn > 3) {
		discountedPrice = (basePrice - .4) * itemQuantityIn;
	}
	else {
		discountedPrice = basePrice * itemQuantityIn;
	}
	
	
	return discountedPrice;
}

CupCake::CupCake() {
	cakeFlavor = "none";
	cakeFrosting = "none";
	sprinkleColor = "none";
}


CupCake::~CupCake() {
}
