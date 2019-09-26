#pragma once
#include "ItemToPurchase.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class ShoppingCart {
public:
	ShoppingCart(string costomerNameIn = "none", string shoppingDateIn = "January 1, 2016");
	~ShoppingCart();
	string GetCostomerName();
	string GetCostomerDate();
	void AddItem(ItemToPurchase itemNameIn);
	void RemoveItem(string itemToRemove);
	void UpdateItemQuantity();
	int GetNumItems();
	double GetTotPrice();
	void PrintItemsPrices(bool & itemsInCart);
	void PrintDescriptions();

private:
	string costomerName;
	string shoppingDate;
	vector<ItemToPurchase> shoppingItems;
};

