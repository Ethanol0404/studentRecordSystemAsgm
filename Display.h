#ifndef Input_type
#define Input_type

#include	<windows.h>
#include	<string>
#include	<vector>
#include	"Student.h"
#include	"InputValid.h"

using namespace std;
extern vector<Student>StuList;
void delay(string);
void delay_no_enter(string);
void fasterdelay(string);
void list_delay(string, string);
void list_delay_int(string, int);

void printStudent(ostream&);
bool PrintList(vector<Student>, int);
void printResult(vector<Student>);
#endif
