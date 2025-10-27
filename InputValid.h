#ifndef InputValid_type
#define InputValid_type
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "Student.h"

using namespace std;
extern vector<Student> StuList;
int input_valid(char input[]);
int input_valid_string(string &input);
double input_valid_double(string &input);
vector<int> handleChoices(string& input, int max);
string studentIdCheck();
string studentIdCheckDuplicate();
bool yesNo();
int yearCheck();
int trimesterCheck();
string courseCheck();
string phoneCheck();
#endif