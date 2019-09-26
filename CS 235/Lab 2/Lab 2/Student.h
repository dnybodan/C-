#ifndef STUDENT
#define STUDENT
#include <string>
#include <sstream>

class Student {

public:
	Student(std::string sID) :
		studentID(sID) {}
	Student() {}
	virtual std::string getStudentID() const { return studentID; }
	virtual std::string toString() const = 0;
	~Student();

private:
	std::string studentID;
};

#endif