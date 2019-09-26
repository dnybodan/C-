#ifndef CSG
#define CSG
#include "Snap.h"
#include "Course.h"

class Csg : public Student, public Course {

public:
	Csg(std::string cName, std::string sID, std::string sGrade) :
		Course(cName), Student(sID),
		studentGrade(sGrade) {}
	Csg() {}
	std::string getStudentGrade() const { return studentGrade; }
	virtual std::string toString() const;
	~Csg();

private:
	std::string studentGrade;
	friend std::ostream& operator<< (std::ostream& os, const Csg& csg) {//use to output object as a stream using << 
		os << csg.toString();
		return os;
	}
};

#endif
