#pragma once
#include <iostream>
#include <string>

using namespace std;

class Course


{
public:
	Course();
	Course(string courseNameIn, string courseDescriptionIn, string prerequisitesIn);
	~Course();
	void SetCourseName(string courseNameIn);
	string GetCourseName();
	void SetCourseDescription(string courseDescriptionIn);
	string GetCourseDescription();
	void SetPrerequisites(string prerequisitesIn);
	string GetPrerequisites();
	 
private:
	string courseName;
	string courseDescription;
	string prerequisites;

};

