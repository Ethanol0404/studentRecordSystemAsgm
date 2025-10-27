#include	<iostream>
#include	<iomanip>
#include	<fstream>
#include	"Display.h"

void printStudent(ostream& out) {
	for (int i = 0; i < StuList.size(); i++) {
		StuList[i].print(out);
	}
}
void delay(string word) {

	for (int i = 0; i < word.length(); i++) {
		cout << word[i];
		Sleep(10);
	}
	Sleep(100);
	cout << endl;
}

void delay_no_enter(string word) {

	for (int i = 0; i < word.length(); i++) {
		cout << word[i];
		Sleep(30);
	}
	Sleep(100);
}

void fasterdelay(string word) {

	for (int i = 0; i < word.length(); i++) {
		cout << word[i];
		Sleep(1);
	}
	cout << endl;
}

void list_delay(string word1, string word2) {

	cout << left << setw(14) << word1;

	for (int i = 0; i < word2.length(); i++) {
		cout << word2[i];
		Sleep(10);

	}
	cout << right << setw(21 - word2.length()) << "|";
}

void list_delay_int(string word1, int word2) {

	cout << left << setw(14) << word1;
	cout << setw(20) << left << word2;
	Sleep(20);
	cout << right << "|";
}

bool PrintList(vector<Student>stuList, int source) {
	int studentCount = stuList.size();

	if (!stuList.empty()) {
		if (source == 1) {//output to screen

			for (int i = 0; i < studentCount; i++) {
				cout << "\n*******************************************STUDENT " << i << "****************************************************";
				stuList[i].print(cout);

				if (stuList[i].exam_cnt != 0) {


					cout << "\n\n--------------------------------------------------PAST EXAM RESULT--------------------------------------------------------" << endl;
					for (int j = 0; j < stuList[i].exam_cnt; j++) {
						stuList[i].exam[j].print(cout);
					}

				}
				else {
					cout << "THIS STUDENT HAVENT'T TAKEN ANY EXAM YET. " << endl;
				}
				cout << "*******************************************STUDENT " << i << "****************************************************\n\n\n";
			}

		}
		else {//output to text file
			string input;
			bool inputCheck;
			cout << "Enter file name you want to save\n";
			do {
				inputCheck = true;
				getline(cin, input);
				if (input.size()<4 || input.substr(input.size()-4)!=".txt") {
					cout << "File nam must be end with \".txt\"\n";
					inputCheck = false;
				}
				
			} while (!inputCheck);
			
			ofstream outFile(input);

			for (int i = 0; i < studentCount; i++) {
				outFile << "*******************************************STUDENT " << i << "****************************************************";

				if (stuList[i].exam_cnt != 0) {
					stuList[i].print(outFile);
					outFile << "\n\n--------------------------------------------------PAST EXAM RESULT--------------------------------------------------" << endl;
					for (int j = 0; j < stuList[i].exam_cnt; j++) {
						stuList[i].exam[j].print(outFile);
					}
					outFile << "*******************************************STUDENT " << i << "****************************************************\n\n\n\n";
				}
				else {
					outFile << "THIS STUDENT HAVENT'T TAKEN ANY EXAM YET. " << endl;
				}
			}
			cout << "Results are exported successfully. Please check the text file (" << input << ") given.\n\n";
			outFile.close();
		}

		return true;
	}
	else {
		cout << "The list is empty" << endl;
		return false;
	}
}

void printResult(vector<Student>list) {
	cout << "Do you want to display results? (Y/N): "; //prompt user to output
	char dumChoice[10];
	int choice2;

	if (yesNo()) {
		cout << "Please select how do you want to display the results: On Screen (1) / In Text File (2): ";
		do {//input validation
			cin.getline(dumChoice, 10);
			choice2 = input_valid(dumChoice);
			if (choice2 != 1 && choice2 != 2) {
				cout << "\nPlease input only 1 or 2.:";
			}
		} while (choice2 != 1 && choice2 != 2);
		PrintList(list, choice2);
		cout << "**Please remember to copy data to a safe place to prevent loss of data.\n";
	}
}