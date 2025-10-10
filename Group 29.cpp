#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<cctype>
#include<cstring>
#include<windows.h> //decoration (delay text speed)

using namespace std;

void Switch();
void Insert();
void Filter();
int filter_subs(string);	//process subject names to filter
string subs_filter[15];		//global variable to store subject name
void Search();
void Edit();
void editname(int);
void editform(int);
void editsubject(int);
void Delete();
void View();

//decoration (delay text speed)
void delay(string);
void delay_no_enter(string);
void fasterdelay(string);
void list_delay(string, string);
void list_delay_int(string, int);

void outputFile();			//outFile
int student_num();			//inFile and count student total
int input_valid(char[]);	//input check: Make sure the input is not alphabet or symbol
string toLower(string);		// change all string to small capital letter
string subs_name[] = { "BM", "BI", "BC", "Math", "Sci", "Sejarah", "Geo" };
string subs_name_alt[] = { "BM: ", "BI: ", "BC: ", "Math: ", "Sci: ", "Sejarah: ", "Geo: " };
int stu_total;

struct student {
	char ID[15];
	char name[50];
	int form = 0;
	int sub[7] = { 0 };
}stu[50], stu_sort[50], stu_fil[50], stu_sea[50];

int main() {
	char reply;
	stu_total = student_num();

	// Menu system
	do {
		system("cls");//clear screen
		fasterdelay("========================================");
		delay(" Welcome to JKJT Student Admin System ");
		fasterdelay("========================================");
		Sleep(100);

		cout << "Main Menu: " << endl;
		cout << "1. Insert" << endl;
		cout << "2. Filter/Search" << endl;
		cout << "3. Modify" << endl;
		cout << "4. View Result" << endl;

		cout << "Enter 1-4 that you wish to proceed: ";

		Switch();
		cout << endl;
		cout << "Do you want to return to menu? (Press Y to return. Press any key to quit): ";
		cin >> reply;
		cin.ignore();
		cout << endl;

	} while (tolower(reply) == 'y');
	outputFile();
	fasterdelay("===================================================================================");
	delay("All student's informations are record successfully. Thank you for using our service");
	fasterdelay("===================================================================================");

	system("pause");
	return 0;
}

