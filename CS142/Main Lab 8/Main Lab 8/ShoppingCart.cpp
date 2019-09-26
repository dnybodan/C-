#include "ShoppingCart.h"
#include "ItemToPurchase.h"
#include <vector>
#include <string>

using namespace std;

ShoppingCart::ShoppingCart(string costomerNameIn, string shoppingDateIn) {
	costomerName = costomerNameIn;
	shoppingDate = shoppingDateIn;
}

ShoppingCart::~ShoppingCart() {
}

string ShoppingCart::GetCostomerName() {
	return costomerName;
}

string ShoppingCart::GetCostomerDate() {
	return shoppingDate;
}

void ShoppingCart::AddItem(ItemToPurchase itemNameIn) {
	string userNewItemName;
	string userNewItemDescription;
	double userNewItemPrice = 0.00;
	int userNewItemQuantity = 0;

	cout << "Enter the item name: " << endl;
	getline(cin, userNewItemName);
	itemNameIn.SetName(userNewItemName);
	cout << "Enter the item description: " << endl;
	getline(cin, userNewItemDescription);
	itemNameIn.SetItemDescription(userNewItemDescription);
	cout << "Enter the item price: " << endl;
	cin >> userNewItemPrice; 
	cin.ignore();
	itemNameIn.SetPrice(userNewItemPrice);
	cout << "Enter the item quantity: " << endl;
	cin >> userNewItemQuantity;
	cin.ignore();
	itemNameIn.SetQuantity(userNewItemQuantity);

	bool addItemToList = true;

	if (shoppingItems.size() > 0) {
		for (unsigned int i = 0; i < shoppingItems.size(); i++) {
			if ((shoppingItems.at(i).GetName() == (itemNameIn.GetName()))) {
				cout << "Item is already in cart. Nothing added." << endl;
				addItemToList = false;
				break;
			}
		}
		
	}

	if (addItemToList == true) {
		shoppingItems.push_back(itemNameIn);
	}
}

void ShoppingCart::RemoveItem(string itemToRemove) {
	
	bool itemInCart = false;
	if (shoppingItems.size() > 0) {
		for (unsigned int i = 0; i < shoppingItems.size(); i++) {
			if ((shoppingItems.at(i).GetName()) == itemToRemove) {
				shoppingItems.erase(shoppingItems.begin() + i);
				itemInCart = true;
			}
		}
		if (itemInCart == false) {
			cout << "Item not found in cart. Nothing removed." << endl;
		}
	}
	else {
		if ((shoppingItems.at(0).GetName()) == itemToRemove) {
			shoppingItems.erase(shoppingItems.begin());
		}
		else {
			cout << "Item not found in cart. Nothing removed." << endl;
		}
	}
}

void ShoppingCart::UpdateItemQuantity() {
	string itemToUpdate;
	int updatedQuantity;
	cout << "Enter the item name: " << endl;
	getline(cin, itemToUpdate);
	cout << "Enter the new quantity:" << endl;
	cin >> updatedQuantity;
	cin.ignore();

	bool itemInCart = false;
	for (int i = 0; i < shoppingItems.size(); i++) {
		if (shoppingItems.at(i).GetName() == itemToUpdate) {
			shoppingItems.at(i).SetQuantity(updatedQuantity);
			itemInCart = true;
			break;
		}
	}

	if (itemInCart == false) {
		cout << "Item not found in cart.Nothing modified." << endl;
	}
}

int ShoppingCart::GetNumItems() {
	int numItems = 0;
	
	for (int i = 0; i < shoppingItems.size(); i++) {
		numItems += shoppingItems.at(i).GetQuantity();
	}
	
	return numItems;
}

double ShoppingCart::GetTotPrice() {
	double totPrice = 0.0;

	for (int i = 0; i < shoppingItems.size(); i++) {
		totPrice += (shoppingItems.at(i).GetPrice() * shoppingItems.at(i).GetQuantity());
	}

	return totPrice;
}

void ShoppingCart::PrintItemsPrices(bool & itemsInCart) {
	
	
	for (int i = 0; i < shoppingItems.size(); i++) {
		shoppingItems.at(i).PrintItemCost(shoppingItems.at(i).GetName());
	}

}

void ShoppingCart::PrintDescriptions() {
	cout << costomerName << "'s Shopping Cart - " << shoppingDate << endl << endl;
	
	
	if (shoppingItems.size() > 0) {
		cout << "Item Descriptions" << endl;
		for (int i = 0; i < shoppingItems.size(); i++) {
			shoppingItems.at(i).PrintItemDescription(shoppingItems.at(i).GetName());
		}
	}
	else {
		cout << "Shopping cart is empty." << endl;
	}
	cout << endl;
}

