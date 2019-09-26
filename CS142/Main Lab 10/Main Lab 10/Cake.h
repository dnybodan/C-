#pragma once
#include "BakedGood.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Cake : public BakedGood {
public:
	virtual string ToString() = 0;
	Cake();
	~Cake();

protected:
	string cakeFlavor;
	string cakeFrosting;

};

