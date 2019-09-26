#include<iostream>
#include<cmath>
#include"Point.h"

using namespace std;

int main() {
	Point myPoint(2, 3);
	
	myPoint.Print();

	myPoint.ShiftUp(7);
	myPoint.Print();

	system("pause");
	return 0;
}