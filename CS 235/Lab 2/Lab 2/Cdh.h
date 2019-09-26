#ifndef CDH
#define CDH
#include "Course.h"

class Cdh : public Course {

public:
	Cdh(std::string cName, std::string cDay, std::string cTime) :
		Course(cName), 
		courseDay(cDay), 
		courseTime(cTime) {}
	Cdh() {}
	std::string getCourseDay() const { return courseDay; }
	std::string getCourseTime() const { return courseTime; }
	virtual std::string toString() const;
	~Cdh();

private:
	std::string courseDay;
	std::string courseTime;
	friend std::ostream& operator<< (std::ostream& os, const Cdh& Cdh) { //use to output object as a stream using << 
		os << Cdh.toString();
		return os;
	}
};

#endif