void Switch() {
	int choice, m1, g;
	char fReply, mReply, vReply, choose[10];

	do {//input validation
		cin.getline(choose, 10);
		choice = input_valid(choose);//input check: check the input is alphabet or symbol

		switch (choice) {
		case 1:
			Insert();
			break;
		case 2:
			do {
				system("cls");
				int input;
				cout << "Please choose the function you wish to proceed with:" << endl;
				cout << "1. Filter" << endl;
				cout << "2. Search" << endl;
				cout << "Choice: ";

				do {
					cin.getline(choose, 10);
					input = input_valid(choose);

					switch (input) {
					case 1:
						Filter();
						break;
					case 2:
						Search();
						break;
					default:
						cout << "Please choose either 1 or 2: ";
						break;
					}
				} while (input != 1 && input != 2);
				cout << "Do you want to continue using Filter/Search? (Press Y to continue. Press any key to quit): ";
				cin >> fReply; //prompt user to continue the module
				cin.ignore();
			} while (tolower(fReply) == 'y');
			break;

		case 3:

			do {
				system("cls");
				cout << "Please select your choice: " << endl;
				cout << "1. Edit" << endl;
				cout << "2. Delete" << endl;
				cout << "Choice: ";
				do {
					cin.getline(choose, 10);
					m1 = input_valid(choose);

					if (m1 == 1) {
						Edit();
					}
					else if (m1 == 2) {
						Delete();
					}
					else {
						cout << "Please enter either 1 or 2: ";
					}
				} while (m1 < 1 || m1>2);

				//updated list
				system("cls");
				//make 3 columns in a row, g = no. of rows
				if (stu_total % 3 == 0) {	// if stu_total is divisible by 3
					g = stu_total / 3;		// normal calculation for number of rows
				}
				else {						// if stu_total is not divisible by 3
					g = stu_total / 3 + 1;	// extra row because it will round down the value of g
				}
				cout << "Updated List: " << endl << endl;
				for (int a = 0; a < g; a++) {
					if (a != stu_total / 3) {			//make full columns (3 student) in 1 row if it is not the last row 
						for (int b = 0; b < 3; b++) {	// b = student
							list_delay("Student ID: ", stu[3 * a + b].ID); // 3 * a + b is the general equation to print out the correct student details for each column
						}
						cout << endl;
						for (int b = 0; b < 3; b++) {
							list_delay("Student name: ", stu[3 * a + b].name);
						}
						cout << endl;
						for (int b = 0; b < 3; b++) {
							list_delay_int("Form: ", stu[3 * a + b].form);
						}
						cout << endl;
						for (int b = 0; b < 7; b++) {// b=subject c=student
							for (int c = 0; c < 3; c++) {
								list_delay_int(subs_name_alt[b], stu[3 * a + c].sub[b]);
							}
							cout << endl;
						}
					}
					else {											// print out incomplete columns in last row
						for (int b = 0; b < stu_total % 3; b++) {	 // b will loop until the remainder value
							list_delay("Student ID: ", stu[3 * a + b].ID);
						}
						cout << endl;
						for (int b = 0; b < stu_total % 3; b++) {
							list_delay("Student name: ", stu[3 * a + b].name);
						}
						cout << endl;
						for (int b = 0; b < stu_total % 3; b++) {
							list_delay_int("Form: ", stu[3 * a + b].form);
						}
						cout << endl;
						for (int b = 0; b < 7; b++) {
							for (int c = 0; c < stu_total % 3; c++) {
								list_delay_int(subs_name_alt[b], stu[3 * a + c].sub[b]);
							}
							cout << endl;
						}
					}
					cout << "=======================================================================================================" << endl;
				}
				cout << "Do you want to continue to edit or delete? (Press Y to continue. Press any key to quit): ";
				cin >> mReply;
				cin.ignore();
			} while (tolower(mReply) == 'y');
			outputFile();
			break;

		case 4:
			do {
				system("cls");
				View();
				cout << "Do you want to continue to view result? (Press Y to continue. Press any key to quit) ";
				cin >> vReply;
			} while (tolower(vReply) == 'y');
			break;

		default:
			cout << "The valid choice only 1-4, Please Enter again: "; //prompt user to reinput if the choice is invalid
			Switch();
			break;
		}
	} while (choice < 1 || choice > 4);
}

