#include <iostream>
#include <string>
#include <vector>
#include "Course.h"

using namespace std;

int main() {
	string userInput;
	string courseNameIn;
	string courseDescriptionIn;
	string prerequisitesIn;
	vector<Course*> courseList;
	Course * currCourse = nullptr;

	cout << "would you like to add a course? (add or quit)." << endl;
	cin >> userInput;
	cin.ignore();


	while (userInput != "quit") {
		cout << "what course?" << endl;
		getline(cin, courseNameIn);


	}






	return 0; 
}