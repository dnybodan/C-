

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>  
#include <cstring>
#include <iomanip>
#include <new>
#include <cctype>
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;


/** Function returns the average score for each exam.
	@param int examIndex: the exam to be averaged
	@param double studentScores[][]: the array where exams are stored
	@param int numStudents: the index of student scores to be averaged
	@return double: averageScore
*/
double getAverageScore(int examIndex, int numStudents, double ** studentScores) {
	double averageScore = 0.0;
	double totalOfScores = 0.0;

	for (int i = 0; i < numStudents; i++) {
		totalOfScores += studentScores[i][examIndex];
	}

	averageScore = totalOfScores / numStudents;


	return averageScore;
}

/** Function that returns a students letter grade by comparing the students grade 
	@param averageScore: average score on test among all students
	@param studentScores: students score on test to be compared to the average
	@returns char: student letter grade
*/
char getGrade(double averageScore, double studentScore) {
	char studentGrade = ' ';
	
	if (abs(averageScore - studentScore) <= 5) {
		studentGrade = 'C';
	}
	else if (abs(averageScore - studentScore) <= 15 && abs(averageScore - studentScore) > 5) {
		if ((averageScore - studentScore) < 0) {
			studentGrade = 'B';
		}
		else {
			studentGrade = 'D';
		}
	}
	else if (abs(averageScore - studentScore) > 15) {
		if ((averageScore - studentScore) < 0) {
			studentGrade = 'A';
		}
		else {
			studentGrade = 'E';
		}
	}
	else {
		return 1;
	}

	return studentGrade;
}

/** Function numOfLetterGrades gives the number of students who achived a certain grade on a specific test
	@param letterGrade: the letter grade to be compared
	@param studentScores: students scores on test in array
	@param numStudents: number of students who took test 
	@param examIndex: which exam is being compared
	@returns int: number of students who achieved a specified letter grade
*/
int numOfLetterGrades(char letterGrade, double ** studentScores, int numStudents, int examIndex) {
	int numLetterGrades = 0;
	for (int i = 0; i < numStudents; i++) {
		if (getGrade(getAverageScore(examIndex, numStudents, studentScores), studentScores[i][examIndex]) == letterGrade) {
			numLetterGrades += 1;
		}
	}

	return numLetterGrades;
}


int main(int argc, char* argv[]) {
	
	VS_MEM_CHECK

	//opening files

	if (argc < 3) {
		cerr << "Not enough files to execute program";
		return 1;
	}

	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);

	if (!(in.is_open())) {
		cerr << "Cannot open " << argv[1];
		return 4;
	}

	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	
	if (!out) {
		in.close();
		cerr << "Cannot open " << argv[2];
		return 3;
	}


	//set up dynamic array

	int numStudents = 0;
	int numExams = 0;	
	in >> numStudents;
	in >> numExams;
	// Skip the rest of the line
	in.ignore(std::numeric_limits<int>::max(), '\n');
	double** studentScores = new double*[numStudents];
	for (int i = 0; i < numStudents; ++i) {
		studentScores[i] = new double[numExams];
	}
	//initialize studentName array
	string* studentNames = new string[numStudents];


	//reading information from input file

	string currStudentName;
	string firstName;
	string lastName;
	string line;
	double currScore;
	for (int i = 0; i < numStudents; ++i) {
		getline(in, line);
		istringstream inss(line);
		inss >> firstName >> lastName;
		currStudentName = (firstName + lastName);
		studentNames[i] = currStudentName;
		for (int j = 0; j < numExams; ++j) {
			inss >> currScore;
			studentScores[i][j] = currScore;
		}
	}
	

	//outputing information

	out << "Student Scores:" << endl;
	for (int i = 0; i < numStudents; i++) {
		out << setw(20) << right << studentNames[i] << " ";
		for (int j = 0; j < numExams; j++) {
			out << setw(7) << studentScores[i][j] << " ";
		}
		out << endl;
	}
	
	
	//Exam Averages

	out << "Exam Averages: " << endl;
	for (int i = 0; i < numExams; i++) {
		out << "\t" << "Exam " << i + 1 << " Average = " << fixed << setprecision(1) << setw(6) << right << getAverageScore(i, numStudents, studentScores) << endl;
	}

	//Student Exam Grades

	out << "Student Exam Grades:" << endl;
	for (int i = 0; i < numStudents; i++) {
		out << setw(20) << right << studentNames[i] << " ";
		for (int j = 0; j < numExams; j++) {
			out << setw(8) << right << fixed << setprecision(0) << studentScores[i][j]  << "(" << getGrade(getAverageScore(j, numStudents, studentScores), studentScores[i][j]) << ")";
		}
		out << endl;
	}

	//Exam Grades

	out << "Exam Grades: " << endl;
	for (int i = 0; i < numExams; i++) {
		out << "\t" << "Exam " << i + 1 << right << setw(5); 
		char letter = ' ';
		
		for (int j = 0; j < 5; j++) {
			if (j == 0) letter = 'A';
			else if (j == 1) letter = 'B';
			else if (j == 2) letter = 'C';
			else if (j == 3) letter = 'D';
			else if (j == 4) letter = 'E';
			out << numOfLetterGrades(letter, studentScores, numStudents, i);
			out << "(" << letter << ")" << " ";
		}
		out << endl;
	}

	


	//clean up

	

	for (int i = 0; i < numStudents; ++i) {
		delete[] studentScores[i];
	}
	delete[] studentScores;


	delete[] studentNames;
	
	
	
	out.close();
	in.close();

	return 0;
}