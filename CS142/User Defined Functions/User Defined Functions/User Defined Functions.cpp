
#include "pch.h"
#include <iostream>
#include <cmath>

using namespace std;

double powerFunction(int numBase, int numExponent) {
	double productAnswer = 0.0;
	double numBaseNew = 1;

	for (int i = 0; i < numExponent; ++i) {
		numBaseNew = numBase * numBaseNew;
		productAnswer = numBaseNew;
	}

	return productAnswer;
}


int main() {
	double equationAnswer;

	equationAnswer = powerFunction(3, 3);
	cout << equationAnswer;


}

