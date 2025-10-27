#ifndef Filter_type
#define Filter_type
#include	"Display.h"
#include	"Student.h"
#include	"InputValid.h"
#include	<cctype>
#include	<algorithm>

extern vector<Student> StuList;
bool mainFilter();
bool Standard_Filter();
bool Range_Filter();
bool Search();
bool multiSearch();
#endif