void Insert() {
	char choice, marks[10], forms[10];
	int index, g;
	bool val, val2 = false, format;

	do {
		system("cls");

		// print out current list of students
		if (stu_total % 3 == 0) {
			g = stu_total / 3;
		}
		else {
			g = stu_total / 3 + 1;
		}
		cout << "Current list: " << endl << endl;
		for (int a = 0; a < g; a++) {
			if (a != stu_total / 3) {
				for (int b = 0; b < 3; b++) {
					list_delay("Student ID: ", stu[3 * a + b].ID);
				}
				cout << endl;
				for (int b = 0; b < 3; b++) {
					list_delay("Student name: ", stu[3 * a + b].name);
				}
				cout << endl;
				for (int b = 0; b < 3; b++) {
					list_delay_int("Form: ", stu[3 * a + b].form);
				}
				cout << endl;
				for (int b = 0; b < 7; b++) {
					for (int c = 0; c < 3; c++) {
						list_delay_int(subs_name_alt[b], stu[3 * a + c].sub[b]);
					}
					cout << endl;
				}
			}
			else {
				for (int b = 0; b < stu_total % 3; b++) {
					list_delay("Student ID: ", stu[3 * a + b].ID);
				}
				cout << endl;
				for (int b = 0; b < stu_total % 3; b++) {
					list_delay("Student name: ", stu[3 * a + b].name);
				}
				cout << endl;
				for (int b = 0; b < stu_total % 3; b++) {
					list_delay_int("Form: ", stu[3 * a + b].form);
				}
				cout << endl;
				for (int b = 0; b < 7; b++) {
					for (int c = 0; c < stu_total % 3; c++) {
						list_delay_int(subs_name_alt[b], stu[3 * a + c].sub[b]);
					}
					cout << endl;
				}
			}
			cout << "=======================================================================================================" << endl;
		}
		cout << "Please enter student information and marks." << endl;
		cout << "Student ID: ";

		do {
			val = false;
			index = 0;

			do {//check format student ID
				format = true;
				cin.getline(stu[stu_total].ID, 15);
				for (int a = 0; a < 2; a++) {
					if (!isdigit(stu[stu_total].ID[a])) {
						format = false;
					}
				}
				for (int a = 2; a < 5; a++) {
					if (!isalpha(stu[stu_total].ID[a]) || !isupper((stu[stu_total].ID[a]))) {
						format = false;
					}
				}
				for (int a = 5; a < 9; a++) {
					if (!isdigit(stu[stu_total].ID[a])) {
						format = false;
					}
				}
				if (format == false) {
					cout << "Please enter an ID with a correct format: ";
				}
			} while (format == false);

			if (stu_total != 0) {
				//student ID validation: check existed student ID
				while (index < stu_total) {

					if (strcmp(stu[stu_total].ID, stu[index].ID) == 0) {
						cout << "The student ID existed. Please enter again: ";
						break;
					}
					else {
						val = true;
						index++;
					}
				}
			}
			else {
				val = true;
			}
		} while (val == false || index < stu_total); // loop again if ID is not found within the student total

		cout << "Student Name: ";
		cin.getline(stu[stu_total].name, 50);

		cout << "Form: ";
		do {
			cin.getline(forms, 10);
			stu[stu_total].form = input_valid(forms);
			if (stu[stu_total].form < 1 || stu[stu_total].form > 3) {
				cout << "This program only records form 1 to form 3 students. Please enter again: ";
			}
		} while (stu[stu_total].form < 1 || stu[stu_total].form >3);

		//input marks for every subject
		for (int x = 0; x < 7; x++) {
			cout << subs_name[x] << ": ";
			do {
				cin.getline(marks, 10);
				stu[stu_total].sub[x] = input_valid(marks);
				if (stu[stu_total].sub[x] < 0 || stu[stu_total].sub[x] > 100) {
					cout << "Please enter marks between 0 to 100: ";
				}
			} while (stu[stu_total].sub[x] < 0 || stu[stu_total].sub[x] > 100);
		}

		stu_total++; //student number + 1 after inserting the details

		//sorting by student ID
		do {
			val2 = true;
			for (int a = 0; a < stu_total - 1; a++) {
				if (strcmp(stu[a].ID, stu[a + 1].ID) == 1) {// comparing two student ID
					strcpy(stu_sort[a].ID, stu[a + 1].ID);	//the student with smaller ID will go to the front
					strcpy(stu_sort[a + 1].ID, stu[a].ID);

					strcpy(stu_sort[a].name, stu[a + 1].name);
					strcpy(stu_sort[a + 1].name, stu[a].name);

					stu_sort[a].form = stu[a + 1].form;
					stu_sort[a + 1].form = stu[a].form;

					for (int b = 0; b < 7; b++) {
						stu_sort[a].sub[b] = stu[a + 1].sub[b];
						stu_sort[a + 1].sub[b] = stu[a].sub[b];
					}

					for (int b = a; b < a + 2; b++) {
						strcpy(stu[b].ID, stu_sort[b].ID);
						strcpy(stu[b].name, stu_sort[b].name);
						stu[b].form = stu_sort[b].form;
						for (int c = 0; c < 7; c++) {
							stu[b].sub[c] = stu_sort[b].sub[c];
						}
					}
					val2 = false;	//val2 is to determine whether the sorting is done or not
				}
			}						//val2 will remain true if all students are sorted
		} while (val2 == false);
		delay("========== Student information inserted ! ==========");
		cout << "Do you want to key in another record? (Press Y to proceed. Press any key to quit): ";
		cin >> choice;
		cin.ignore();
	} while (tolower(choice) == 'y');

	outputFile();
}

