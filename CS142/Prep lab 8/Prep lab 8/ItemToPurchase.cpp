#include "ItemToPurchase.h"
#include <iostream>
#include <string>

using namespace std;


ItemToPurchase::ItemToPurchase() {
	itemName = "none";
	itemPrice = 0.0;
	itemQuantity = 0;
}


ItemToPurchase::~ItemToPurchase() {

}

void ItemToPurchase::SetName(string nameIn) {
	itemName = nameIn;
}

string ItemToPurchase::GetName() {
	return itemName;
}

void ItemToPurchase::SetPrice(double priceIn) {
	itemPrice = priceIn;
}

double ItemToPurchase::GetPrice() {
	return itemPrice;
}

void ItemToPurchase::SetQuantity(int quantityIn) {
	itemQuantity = quantityIn;
}

int ItemToPurchase::GetQuantity() {
	return itemQuantity;
}

void ItemToPurchase::Print() {
	cout << "ItemName: " << itemName << endl;
	cout << "ItemPrice: " << itemPrice << endl;
	cout << "ItemQuantity: " << itemQuantity << endl;
}

