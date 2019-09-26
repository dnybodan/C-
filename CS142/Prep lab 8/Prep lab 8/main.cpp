#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <iomanip>
#include "ItemToPurchase.h"

using namespace std;

int main() {
	ItemToPurchase itemOne;
	string itemNameIn;
	double itemPriceIn = 0.0;
	int itemQuantityIn = 0;
	ItemToPurchase itemTwo;

	cout << "Item 1" << endl;
	cout << "Enter the item name: " << endl;
	getline(cin, itemNameIn);
	itemOne.SetName(itemNameIn);
	cout << "Enter the item price: " << endl;
	cin >> itemPriceIn;
	cin.ignore();
	itemOne.SetPrice(itemPriceIn);
	cout << "Enter the item quantity: " << endl;
	cin >> itemQuantityIn;
	cin.ignore();
	itemOne.SetQuantity(itemQuantityIn);

	cout << "Item 2" << endl;
	cout << "Enter the item name: " << endl;
	getline(cin, itemNameIn);
	itemTwo.SetName(itemNameIn);
	cout << "Enter the item price: " << endl;
	cin >> itemPriceIn;
	cin.ignore();
	itemTwo.SetPrice(itemPriceIn);
	cout << "Enter the item quantity: " << endl;
	cin >> itemQuantityIn;
	cin.ignore();
	itemTwo.SetQuantity(itemQuantityIn);

	cout << "TOTAL COST" << endl;
	cout << itemOne.GetName() << itemOne.GetQuantity() << " @ $" << fixed << setprecision(2) << itemOne.GetPrice() << " = $" << (itemOne.GetPrice() * itemOne.GetQuantity()) << endl;
	cout << itemTwo.GetName() << itemTwo.GetQuantity() << " @ $" << fixed << setprecision(2) << itemTwo.GetPrice() << " = $" << (itemTwo.GetPrice() * itemTwo.GetQuantity()) << endl << endl;
	cout << "Total: $" << (itemOne.GetPrice() * itemOne.GetQuantity()) + (itemTwo.GetPrice() * itemTwo.GetQuantity());


	return 0;
}