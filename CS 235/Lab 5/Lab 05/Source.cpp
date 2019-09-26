#include "ExpressionManager.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <fstream>

using namespace std;

int main(int argc, char * argv[])
{
	//opening files

	if (argc < 3)
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}
  


	string line;
	string userInput;
	ExpressionManager currExpression;
	while (getline(in, line)) //reads until eof
	{
		try
		{
			stringstream ss(line);
			out << ss.str() << " ";
			ss >> userInput;
			if (userInput == "Expression:")
			{
				string expression;
				expression = line.substr(11, line.find("\n"));
				currExpression.setCurrExpression(expression);
			}
			else
			{
				if (userInput == "Infix:")
				{
					out << currExpression.infix();
				}
				else if (userInput == "Postfix:")
				{
					if(currExpression.infix() != "")
					{ 
						out << currExpression.postfix();
					}
					else
					{
						out << currExpression.infix(); 
					}
				}
				else if (userInput == "Prefix:")
				{
					if (currExpression.infix() != "")
					{
						out << currExpression.prefix();
					}
					else
					{
						out << currExpression.infix();
					}
				}
				else if (userInput == "Value:")
				{
					if (currExpression.infix() != "")
					{
						out << currExpression.value();
					}
					else
					{
						out << currExpression.infix();
					}

				}
			}
		}
		catch (out_of_range)
		{
			out << "Unbalanced";
		}
		catch (int i)
		{
			if (i == 1)
			{
				out << "Missing Operator";
			}
			if (i == 2)
			{
				out << "Missing Operand";
			}
			if (i == 3)
			{
				out << "Illegal Operator";
			}
		}
		out << endl;
	}

	return 0;
}