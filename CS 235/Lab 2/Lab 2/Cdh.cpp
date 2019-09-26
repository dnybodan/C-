#include "Cdh.h"

std::string Cdh::toString() const {
	
	std::ostringstream stringOut;
	stringOut << "cdh(" << Course::toString()
		<< ", " << courseDay
		<< ", " << courseTime
		<< ")";
	return stringOut.str();
}

Cdh::~Cdh() {
}
