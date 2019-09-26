#ifndef SNAP
#define SNAP
#include "Student.h"
#include <ostream>
#include <ios>
#include <iostream>


class Snap : public Student {

public:
	Snap(std::string sID, std::string sName, std::string sAddress, std::string sPhone) :
		Student(sID), 
		studentName(sName), 
		studentAddress(sAddress), 
		studentPhone(sPhone) {}
	Snap() {}
	std::string getStudentName() const { return studentName; }
	std::string getStudentAddress() const { return studentAddress; }
	std::string getStudentPhone() const { return studentPhone; }
	virtual std::string toString() const;
	~Snap();
	
private:
	std::string studentName;
	std::string studentAddress;
	std::string studentPhone;
	friend std::ostream& operator<< (std::ostream& os, const Snap& snap) {  //use to output object as a stream using << 
		os << snap.toString();
		return os;
	}
};

#endif