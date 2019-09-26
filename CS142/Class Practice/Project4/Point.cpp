#include "Point.h"
#include <iostream>
using namespace std;


Point::Point() {
	xVal = 0;
	yVal = 0;
}

Point::Point(double xValIn, double yValIn) {
	xVal = xValIn;
	yVal = yValIn;

}

void Point::ShiftUp(double yValToIncreasBy) {
	yVal = yVal + yValToIncreasBy;
}

void Point::Print() {
	cout << "(" << xVal << ", " << yVal << ")" << endl;
}

void Point::SetX(double xValIn) {
	xVal = xValIn;

}

void Point::SetY(double yValIn) {
	//this-> yVal = yVal; if parameter was same name, use 'this->'
	yVal = yValIn;
}

double Point::GetX() {
	return xVal;
}

double Point::GetY() {
	return yVal;
}