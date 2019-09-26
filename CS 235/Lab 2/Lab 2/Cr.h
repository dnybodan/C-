#ifndef CR
#define CR
#include "Course.h"

class Cr : public Course {

public:
	Cr(std::string cName, std::string cRoom) :
		Course(cName), courseRoom(cRoom) {}
	Cr() {}
	std::string getCourseRoom() const { return courseRoom; }
	virtual std::string toString() const;
	~Cr();

private:
	std::string courseRoom;
	friend std::ostream& operator<< (std::ostream& os, const Cr& Cr) { //use to output object as a stream using << 
		os << Cr.toString();
		return os;
	}
};

#endif
