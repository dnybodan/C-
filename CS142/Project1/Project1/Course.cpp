#include "Course.h"



Course::Course()
{
	courseName = "none";
	courseDescription = "none";
	prerequisites = "n/a";
}

Course::Course(string courseNameIn, string courseDescriptionIn, string prerequisitesIn)
{
	courseName = courseNameIn;
	courseDescription = courseDescriptionIn;
	prerequisites = prerequisitesIn;
}


Course::~Course()
{
}

void Course::SetCourseName(string courseNameIn)
{
	courseName = courseNameIn;
}

string Course::GetCourseName()
{
	return courseName;
}

void Course::SetCourseDescription(string courseDescriptionIn)
{
	courseDescription = courseDescriptionIn;
}

string Course::GetCourseDescription()
{
	return courseDescription;
}

void Course::SetPrerequisites(string prerequisitesIn)
{
	prerequisites = prerequisitesIn;
}

string Course::GetPrerequisites()
{
	return prerequisites;
}
