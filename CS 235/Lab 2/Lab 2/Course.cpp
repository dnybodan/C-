#include "Course.h"

Course::Course() {
}

std::string Course::toString() const {
	std::ostringstream stringOut;
	stringOut << courseName;
	return stringOut.str();
}

Course::~Course() {
}
