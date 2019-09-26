#include "Csg.h"


std::string Csg::toString() const {

	std::ostringstream stringOut;
	stringOut << "csg(" << Course::toString()
		<< "," << Student::toString()
		<< "," << studentGrade
		<< ")";
	return stringOut.str();
}

Csg::~Csg() {
}
