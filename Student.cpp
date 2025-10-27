#include <iostream>
#include "Student.h"


bool Student::calculateCurrentCGPA()
{
	double sum = 0;
	Exam temp;
	int total_credits = 0;

	if (exam_cnt == 0)
	{
		cout << "\n\nNo exam result yet.\n";
		return false;
	}

	else
	{
		totalCreditsEarned = 0;
		for (int i = 0; i < exam_cnt; i++)
		{

			total_credits = 0;
			for (int j = 0; j < exam[i].numOfSubjects; j++)
			{
				total_credits = total_credits + exam[i].sub[j].credit_hours;


			}

			//calculate total points
			sum = sum + (exam[i].gpa * total_credits);
			totalCreditsEarned = totalCreditsEarned + total_credits;

		}

		current_cgpa = sum / totalCreditsEarned;

		return true;

	}

}



Student::Student()
{
	name = "";
	id = "";
	course = "";
	phone = "";
	current_cgpa = 0;
	totalCreditsEarned = 0;
	exam_cnt = 0;

}



bool Student::compareName1(Student p2) {
	if (name.compare(p2.name) >= 0)
		return true;
	return false;
}


bool Student::compareID(Student p2) {
	if (id.compare(p2.id) == 0)
		return true;
	return false;
}


void Student::print(ostream& out)
{
	out << "\n\nName: " << name;
	out << "\nId: " << id;
	out << "\nCourse: " << course;
	out << "\nPhone No: " << phone;
	out << "\nCurrent CGPA: " << current_cgpa;
	out << "\nTotal Credits Earned: " << totalCreditsEarned;
	out << endl;


}
