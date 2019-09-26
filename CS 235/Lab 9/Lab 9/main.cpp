#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Set.h"
#include "HashMap.h"
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC   
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

int main(int argc, char * argv[])
{
	VS_MEM_CHECK
	//opening files
#if 1
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
#endif

	HashMap<string, string> Pokemon;
	HashMap<string, string> Move;
	HashMap<string, Set<string>> Effectives;
	HashMap<string, Set<string>> Ineffectivities;
	string line;
	
	//unit testing for Set.h and HashMap.h
	while (getline(in, line))
	{
		
		istringstream iss(line);
		string command;
		iss >> command;

		out << line;

		if (command == "Set:")
		{
			out << endl;
			Set<string> SetItems;
			string item;
			while (iss >> item)
			{
				SetItems.insert(item);
			}
			out << "[" << SetItems.toString() << "]" << endl << endl;
		}
		if (command == "Pokemon:")
		{
			out << endl;
			string key;
			string value;
			iss >> key;
			iss >> value;
			Pokemon[key] = value;
		}
		if (command == "Pokemon")
		{
			out <<  ": ";
			out << Pokemon.toString();
		}
		if (command == "Move:")
		{
			out << endl;
			string key;
			string value;
			iss >> key;
			iss >> value;
			Move[key] = value;
		}
		if (command == "Moves")
		{
			out << ": ";
			out << Move.toString();
		}
		if (command == "Effective:")
		{
			out << endl;
			string key;
			string value;
			iss >> key;
			//Effectives[key] = Set<string>();
			while (iss >> value)
			{
				Effectives[key].insert(value);
			}
			
		}
		if (command == "Effectivities")
		{
			out << ": ";
			out << Effectives.toString();
		}
		if (command == "Ineffective:")
		{
			out << endl;
			string key;
			string value;
			iss >> key;
			//Ineffectivities[key] = Set<string>();
			while (iss >> value)
			{
				Ineffectivities[key].insert(value);
			}
		}
		if (command == "Ineffectivities")
		{
			out << ": ";
			out << Ineffectivities.toString();
		}
		if (command == "Battle:")
		{
			out << endl;
			string Pokemon1;
			string Pokemon2;
			string Action1;
			string Action2;
			int damageAToB = 0;
			int damageBToA = 0;
			iss >> Pokemon1;
			iss >> Action1;
			iss >> Pokemon2;
			iss >> Action2;
			out << "\t" << Pokemon1 << "(" << Action1 << ") vs " << Pokemon2 << "(" << Action2 << ")" << endl;
			out << "\t";

			if (Effectives[Move[Action1]].count(Pokemon[Pokemon2]) == 1)
			{
				out << Pokemon1 << "'s " << Action1 << " is super effective against " << Pokemon2 << endl;
			}
			else if (Ineffectivities[Move[Action1]].count(Pokemon[Pokemon2]) == 1)
			{
				out << Pokemon1 << "'s " << Action1 << " is ineffective against " << Pokemon2 << endl;
			}
			else if (Effectives[Move[Action1]].count(Pokemon[Pokemon2]) == 0 && Ineffectivities[Move[Action1]].count(Pokemon[Pokemon2]) == 0)
			{
				out << Pokemon1 << "'s " << Action1 << " is effective against " << Pokemon2 << endl;
			}
			out << "\t";

			if (Effectives[Move[Action2]].count(Pokemon[Pokemon1]) == 1)
			{
				out << Pokemon2 << "'s " << Action2 << " is super effective against " << Pokemon1 << endl;
			}
			else if (Ineffectivities[Move[Action2]].count(Pokemon[Pokemon1]) == 1)
			{
				out << Pokemon2 << "'s " << Action2 << " is ineffective against " << Pokemon1 << endl;
			}
			else if (Effectives[Move[Action2]].count(Pokemon[Pokemon1]) == 0 && Ineffectivities[Move[Action2]].count(Pokemon[Pokemon1]) == 0)
			{
				out << Pokemon2 << "'s " << Action2 << " is effective against " << Pokemon1 << endl;
			}
			out << "\t";
			damageAToB = Effectives[Move[Action1]].count(Pokemon[Pokemon2]) - Ineffectivities[Move[Action1]].count(Pokemon[Pokemon2]);
			damageBToA = Effectives[Move[Action2]].count(Pokemon[Pokemon1]) - Ineffectivities[Move[Action2]].count(Pokemon[Pokemon1]);
			if ((damageAToB - damageBToA) == 0) out << "The battle between " << Pokemon1 << " and " << Pokemon2 << " is a tie." << endl;
			else if ((damageAToB - damageBToA) > 0) out << "In the battle between " << Pokemon1 << " and "<< Pokemon2 << ", " << Pokemon1 << " wins!" << endl;
			else if ((damageAToB - damageBToA) < 0) out << "In the battle between " << Pokemon1 << " and " << Pokemon2 << ", " << Pokemon2 << " wins!" << endl;
			out << endl;
		}
	}

	system("pause");
	return 0;
}