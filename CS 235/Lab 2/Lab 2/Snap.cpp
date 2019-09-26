#include "Snap.h"

std::string Snap::toString() const {

	std::ostringstream subString;
	subString << "snap(" << Student::toString()
		<< "," << studentName
		<< "," << studentAddress
		<< "," << studentPhone
		<< ")";

	return subString.str();
}

Snap::~Snap() {
}



