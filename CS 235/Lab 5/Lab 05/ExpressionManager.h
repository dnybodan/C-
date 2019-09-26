#ifndef EXPRESSION_MANAGER_H
#define EXPRESSION_MANAGER_H
#include "ExpressionManagerInterface.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;
class ExpressionManager : public ExpressionManagerInterface
{
private:
	string currExp;
	string post;

public:

	ExpressionManager() {}

	~ExpressionManager() {}
	/*setCurrExpression sets the expression to be operated on
	@param currE is the current Expression*/
	void setCurrExpression(std::string currE) { currExp = currE; }
	/*isOpen checks to see if a char is an open bracket/brace/or parenthesis
	@param c is a char to be checkd*/
	bool isOpen(string c);
	/*isClose checks to see if char is closed bracket/brace/or parenthesis
	@param c is char to be checked*/
	bool isClose(string c);
	/*isOperator check if a char is an operator
	@param c is char to be checked*/
	bool isOperator(string c);
	/*isBracket checks if char is a bracket*/
	bool isBracket(string c);
	/*stringToInt changes a string int value to an int
	@param c is the string to be changed to int*/
	int stringToInt(string c);
	bool isOperand(string c);
	/*getPrecedence returns the precedence value of an operator
	@param c to be checked*/
	int getPrecedence(string c);
	
	/** Return the integer value of the infix expression */
	virtual int value(void);

	/** Return the infix items from the expression
		Throw an error if the expression
		1) is not balanced.
		2) the number of operators IS NOT one less than the number of operands.
		3) there are adjacent operators. */
	virtual std::string infix(void);

	/** Return a postfix representation of the infix expression */
	virtual std::string postfix(void);

	/** (BONUS) Return a prefix representation of the infix expression */
	virtual std::string prefix(void)
	{
		return "NOT IMPLEMENTED";
	}

	/** Return the infix vector'd expression items */
	virtual std::string toString() const { return currExp; }
};
#endif //EXPRESSION_MANAGER_H
