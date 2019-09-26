#include "ItemToPurchase.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

ItemToPurchase::~ItemToPurchase() {

}
ItemToPurchase::ItemToPurchase(string initName, string initDescription, double initPrice, int initQuantity) {
	itemName = initName;
	itemDescription = initDescription;
	itemPrice = initPrice;
	itemQuantity = initQuantity;
}

void ItemToPurchase::SetName(string nameIn) {
	itemName = nameIn;
}

string ItemToPurchase::GetName() {
	return itemName;
}

void ItemToPurchase::SetItemDescription(string itemDescriptionIn) {
	itemDescription = itemDescriptionIn;
}

string ItemToPurchase::GetItemDescription() {
	return itemDescription;
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

void ItemToPurchase::PrintItemCost(string itemIn) {
	cout << fixed << setprecision(2) << itemIn << " " << itemQuantity << " @ $" << itemPrice << " = $" << itemPrice * itemQuantity << endl;
}

void ItemToPurchase::PrintItemDescription(string itemIn) {
	cout << itemIn << ": " << itemDescription << endl;
}

void ItemToPurchase::Print() {
	cout << "ItemName: " << itemName << endl;
	cout << "ItemDescription: " << itemDescription << endl;
	cout << "ItemPrice: " << itemPrice << endl;
	cout << "ItemQuantity: " << itemQuantity << endl;
}
