#ifndef Insert_type
#define Insert_type
#include	"Display.h"
#include	"Student.h"
#include	"InputValid.h"
#include	<vector>

extern vector<Student> StuList; //extends visibility of the variable to multiple source file
//bool Insert(vector<Student>*StuList);  //if use pointer
bool Insert();
bool readStuRecord();
bool readStuExam();
void insertNewStudent();
bool insertNewExam();
bool insertNewExam_id(string id);
#endif