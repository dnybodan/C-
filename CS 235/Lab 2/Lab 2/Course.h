#ifndef COURSE
#define COURSE
#include <string>
#include <sstream>

class Course {

public:
	Course(std::string cName) :
	courseName(cName) {}
	Course();
	virtual std::string getCourseName() { return courseName; }
	virtual std::string toString() const = 0;
	~Course();
private:
	std::string courseName;
	
};

#endif