void Filter() {
	system("cls");
	int forms, sub_no = 0, count = 0, sub_count = 0, g;
	char form_og[10];
	bool val = false, val2;
	string no_subs[14], subjects;

	cout << "Please key in the information you wanted to filter: " << endl;
	cout << "Form: "; //input the student form to be filtered
	do {
		cin.getline(form_og, 10);
		forms = input_valid(form_og);
		cout << endl;
		if (forms < 1 || forms > 3) {
			cout << "This program only record form 1 to form 3 students. Please enter again: ";
		}
	} while (forms < 1 || forms > 3);

	cout << "Subjects that can be filtered: BM, BI, BC, Math, Sci, Sejarah, Geo." << endl;

	cout << "Subjects(s): ";
	getline(cin, subjects);
	cout << endl;

	sub_no = filter_subs(subjects);


	delay("Filtering . . . . . .");
	cout << endl;
	Sleep(1000);

	cout << "Filtered List: " << endl;

	// list and count number of student by form that we want to filter
	for (int a = 0; a < stu_total; a++) {
		if (forms == stu[a].form) {
			strcpy(stu_fil[count].ID, stu[a].ID);
			strcpy(stu_fil[count].name, stu[a].name);
			stu_fil[count].form = stu[a].form;

			for (int b = 0; b < 7; b++) {
				stu_fil[count].sub[b] = stu[a].sub[b];
			}
			count++;
			val = true;
		}
	}

	cout << endl;
	if (val == true) {
		//print out list of students info after filtering
		if (count % 3 == 0) { //count = no. of students after filtering
			g = count / 3;
		}
		else {
			g = count / 3 + 1;
		}
		for (int a = 0; a < g; a++) {
			if (a != count / 3) {
				for (int b = 0; b < 3; b++) {
					list_delay("Student ID: ", stu_fil[3 * a + b].ID);
				}
				cout << endl;
				for (int b = 0; b < 3; b++) {
					list_delay("Student name: ", stu_fil[3 * a + b].name);
				}
				cout << endl;
				for (int b = 0; b < 3; b++) {
					list_delay_int("Form: ", stu_fil[3 * a + b].form);
				}
				cout << endl;
				for (int b = 0; b < sub_no; b++) {//b = no. of subjects to be filtered
					val2 = false;
					for (int c = 0; c < 7; c++) {//loop through all subject names
						if (toLower(subs_filter[b]) == toLower(subs_name[c])) {//print out the marks if the names matched
							for (int d = 0; d < 3; d++) {
								list_delay_int(subs_name_alt[c], stu_fil[3 * a + d].sub[c]);
							}
							val2 = true;
							cout << endl;
						}
					}
					if (val2 == false && a < 1) { //only runs when there is a subject that does not exist and only when a = 0 (to ensure it only counts every subject once)
						no_subs[sub_count] = subs_filter[b];
						sub_count++;
					}
				}
			}
			else {
				for (int b = 0; b < count % 3; b++) {
					list_delay("Student ID: ", stu_fil[3 * a + b].ID);
				}
				cout << endl;
				for (int b = 0; b < count % 3; b++) {
					list_delay("Student name: ", stu_fil[3 * a + b].name);
				}
				cout << endl;
				for (int b = 0; b < count % 3; b++) {
					list_delay_int("Form: ", stu_fil[3 * a + b].form);
				}
				cout << endl;
				for (int b = 0; b < sub_no; b++) {
					val2 = false;
					for (int c = 0; c < 7; c++) {
						if (toLower(subs_filter[b]) == toLower(subs_name[c])) {
							for (int d = 0; d < count % 3; d++) {
								list_delay_int(subs_name_alt[c], stu_fil[3 * a + d].sub[c]);
							}
							val2 = true;
							cout << endl;
						}
					}
					if (val2 == false && a < 1) {
						no_subs[sub_count] = subs_filter[b];
						sub_count++;
					}
				}
			}
			cout << "=======================================================================================================" << endl;
		}
		for (int a = 0; a < sub_count; a++) {// print out the subject names that do not exist
			cout << "No subject named " << no_subs[a] << "." << endl;
		}
	}
	else {
		cout << "No Form " << forms << " students." << endl; //print if no students in that form
	}
}

