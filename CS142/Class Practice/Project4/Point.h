#pragma once
class Point
{
public:
	Point();
	Point(double xValIn, double yValIn);

	void SetX(double xValIn);
	void SetY(double yValIn);
	double GetX();
	double GetY();
	void Print();
	void ShiftUp(double yValToIncreasBy);

private:
	double xVal;
	double yVal;
};

