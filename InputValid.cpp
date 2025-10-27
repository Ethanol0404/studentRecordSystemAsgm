#include "inputValid.h"

int input_valid(char input[]) {//input check: Make sure the input is not alphabet or symbol
	bool val;
	int value;
	do {
		val = true;
		if (strlen(input) == 0) {
			val = false;
		}
		for (int a = 0; a < strlen(input); a++) {
			if (!isdigit(input[a])) {
				val = false;
			}
		}
		if (val == true) {
			value = stoi(input);
		}
		else {
			cout << "Please enter number digit: ";
			cin.getline(input, 10);
		}
	} while (val == false);

	return value;
}

int input_valid_string(string &input) {//pass by reference
	bool val;
	int value;
	do {
		val = true;
		if (input.empty()) {
			val = false;
		}
		for (int a = 0; a < input.size(); a++) {
			if (!isdigit(input[a])) {
				val = false;
				break;
			}
		}
		if (val == true) {
			value = stoi(input);
		}
		else {
			cout << "Please enter number digit: ";
			getline(cin, input);
		}
	} while (val == false);

	return value;
}

double input_valid_double(string &input) {//input check: Make sure the input is not alphabet or symbol
	bool val;
	double value;
	do {
		val = true;
		if (input.empty()) {
			val = false;
			break;
		}
		for (int a = 0; a < input.size(); a++) {
			if (!isdigit(input[a])) {
				val = false;
			}
		}
		if (val == true) {
			value = stod(input);
		}
		else {
			cout << "Please enter number digit: ";
			getline(cin, input);
		}
	} while (val == false);

	return value;
}

vector<int>handleChoices(string& input, int max) {
	vector<int> choices;
	size_t start = 0;
	size_t end;
	bool inputCheck, duplicateCheck;

	while ((end = input.find(" ", start)) != string::npos) {
		string token = input.substr(start, end - start);
		inputCheck = true;

		// Skip empty tokens (e.g., double spaces)
		if (token.empty()) {
			start = end + 1;
			continue;
		}

		for (char c : token) {
			if (!isdigit(c)) {
				cout << token << " is ignored\n";
				inputCheck = false;
				break;
			}
		}

		if (inputCheck) {
			duplicateCheck = false; //reset
			int value = stoi(token);
			for (int exist : choices) {
				if (value == exist) {
					cout << token << " is duplicate and ignored\n";
					duplicateCheck = true;
					break;
				}
			}
			if (!duplicateCheck && ((value >= 1 && value <= max))) {
				choices.push_back(value);
			}
			else {
				cout << token << " is ignored\n";
			}
		}

		start = end + 1; //whether true or false will executed
	}
	// Handle last token 
	string token = input.substr(start);
	inputCheck = true;

	for (char c : token) {
		if (!isdigit(c)) {
			cout << token << " is ignored\n";
			inputCheck = false;
			break;
		}
	}

	if (inputCheck) {
		duplicateCheck = false; //reset
		int value = stoi(token);
		for (int exist : choices) {
			if (value == exist) {
				cout << token << " is duplicate and ignored\n";
				duplicateCheck = true;
				break;
			}
		}
		if (!duplicateCheck && ((value >= 1 && value <= max))) {
			choices.push_back(value);
		}
		else {
			cout << token << " is ignored\n";
		}
	}
	return choices;
}

string studentIdCheck() {
	string input;
	bool format;
	do {
		getline(cin, input);
		format = true;
		if (input.length() != 7) {
			format = false;
		}
		for (int i = 0; i < input.length(); i++) {
			if (!isdigit(input[i])) {
				format = false;
			}
			break;
		}
		if (!format) {
			cout << "Student ID must digit only and exact 7 character. Please try again\n";
		}
	} while (!format);
	return input;
}

string studentIdCheckDuplicate(){
	string input;
	bool format;
	do {
		format = true;
		getline(cin, input);
		if (input.length() != 7) {
			format = false;
		}
		for (int i = 0; i < input.length(); i++) {
			if (!isdigit(input[i])) {
				format = false;
			}
			break;
		}
		if (!format) {
			cout << "Student ID must digit only and exact 7 character. Please try again\n";
		}
		if (!StuList.empty()) {
			for (Student student : StuList) {
				if (input.compare(student.id) == 0) {
					cout << "Duplicate ID " <<input << ". Please try again\n";
					format = false;
					break;
				}
			}
		}
	} while (!format);
	return input;
}

bool yesNo() {
	cout << endl;
	char comfirm = ' ';
	do {
		cin >> comfirm;
		cin.ignore();
		if (tolower(comfirm) != 'y' && tolower(comfirm) != 'n') {
			cout << "invalid. Please type only 'y' and 'n'\n";
		}

	} while (tolower(comfirm) != 'y' && tolower(comfirm) != 'n');
	if (tolower(comfirm) == 'y') {
		return true;
	}
	else {
		return false;
	}
}

int yearCheck() {
	int year;
	bool yearCheck;
	string input;
	cout << "Year: \n";
	do {
		yearCheck = true;
		getline(cin, input);
		if (input.size() != 4) {
			cout << "This is not a year. Please try again.\n";
			yearCheck = false;
		}
		else {
			year = input_valid_string(input);
		}
	} while (!yearCheck);

	return year;
}

int trimesterCheck() {
	int trimester;
	bool trimesterCheck;
	string input;

	cout << "Enter trimester\nOption 1\nOption 5\nOption 10\n";
	do {
		trimesterCheck = true;
		getline(cin, input);
		trimester = input_valid_string(input);
		if (trimester != 1 && trimester != 5 && trimester != 10) {
			trimesterCheck = false;
			cout << "Trimester incorrect. Try again.\n";
		}

	} while (!trimesterCheck);

	return trimester;
}

string courseCheck() {
	bool format;
	string input;
	do {
		format = true;
		getline(cin, input);
		if (input.length() != 3) {
			format = false;
		}
		for (int i = 0; i < input.length(); i++) {
			if (!isalpha(input[i])) {
				format = false;
				break;
			}
			input[i] = toupper(input[i]);
		}
		if (!format) {
			cout << "Course ID must be exact 3 character and must be character only\n";
		}

	} while (!format);
	return input;
}

string phoneCheck() {
	bool format;
	string input;
	do {
		format = true;
		cout << "Phone Number: ";
		getline(cin, input);
		if (input.length() != 10) {
			format = false;
		}
		for (int i = 0; i < input.length(); i++) {
			if (!isdigit(input[i])) {
				format = false;
				break;
			}
		}
		if (!format) {
			cout << "Phone Number must be exact 10 character and must be digit only\n";
		}


	} while (!format);
	return input;
}