void Search() {
	system("cls");
	char name[50];
	bool val, val2 = false;
	int g, count = 0;
	//check student name
	cout << "Please type the name of student to search: ";
	cin.getline(name, 50);

	for (int a = 0; a < stu_total; a++) {//a = student index
		val = true;
		for (int b = 0; b < strlen(name); b++) {//b = student's name character index
			if (name[b] != stu[a].name[b]) {	//works by checking every single character of the name 
				val = false;					//so that even if only the front part of the name is typed, it'll match the actual whole name
			}
		}
		//copy every name that contains the part user searched into an array and add number of student searched
		if (val == true) {
			strcpy(stu_sea[count].ID, stu[a].ID);
			strcpy(stu_sea[count].name, stu[a].name);
			stu_sea[count].form = stu[a].form;

			for (int b = 0; b < 7; b++) {
				stu_sea[count].sub[b] = stu[a].sub[b];
			}
			val2 = true;
			count++;
		}

	}

	cout << endl;
	delay("Searching . . . . . .");
	cout << endl;
	Sleep(1000);

	//show search results of students info if student name matched
	if (count % 3 == 0) {
		g = count / 3;
	}
	else {
		g = count / 3 + 1;
	}

	cout << "Serach Result: " << endl;
	if (val2 == false) {
		cout << "No student named " << name << endl;
	}
	for (int a = 0; a < g; a++) {
		if (a != count / 3) {
			for (int b = 0; b < 3; b++) {
				list_delay("Student ID: ", stu_sea[3 * a + b].ID);
			}
			cout << endl;
			for (int b = 0; b < 3; b++) {
				list_delay("Student name: ", stu_sea[3 * a + b].name);
			}
			cout << endl;
			for (int b = 0; b < 3; b++) {
				list_delay_int("Form: ", stu_sea[3 * a + b].form);
			}
			cout << endl;
			for (int b = 0; b < 7; b++) {
				for (int c = 0; c < 3; c++) {
					list_delay_int(subs_name_alt[b], stu_sea[3 * a + c].sub[b]);
				}
				cout << endl;
			}
		}
		else {
			for (int b = 0; b < count % 3; b++) {
				list_delay("Student ID: ", stu_sea[3 * a + b].ID);
			}
			cout << endl;
			for (int b = 0; b < count % 3; b++) {
				list_delay("Student name: ", stu_sea[3 * a + b].name);
			}
			cout << endl;
			for (int b = 0; b < count % 3; b++) {
				list_delay_int("Form: ", stu_sea[3 * a + b].form);
			}
			cout << endl;
			for (int b = 0; b < 7; b++) {
				for (int c = 0; c < count % 3; c++) {
					list_delay_int(subs_name_alt[b], stu_sea[3 * a + c].sub[b]);
				}
				cout << endl;
			}
		}
		cout << "=======================================================================================================" << endl;
	}
}

