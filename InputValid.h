#ifndef InputValid_type
#define InputValid_type
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;
int input_valid(char input[]);
int input_valid_string(string &input);
double input_valid_double(string &input);
vector<int> handleChoices(string& input, int max);

#endif