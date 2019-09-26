#include "ExpressionManager.h"
const std::string OPEN = "[{(";
const std::string CLOSE = "]})";
const std::string OPERATORS = "+-*/%";
const std::string BRACKETS = "[{(]})";
const std::string PRECEDENCE = "11222";

#if 1
bool ExpressionManager::isOpen(string c)
{
	return OPEN.find(c) != std::string::npos; 
}

bool ExpressionManager::isClose(string c)
{
	return CLOSE.find(c) != std::string::npos; 
}

bool ExpressionManager::isOperator(string c)
{
	return OPERATORS.find(c) != std::string::npos;
}

bool ExpressionManager::isBracket(string c)
{
	return BRACKETS.find(c) != std::string::npos;
}

bool ExpressionManager::isOperand(string c)
{
	for (unsigned int i = 0; i < c.size(); ++i)
	{
		if (isdigit(c.at(i)))
		{
			return true;
		}
	}
	return false;
}

int ExpressionManager::getPrecedence(string c)
{
	int findPrecedence = 0;
	int precedenceValue = 0;
	if (isOperator(c))
	{
		findPrecedence = OPERATORS.find(c);
		precedenceValue = PRECEDENCE.at(findPrecedence);
	}
	else if (isBracket(c))
	{
		precedenceValue = 0;
	}

	return precedenceValue;
}

int ExpressionManager::stringToInt(string c)
{
	stringstream ss(c);
	int i = 0;
	ss >> i;
	return i;
}


#endif

std::string ExpressionManager::infix(void)
{
	stack<string> exp;
	stringstream ss(currExp);
	string currChar;
	string back;
	back = currExp.back();

	while (ss >> currChar)
	{
		if (isOpen(currChar))
		{
			exp.push(currChar);
		}
		else if (isClose(currChar))
		{
			if (exp.empty())
			{
				throw std::out_of_range("Unbalanced");
				break;
			}
			else
			{
				string checkChar = exp.top();
				exp.pop();
				if (OPEN.find(checkChar) != CLOSE.find(currChar))
				{
					throw std::out_of_range("Unbalanced");
					break;
				}
			}
		}
	}
	exp.empty();
	int operators = 0;
	int operands = 0;
	stack<string> infix;
	stringstream ns(currExp);

	while (ns >> currChar)
	{
		if (isOperator(currChar))
		{
			if (!(infix.empty()) && infix.top() == currChar)
			{
				throw 2;
				return "";
			}
			else
			{
				infix.push(currChar);
				operators++;
			}
		}
		else if (isOperand(currChar))
		{
			if (!(infix.empty()) && isOperand(infix.top()))
			{
				throw 1;
				return "";
			}
			else
			{
				infix.push(currChar);
				operands++;
			}
		}
		else if ((!isOperand(currChar)) && (!isOperator(currChar)) && (!isBracket(currChar)))
		{
			throw 3;
			return "";
		}
	}
	if ((operators + 1) < (operands))
	{
		throw 1;
		return "";
	}
	if ((operators + 1) > (operands))
	{
		throw 2;
		return "";
	}

	infix.empty();
	exp.empty();
	return currExp;
}

std::string ExpressionManager::postfix(void)
{
	stringstream ss(currExp);
	string currChar;
	stack<string> operators;
	stack<string> infix;
	stringstream postfix;
	
	while (ss >> currChar)
	{
		infix.push(currChar);
		if (isOperand(currChar))
		{

			postfix << currChar << " ";
		}
		else if (isOpen(currChar))
		{
			operators.push(currChar);
		}
		else if (isClose(currChar)) 
		{
			while (!isOpen(operators.top()) && (operators.size() != 0)) 
			{
				postfix << operators.top() <<  " ";
				operators.pop();
			}
			operators.pop();
		}
		else if (isOperator(currChar))
		{
			if (operators.empty())
			{
				operators.push(currChar);
			}
			else if (getPrecedence(currChar) > getPrecedence(operators.top()))
			{
				operators.push(currChar);
			}
			else
			{
				while ((!operators.empty()) && (getPrecedence(currChar) <= getPrecedence(operators.top())))
				{
					postfix << operators.top() << " ";
					operators.pop();
				}
				operators.push(currChar);
			}
		}
	}
	while (!operators.empty()) 
	{
		postfix << operators.top() << " ";
		operators.pop();
	}
	post = postfix.str();
	operators.empty();
	infix.empty();
	return postfix.str();
}

int ExpressionManager::value(void)
{
	stack<int> operands;
	stringstream ss(post);
	string currToken;
	int right = 0;
	int left = 0;
	int answer = 0;
	while (ss >> currToken)
	{
		if (isOperand(currToken))
		{
			int newInt = 0;
			newInt = stringToInt(currToken);
			operands.push(newInt);
		}
		else if (isOperator(currToken))
		{
			right = operands.top();
			operands.pop();
			left = operands.top();
			operands.pop();
			if (currToken == "+")
			{
				answer = left + right;
			}
			else if (currToken == "-")
			{
				answer = left - right;
			}
			else if (currToken == "*")
			{
				answer = left * right;
			}
			else if (currToken == "/")
			{
				answer = left / right;
			}
			else if (currToken == "%")
			{
				answer = left % right;
			}
			 //fixme
			operands.push(answer);
		}
	}
	return operands.top();
}