void Edit() {
	char id[15], choose[10], editstudent = 'i', editother;
	int index, m2, g;

	do {
		system("cls");
		bool val = false;

		//print out current list for edit module
		if (stu_total % 3 == 0) {
			g = stu_total / 3;
		}
		else {
			g = stu_total / 3 + 1;
		}
		cout << "Current list: " << endl << endl;
		for (int a = 0; a < g; a++) {
			if (a != stu_total / 3) {
				for (int b = 0; b < 3; b++) {
					list_delay("Student ID: ", stu[3 * a + b].ID);
				}
				cout << endl;
				for (int b = 0; b < 3; b++) {
					list_delay("Student name: ", stu[3 * a + b].name);
				}
				cout << endl;
				for (int b = 0; b < 3; b++) {
					list_delay_int("Form: ", stu[3 * a + b].form);
				}
				cout << endl;
				for (int b = 0; b < 7; b++) {
					for (int c = 0; c < 3; c++) {
						list_delay_int(subs_name_alt[b], stu[3 * a + c].sub[b]);
					}
					cout << endl;
				}
			}
			else {
				for (int b = 0; b < stu_total % 3; b++) {
					list_delay("Student ID: ", stu[3 * a + b].ID);
				}
				cout << endl;
				for (int b = 0; b < stu_total % 3; b++) {
					list_delay("Student name: ", stu[3 * a + b].name);
				}
				cout << endl;
				for (int b = 0; b < stu_total % 3; b++) {
					list_delay_int("Form: ", stu[3 * a + b].form);
				}
				cout << endl;
				for (int b = 0; b < 7; b++) {
					for (int c = 0; c < stu_total % 3; c++) {
						list_delay_int(subs_name_alt[b], stu[3 * a + c].sub[b]);
					}
					cout << endl;
				}
			}
			cout << "=======================================================================================================" << endl;
		}
		cout << endl;
		cout << "Please key in the student ID that you want to edit: ";

		while (val == false) {
			index = 0;
			val = false;
			cin.getline(id, 10);

			//student ID validation
			while (val == false && index < stu_total) {
				if (strcmp(id, stu[index].ID) == 0) {
					val = true;
				}
				index++;
			}
			if (val == false) {
				cout << "Please enter correct student ID: ";
			}
		}
		if (val == true) {
			index--; //student index correction because index will add extra 1 when student validation was done

			do {
				if (tolower(editstudent) == 'y') { // only shows the student info to be edited when editing for the second time
					//print out the student info to be edited
					cout << endl;
					delay("The student information: ");
					cout << endl;
					fasterdelay("-----------------------------------");
					list_delay("Student ID: ", stu[index].ID);
					cout << endl;
					list_delay("Student name: ", stu[index].name);
					cout << endl;
					list_delay_int("Form: ", stu[index].form);
					cout << endl;

					for (int x = 0; x < 7; x++) {
						list_delay_int(subs_name_alt[x], stu[index].sub[x]);
						cout << endl;
					}
					fasterdelay("-----------------------------------");
					cout << endl;
				}
				cout << "Please select the attribute that you want to edit: " << endl;
				cout << "1. Name" << endl;
				cout << "2. Form" << endl;
				cout << "3. Marks" << endl;
				cout << "Choice: ";
				do {
					//choose attribute to edit
					cin.getline(choose, 10);
					m2 = input_valid(choose);

					if (m2 == 1) {
						editname(index);
					}
					else if (m2 == 2) {
						editform(index);
					}
					else if (m2 == 3) {
						editsubject(index);
					}
					else {
						cout << "The valid value choice are 1,2,3. Please enter again: ";
					}

				} while (m2 < 1 || m2 > 3);

				cout << "Do you still have anything to edit for this student? (Press Y to proceed. Press any key to quit.): ";
				cin >> editstudent;
				cin.ignore();
			} while (tolower(editstudent) == 'y');
		}
		cout << "Do you want to edit record for other student? (Press Y to proceed. Press any key to quit.): ";
		cin >> editother;
		cin.ignore();
	} while (tolower(editother) == 'y');
	outputFile();
	cout << endl;
	delay("========== Successfully updated! ==========");
}

void editname(int index) {
	char newname[50];

	cout << "Please update the name: ";
	cin.getline(newname, 50);
	cout << endl;

	strcpy(stu[index].name, newname);
	delay("========== Student's name updated successfully! ==========");
	cout << endl;
}


void editform(int index) {
	int newform;
	char form[10];
	cout << "Please update the form: ";
	do {
		cin.getline(form, 10);
		newform = input_valid(form);
		if (newform < 1 || newform > 3) {
			cout << "This program only record form 1 to form 3 students. Please enter again: ";
		}
	} while (newform < 1 || newform>3);

	cout << endl;
	stu[index].form = newform;
	delay("========== Student's form updated successfully! ========= ");
	cout << endl;
}

void editsubject(int index) {
	int sub_index, newmark;
	char marks[10];
	string edit_subject;
	bool cont = false;

	cout << "Please enter the subject that you want to change the mark (BM/BI/BC/Math/Sci/Sejarah/Geo): ";
	do {
		sub_index = 0;
		cin >> edit_subject;
		//subject name validation
		while (cont == false && sub_index < 7) {
			if (toLower(edit_subject) == toLower(subs_name[sub_index])) {
				cont = true;
			}
			sub_index++;
		}
		if (cont == false) {
			cout << "Please enter subject correctly: ";
		}
	} while (cont == false);
	sub_index--;//subject index correction because index will add extra 1 after subject name validation was done

	if (cont == true) {
		cout << "Please update the mark for " << subs_name[sub_index] << ": ";
		cin.ignore(256, '\n');
		do {
			cin.getline(marks, 10);
			newmark = input_valid(marks);
			if (newmark < 0 || newmark > 100) {
				cout << "Please enter marks between 0 to 100: ";
			}
		} while (newmark < 0 || newmark > 100);

		stu[index].sub[sub_index] = newmark;
		cout << endl;
		delay_no_enter("========== ");
		delay_no_enter(subs_name[sub_index]);
		delay_no_enter("'s mark updated successfully! ==========");
		cout << endl << endl;
	}
}

