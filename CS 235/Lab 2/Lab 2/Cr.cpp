#include "Cr.h"


std::string Cr::toString() const {

	std::ostringstream stringOut;
	stringOut << "cr(" << Course::toString()
		<< ", " << courseRoom
		<< ")";
	return stringOut.str();
}

Cr::~Cr() {
}
