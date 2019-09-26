#include "LayerCake.h"





LayerCake::LayerCake(string cakeFlavorIn, string cakeFrostingIn, int layerAmountIn){
	cakeFlavor = cakeFlavorIn;
	cakeFrosting = cakeFrostingIn;
	layerAmount = layerAmountIn;

	double initPrice = 9.00;
	double addCreamCheese = 1.00;
	double addLayer = 3.00;
	basePrice = initPrice;
	
	if (cakeFrosting == "cream-cheese") {
		basePrice += layerAmount;
	}

	if (layerAmount > 1) {
		basePrice += (layerAmount - 1) * 3;
	}
	
}

string LayerCake::ToString() {
	ostringstream orderOSS;
	string basicDescription;
	orderOSS << layerAmount << "-layer " << cakeFlavor << "cake with " << cakeFrosting << " frosting" << BakedGood::ToString();
	basicDescription = orderOSS.str();
	return basicDescription;
}

double LayerCake::DiscountedPrice(int itemQuantityIn) {

	if (itemQuantityIn > 2) {
		discountedPrice = (basePrice * itemQuantityIn) - (itemQuantityIn * 2);
		return discountedPrice;
	}
	else {
		return basePrice * itemQuantityIn;
	}


	
}

LayerCake::LayerCake() {
	cakeFlavor = "none";
	cakeFrosting = "none";
	layerAmount = 0;
}


LayerCake::~LayerCake() {
}