void Delete() {
	char id[10];
	bool val = false;
	int index, g;

	//print out current list for delete module
	if (stu_total % 3 == 0) {
		g = stu_total / 3;
	}
	else {
		g = stu_total / 3 + 1;
	}
	cout << "Current List: " << endl << endl;
	for (int a = 0; a < g; a++) {
		if (a != stu_total / 3) {
			for (int b = 0; b < 3; b++) {
				list_delay("Student ID: ", stu[3 * a + b].ID);
			}
			cout << endl;
			for (int b = 0; b < 3; b++) {
				list_delay("Student name: ", stu[3 * a + b].name);
			}
			cout << endl;
			for (int b = 0; b < 3; b++) {
				list_delay_int("Form: ", stu[3 * a + b].form);
			}
			cout << endl;
			for (int b = 0; b < 7; b++) {
				for (int c = 0; c < 3; c++) {
					list_delay_int(subs_name_alt[b], stu[3 * a + c].sub[b]);
				}
				cout << endl;
			}
		}
		else {
			for (int b = 0; b < stu_total % 3; b++) {
				list_delay("Student ID: ", stu[3 * a + b].ID);
			}
			cout << endl;
			for (int b = 0; b < stu_total % 3; b++) {
				list_delay("Student name: ", stu[3 * a + b].name);
			}
			cout << endl;
			for (int b = 0; b < stu_total % 3; b++) {
				list_delay_int("Form: ", stu[3 * a + b].form);
			}
			cout << endl;
			for (int b = 0; b < 7; b++) {
				for (int c = 0; c < stu_total % 3; c++) {
					list_delay_int(subs_name_alt[b], stu[3 * a + c].sub[b]);
				}
				cout << endl;
			}
		}
		cout << "=======================================================================================================" << endl;
	}

	cout << "Please key in the student ID that you want to delete the entire record: " << endl;
	while (val == false) {
		index = 0;
		val = false;
		cin.getline(id, 10);

		//student ID validation
		while (val == false && index < stu_total) {
			if (strcmp(id, stu[index].ID) == 0) {
				val = true;
			}
			index++;
		}
		if (val == false) {
			cout << "Please enter correct student ID: ";
		}
	}

	if (val == true) {
		index--; //student index correction because index will add extra 1 after student validation was done

		//reduce 1 index number of every student after the index of deleted student to fill in the empty space of the array
		for (index; index < stu_total; index++) {
			strcpy(stu[index].ID, stu[index + 1].ID);
			strcpy(stu[index].name, stu[index + 1].name);
			stu[index].form = stu[index + 1].form;
			for (int x = 0; x < 7; x++) {
				stu[index].sub[x] = stu[index + 1].sub[x];

			}
		}
		stu_total--;
		cout << endl;
		delay("========== Successfully Deleted! ==========");
		system("cls");
	}
}

