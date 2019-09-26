//Daniel Nybo
//December 5 2018
//Professor Wood
//Section 8
//Main Lab 10 doveloped in VS

#include "BakedGood.h"
#include "Bread.h"
#include "LayerCake.h"
#include "Cake.h"
#include "CupCake.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

void Invoice(vector<BakedGood*> orderList) {
	int numInstances = 0;
	int totalQuantity = 0;
	double totalPrice = 0.0;
	vector<BakedGood*> tempOrders;
	tempOrders = orderList;
	cout << "Invoice: " << endl;
	cout << setw(75) << left << "BakedGood" << setw(9) << right << "Quantity" << setw(9) << right << "Total" << endl;


	for (unsigned int i = 0; i < tempOrders.size(); i++) {
		numInstances = 1;
		for (unsigned int j = i + 1; j < tempOrders.size(); j++) {
			if ((*tempOrders.at(i)).ToString() == (*tempOrders.at(j)).ToString()) {
				numInstances += 1;
				tempOrders.erase(tempOrders.begin() + j);
				--j;
			}
		}
		cout << setw(75) << left << ((*tempOrders.at(i)).ToString()) << setw(9) << right << numInstances << setw(9) << right << fixed << setprecision(2) << ((*tempOrders.at(i)).DiscountedPrice(numInstances)) << endl;
		totalPrice += ((*tempOrders.at(i)).DiscountedPrice(numInstances));
		totalQuantity += numInstances;
	}
	
	cout << setw(75) << left << "Totals" << setw(9) << right << totalQuantity << setw(9) << right << fixed << setprecision(2) << totalPrice << endl;

	
}



int main() {
	string userInput;
	string userClass;
	string breadVariety;
	string cakeType;
	string cakeFlavor;
	string cakeFrosting;
	int layerAmount;
	string sprinkleColor;
	int itemQuantity;
	vector<BakedGood*> orderList;
	istringstream subOrderISS;

	cout << "**Bread and Cakes Bakery**" << endl << endl;

	cout << "Enter sub-order (enter \"done\" to finish)" << endl;
	
	do {
		
		cout << "Sub-order: ";
		getline(cin, userInput);

		subOrderISS.clear();
		subOrderISS.str(userInput);

		subOrderISS >> userClass;

		if (userClass == "Bread") {
			subOrderISS >> breadVariety;
			subOrderISS >> itemQuantity;
			
			for (int i = 0; i < itemQuantity; i++) {
				orderList.push_back(new Bread(breadVariety));
			}
		}

		else if (userClass == "Layer-cake") {
			subOrderISS >> cakeFlavor;
			subOrderISS >> cakeFrosting;
			subOrderISS >> layerAmount;
			subOrderISS >> itemQuantity;
			
			for (int i = 0; i < itemQuantity; i++) {
				orderList.push_back(new LayerCake(cakeFlavor, cakeFrosting, layerAmount));
			}
			

		}
		else if (userClass == "Cupcake") {
			subOrderISS >> cakeFlavor;
			subOrderISS >> cakeFrosting;
			subOrderISS >> sprinkleColor;
			subOrderISS >> itemQuantity;
			
			for (int i = 0; i < itemQuantity; i++) {
				orderList.push_back(new CupCake(cakeFlavor, cakeFrosting, sprinkleColor));
			}
		}

	} while (userClass != "done");

	cout << endl << "Order Confirmations:" << endl;

	for (unsigned int i = 0; i < orderList.size(); i++) {
		cout << (*orderList.at(i)).ToString() << endl;
	}
	cout << endl;

	Invoice(orderList);

	for (unsigned int i = 0; i < orderList.size(); i++) {
		delete orderList.at(i);
	}
	orderList.clear();

	

	cout << "Good Bye";
	return 0;
}