#include "Student.h"

std::string Student::toString() const {
	std::ostringstream stringOut;
	stringOut << studentID;
	return stringOut.str();
}

Student::~Student() {
}
