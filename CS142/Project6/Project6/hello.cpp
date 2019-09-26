#include <iostream>
#include <fstream>
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

int main(int argc, char* argv[])
{
	VS_MEM_CHECK			// check for memory leaks

		ostream& out = (argc > 2) ? *(new ofstream(argv[2])) : cout;
	if (!out) return 2;
	out << "Hello, World!";
	if (&out != &cout) delete(&out);

	return 0;
}