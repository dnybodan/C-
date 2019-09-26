#pragma once
#include "Cake.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
class LayerCake : public Cake {

public:
	
	LayerCake(string cakeFlavorIn, string cakeFrostingIn, int layerAmountIn);
	virtual string ToString();
	double DiscountedPrice(int itemQuantityIn);

	LayerCake();
	~LayerCake();
private:
	int layerAmount = 0;
};

