#pragma once
#include<iostream>
#include<string>
using namespace std;


class ItemToPurchase {

public:

	ItemToPurchase();
	~ItemToPurchase();
	void SetName(string nameIn);
	string GetName();
	void SetPrice(double priceIn);
	double GetPrice();
	void SetQuantity(int quantityIn);
	int GetQuantity();
	void Print();

private:
	string itemName;
	double itemPrice;
	int itemQuantity;

};