void View() {
	string choice;
	int chosen_form;
	bool val = false;
	cout << "Please choose the form that you wish to view [ALL/1/2/3]: ";
	//choice checking and validation
	while (val == false) {
		cin >> choice;
		if (toLower(choice) == "all") {
			chosen_form = -1;
			val = true;
		}
		else if (choice == "1") {
			chosen_form = 1;
			val = true;
		}
		else if (choice == "2") {
			chosen_form = 2;
			val = true;
		}
		else if (choice == "3") {
			chosen_form = 3;
			val = true;
		}
		else {
			cout << "Please choose only ALL/1/2/3: ";
			val = false;
		}
	}

	for (int a = 0; a < 7; a++) {
		double sum = 0, sum_squared = 0;
		int highest_score = -1, count = 0, scorer = 0;
		string highest_scorer;

		for (int b = 0; b < stu_total; b++) {
			//filter and collect the marks of students if the chosen form matched the form of the student then make calculation
			if (chosen_form == -1 || stu[b].form == chosen_form) {
				int mark = stu[b].sub[a];
				sum += mark;
				sum_squared += mark * mark;
				if (mark > highest_score) {
					highest_score = mark;
				}
				count++; //increase student number 
			}
		}

		if (count > 0) {
			double average = sum / count;
			double variance = (sum_squared / count) - (average * average);
			double standard_deviation = sqrt(variance);

			delay(subs_name_alt[a]);
			cout << fixed << showpoint << setprecision(2) << "Average: " << average << endl;
			cout << "Standard Deviation: " << standard_deviation << endl;
			cout << "Highest Score: " << highest_score << endl;
			cout << "Highest Scorer: ";
			if (chosen_form == -1) {
				for (int b = 0; b < stu_total; b++) {
					if (stu[b].sub[a] == highest_score) {
						scorer++;
						if (scorer > 1) {
							cout << " & " << stu[b].name;
						}
						else {
							cout << stu[b].name;
						}
					}

				}
			}
			else {
				for (int b = 0; b < stu_total; b++) {
					if (stu[b].form == chosen_form && stu[b].sub[a] == highest_score) {
						scorer++;
						if (scorer > 1) {
							cout << " & " << stu[b].name;
						}
						else {
							cout << stu[b].name;
						}
					}
				}
			}
			cout << endl;
			fasterdelay("-----------------------------------------");
		}
		else {
			cout << "No data available for subject " << subs_name[a] << " in the chosen form.\n";
			fasterdelay("-----------------------------------------");
		}
	}
}

string toLower(string input) {// change all string to small letters
	for (int x = 0; x < input.length(); x++) {
		input[x] = tolower(input[x]);
	}
	return input;
}

int filter_subs(string input) {
	int start = 0, length = 0, sub_no = 0;
	string substring;
	for (int a = 0; a < input.length(); a++) {
		if (!isspace(input[a])) {
			length++;
		}
		else {
			substring = input.substr(start, length);
			length = 0;
			subs_filter[sub_no] = substring;
			sub_no++;
			start = a + 1;
		}
	}
	if (length > 0) {
		substring = input.substr(start, length);
		subs_filter[sub_no] = substring;
		sub_no++;
	}
	return sub_no;
}

void outputFile() { //ofstream function
	ofstream outFile("student.txt");
	for (int a = 0; a < stu_total; a++) {
		outFile << stu[a].ID << endl;
		outFile << stu[a].name << endl;
		outFile << stu[a].form << endl;
		for (int b = 0; b < 7; b++) {
			outFile << stu[a].sub[b] << " ";
		}
		outFile << endl;
	}
	outFile.close();
}

int student_num() {//ifstream function and count student_total
	int a = 0;
	ifstream inFile("student.txt");
	if (!inFile.fail()) {
		while (!inFile.eof()) {
			inFile.getline(stu[a].ID, 15);
			inFile.getline(stu[a].name, 50);
			inFile >> stu[a].form;
			for (int b = 0; b < 7; b++) {
				inFile >> stu[a].sub[b];
			}
			inFile.ignore(256, '\n');
			a++;
		}
	}
	if (a != 0) {	//only executes if student data already exists in the text file
		a--;		//an empty row exists at the end of the text file after ofstream
	}				//student number need to - 1 to prevent an extra empty array
	inFile.close();
	return a;
}

int input_valid(char input[]) {//input check: Make sure the input is not alphabet or symbol
	bool val;
	int value;
	do {
		val = true;
		for (int a = 0; a < strlen(input); a++) {
			if (!isdigit(input[a])) {
				val = false;
			}
		}
		if (val == true) {
			value = stoi(input);
		}
		else {
			cout << "Please enter a correct value: ";
			cin.getline(input, 10);
		}
	} while (val == false);

	return value;
}

//decoration (delay text speed)
void delay(string word) {

	for (int i = 0; i < word.length(); i++) {
		cout << word[i];
		Sleep(30);
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