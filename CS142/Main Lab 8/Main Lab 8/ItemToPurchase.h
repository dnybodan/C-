#pragma once
#include<iostream>
#include<string>
using namespace std;


class ItemToPurchase {

public:

	~ItemToPurchase();
	ItemToPurchase(string initName = "none", string initDescription = "none", double initPrice = 0.0, int initQuantity = 0);
	void SetName(string nameIn);
	string GetName();
	void SetItemDescription(string itemDescriptionIn);
	string GetItemDescription();
	void SetPrice(double priceIn);
	double GetPrice();
	void SetQuantity(int quantityIn);
	int GetQuantity();
	void PrintItemCost(string itemIn);
	void PrintItemDescription(string itemIn);
	void Print();

private:
	string itemName;
	string itemDescription;
	double itemPrice;
	int itemQuantity;
};