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
			for (int i : choices) {
				if (value == choices[i]) {
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

void studentIdCheck(string) {

}