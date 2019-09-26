#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Student.h"
#include "Course.h"
#include "Snap.h"
#include "Cdh.h"
#include "Csg.h"
#include "Cr.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC   
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif
using namespace std;

int main(int argc, char * argv[]) {

	VS_MEM_CHECK

	//opening files
	if (argc < 3) {
		cerr << "Please provide name of input and output files";
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out) {
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	// define and fill vectors for snap, cdh, csg, crs
	vector<Snap> snaps;
	vector<Cdh> cdhs;
	vector<Csg> csgs;
	vector<Cr> crs;
	out << "Input Strings: " << endl;
	for (string line; getline(in, line);) {	// Read until EOF
		try {
			if ("snap(" == line.substr(0, 5)) {
				out << line << endl;
				string studentID = line.substr(5, line.find(',') - 5);
				line = line.substr(line.find(',') + 1);
				string studentName = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string studentAddress = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string studentPhone = line.substr(0, line.find(')'));
				snaps.push_back(Snap(studentID, studentName, studentAddress, studentPhone));
			}
			else if ("csg(" == line.substr(0, 4)) {
				out << line << endl;
				string courseName = line.substr(4, line.find(',') - 4);
				line = line.substr(line.find(',') + 1);
				string studentID = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string studentGrade = line.substr(0, line.find(')'));
				csgs.push_back(Csg(courseName, studentID, studentGrade));
			}

			else if ("cdh(" == line.substr(0, 4)) {
				out << line << endl;
				string courseName = line.substr(4, line.find(',') - 4);
				line = line.substr(line.find(',') + 1);
				string courseDay = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string courseTime = line.substr(0, line.find(')'));
				cdhs.push_back(Cdh(courseName, courseDay, courseTime));
			}

			else if ("cr(" == line.substr(0, 3)) {
				out << line << endl;
				string courseName = line.substr(3, line.find(',') - 3);
				line = line.substr(line.find(',') + 1);
				string room = line.substr(0, line.find(')'));
				crs.push_back(Cr(courseName, room));
			}

			else {
				throw line;
			}
		}
		catch (std::string badLine) {
			out << "**Error: " << badLine << endl;
		}
	}


	//outputting vectors
	out << endl;
	out << "Vectors:" << endl;
	for (unsigned int i = 0; i < snaps.size(); i++) {
		out << snaps[i] << endl;
	}
	for (unsigned int i = 0; i < csgs.size(); i++) {
		out << csgs[i] << endl;
	}
	for (unsigned int i = 0; i < cdhs.size(); i++) {
		out << cdhs[i] << endl;
	}
	for (unsigned int i = 0; i < crs.size(); i++) {
		out << crs[i] << endl;
	}

	//Course Grades
	out << endl;
	out << "Course Grades:" << endl;
	for (unsigned int i = 0; i < csgs.size(); i++) {
		for (unsigned int j = 0; j < snaps.size(); j++) {
			if (csgs.at(i).getStudentID() == snaps.at(j).getStudentID()) {
				out << csgs.at(i).getCourseName()
					<< "," << snaps.at(j).getStudentName()
					<< "," << csgs.at(i).getStudentGrade() 
					<< endl;
			}
		}
	}

	//Student Schedules
	out << endl;
	out << "Student Schedules: " << endl;
	for (unsigned int i = 0; i < snaps.size(); i++) {
		out << snaps.at(i).getStudentName()
			<< ", " << snaps.at(i).getStudentID()
			<< ", " << snaps.at(i).getStudentAddress()
			<< ", " << snaps.at(i).getStudentPhone()
			<< endl;
		for (unsigned int j = 0; j < csgs.size(); j++) {
			if (csgs.at(j).getStudentID() == snaps.at(i).getStudentID()) {
				out << "   " << csgs.at(j).getCourseName() << " ";

				ostringstream courseDayCombined;
				string courseTime;
				courseDayCombined.str() = "";
				for (unsigned int k = 0; k < cdhs.size(); k++) { // combine same course days
					if (csgs.at(j).getCourseName() == cdhs.at(k).getCourseName()) {
						courseDayCombined << cdhs.at(k).getCourseDay();
						courseTime = cdhs.at(k).getCourseTime();
					}
				}
				out << courseDayCombined.str() << " " << courseTime << ", ";
				
				
				
				for (unsigned int l = 0; l < crs.size(); l++) {
					if (csgs.at(j).getCourseName() == crs.at(l).getCourseName()) {
						out << crs.at(l).getCourseRoom() << endl;
					}
				}

			}
		}
		out << endl;
	}
	

	//clean up 
	snaps.clear();
	csgs.clear();
	cdhs.clear();
	crs.clear();

	in.close();
	out.close();

	return 0;
}