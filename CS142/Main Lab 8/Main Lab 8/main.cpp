//Daniel Nybo
//dnybo.dan@gmail.com
//Prof. Wood Section 8
//Lab 8 doveloped in Visual Studio

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <iomanip>
#include "ItemToPurchase.h"
#include "ShoppingCart.h"

using namespace std;

int main() {
	string itemNameIn;
	ItemToPurchase currItem;
	double itemPriceIn = 0.0;
	int itemQuantityIn = 0;
	string userInput;
	string userName;
	string shoppingDate;

	cout << "Enter Customer's Name:" << endl;
	getline(cin, userName);
	cout << "Enter Today's Date:" << endl;
	getline(cin, shoppingDate);

	ShoppingCart userCart(userName, shoppingDate);


	while (userInput != "quit") {
		cout << "Enter option: " << endl;
		cin >> userInput;
		cin.ignore();
			
		if (userInput == "options") {
			cout << "MENU" << endl;
			cout << "add - Add item to cart" << endl;
			cout << "remove - Remove item from cart" << endl;
			cout << "change - Change item quantity" << endl;
			cout << "descriptions - Output items' descriptions" << endl;
			cout << "cart - Output shopping cart" << endl;
			cout << "options - Print the options menu" << endl;
			cout << "quit - Quit" << endl;
		}

		else if (userInput == "add") {
			userCart.AddItem(currItem);
		}

		else if (userInput == "cart") {
			cout << userCart.GetCostomerName() << "'s Shopping Cart - " << userCart.GetCostomerDate() << endl;
			bool itemsInCart = true;
		
			if (userCart.GetNumItems() > 0) {
				cout << "Number of Items: " << userCart.GetNumItems() << endl << endl;
				userCart.PrintItemsPrices(itemsInCart);

			}
			else {
				cout << "Shopping cart is empty." << endl << endl;
				itemsInCart = false;
			}

			if (itemsInCart == true) {
				cout << endl << "Total: $" << userCart.GetTotPrice() << endl << endl;
			}
		}

		else if (userInput == "remove"){
			string userRemoveItemName;
			cout << "Enter name of the item to remove: " << endl;
			getline(cin, userRemoveItemName);
			

			userCart.RemoveItem(userRemoveItemName);
		}

		else if (userInput == "change") {
			userCart.UpdateItemQuantity();

		}

		else if (userInput == "descriptions") {
			userCart.PrintDescriptions();
		}
		
		else if (userInput == "quit") {
			break;
		}

		else {
			cout << "MENU" << endl;
			cout << "add - Add item to cart" << endl;
			cout << "remove - Remove item from cart" << endl;
			cout << "change - Change item quantity" << endl;
			cout << "descriptions - Output items' descriptions" << endl;
			cout << "cart - Output shopping cart" << endl;
			cout << "options - Print the options menu" << endl;
			cout << "quit - Quit" << endl;
		}

	}
	cout << "Goodbye." << endl;

	//system("pause");
	return 0;
}