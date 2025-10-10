#include	<iostream>
#include	<iomanip>
#include 	<fstream>
#include	<string>
#include	<cstdlib>
#include	"List.h"
#include	"Student.h"

using namespace std;


bool CreateStuList(const char*, List*);
bool DeleteStudent(List*, char*);
bool PrintList(List, int);
bool InsertExamResult(const char*, List*);
bool PrintStatistic(List);
bool FilterStudent(List, List*, char*, int, int);
bool UpdateIDandPhone(List*);
bool FindPotentialFirstClass(List, List*, char*);
int menu();
int input_valid(char[]);

using namespace std;


int main() {

	//Create student list & insert exam
	List studentList;
	char f_name1[] = "student.txt";
	char f_name2[] = "exam.txt";
	bool checkCreate = false;
	bool checkInsert = false;

	//Delete student record
	char del_id[8] = "";

	//Print results
	int choice2 = 0;

	//Filter
	List filt_stu;
	char filt_crs[12] = "";
	int filt_yr = 0, filt_cred = 0;

	//Update id and phone
	bool checkUpdate = false;

	//Find potential first class
	List fc_stu;
	char fc_crs[12] = "";

	//menu
	int choice = 0;
	char dumChoice[10]; //dummy choice for validation (stoi)
	char printChoice = ' ';
	bool nFirst_in;

	do {
		system("cls");
		choice = menu();
		cout << "\n";
		nFirst_in = false;
		do {
			if (nFirst_in) { //will run only if the first time input is incorrect
				cout << "Please enter the number of the tasks given (1-9): ";
				cin.getline(dumChoice, 10);
				choice = input_valid(dumChoice);
			}

			switch (choice) {
			case 1:
				if (checkCreate) { //restrict this option to be used once 
					cout << "This function is used already, please exit the system before using it again.\n";
				}
				else {
					//create student list
					if (CreateStuList(f_name1, &studentList)) {
						cout << "\n\nStudent List created successfully.\n";
					}
					else {
						cout << "\nFailed to create Student List. Please ensure the text file is filled with record.\n";
					}
					checkCreate = true;

				}
				break;
			case 2:
				//delete student record
				cout << "type student id to delete: ";
				cin >> del_id;
				cin.ignore();
				if (DeleteStudent(&studentList, del_id)) {

					cout << "Do you want to display results? (Y/N): ";
					do {
						cin >> printChoice;
						cin.ignore();
						if (tolower(printChoice) != 'y' && tolower(printChoice) != 'n') {
							cout << "\nPlease input only Y or N: ";
						}
					} while (tolower(printChoice) != 'y' && tolower(printChoice) != 'n');
					if (tolower(printChoice) == 'y') {
						cout << "Current Student list:\n";
						PrintList(studentList, 1);
						cout << "**Please remember to copy data to a safe place to prevent loss of data.\n";
					}
				}
				else {
					cout << "Cannot find student with id " << del_id << "\n\n";
				}
				break;
			case 3:
				//print student record

				cout << "Please select how do you want to display the results: On Screen (1) / In Text File (2): ";
				do {//input validation
					cin.getline(dumChoice, 10);
					choice2 = input_valid(dumChoice);
					if (choice2 != 1 && choice2 != 2) {
						cout << "\nPlease input only 1 or 2.:";
					}
				} while (choice2 != 1 && choice2 != 2);
				PrintList(studentList, choice2);
				cout << "**Please remember to copy data to a safe place to prevent loss of data.\n";
				break;
			case 4:
				if (!checkCreate) {//ensure student list is created before using this function
					cout << "\nIt is recommended that the student list has to be created first before using this function.\n\n";
				}
				else {
					if (checkInsert) {//restrict this option to be used once 
						cout << "This function is used already, please exit the system before using it again.\n";
					}
					else {
						if (InsertExamResult(f_name2, &studentList)) {
							cout << "\nExam results inserted successfully.\n\n\n";
						}
						else {
							cout << "Failed to insert exam record\n";
						}
						checkInsert = true;
					}
				}
				break;
			case 5:
				//print student statistics
				PrintStatistic(studentList);
				break;
			case 6:
				//filter student record
				cout << "Please input '-1' if you do not want to filter that particular criteria.\n\n";
				cout << "Insert course to filter: ";
				cin >> filt_crs;
				cin.ignore();
				cout << "\nInsert year to filter: ";
				cin >> filt_yr;
				cin.ignore();
				cout << "\nInsert credit hours to filter: ";
				cin >> filt_cred;
				cin.ignore();

				if (FilterStudent(studentList, &filt_stu, filt_crs, filt_yr, filt_cred)) {
					cout << "Do you want to display results? (Y/N): "; //prompt user to output

					do {//Input validation
						cin >> printChoice;
						cin.ignore();
						if (tolower(printChoice) != 'y' && tolower(printChoice) != 'n') {
							cout << "\nPlease input only Y or N: ";
						}
					} while (tolower(printChoice) != 'y' && tolower(printChoice) != 'n');

					if (tolower(printChoice) == 'y') {
						cout << "Current Student list:\n";
						PrintList(filt_stu, 1);
						cout << "**Please remember to copy data to a safe place to prevent loss of data.\n";
					}
				}

				for (int i = filt_stu.count; i > 0; i--) { //clear list before using the next time to prevent data clashing
					filt_stu.remove(i);
				}
				break;
			case 7:
				//update id and phone format of student record
				if (checkUpdate) { //restrict this option to be used once 
					cout << "This function is used already, please exit the system before using it again.\n";
				}
				else {
					if (UpdateIDandPhone(&studentList)) {
						cout << "Successfully updated ID and Phone of students.\n\n";
						cout << "Do you want to display results? (Y/N): ";

						do {//input validation
							cin >> printChoice;
							cin.ignore();
							if (tolower(printChoice) != 'y' && tolower(printChoice) != 'n') {
								cout << "\nPlease input only Y or N: ";
							}
						} while (tolower(printChoice) != 'y' && tolower(printChoice) != 'n');
						if (tolower(printChoice) == 'y') {
							cout << "Current Student list:\n";
							PrintList(studentList, 1);
							cout << "**Please remember to copy data to a safe place to prevent loss of data.\n";
						}
					}
					checkUpdate = true;
				}
				break;
			case 8:
				//find potential first class in student record
				cout << "Insert course: ";
				cin >> fc_crs;
				cin.ignore();

				if (FindPotentialFirstClass(studentList, &fc_stu, fc_crs)) {
					cout << "Do you want to display results? (Y/N): ";

					do {//input validation
						cin >> printChoice;
						cin.ignore();
						if (tolower(printChoice) != 'y' && tolower(printChoice) != 'n') {
							cout << "\nPlease input only Y or N: ";
						}
					} while (tolower(printChoice) != 'y' && tolower(printChoice) != 'n');

					if (tolower(printChoice) == 'y') {
						cout << "Current Student list:\n";
						PrintList(fc_stu, 1);
						cout << "**Please remember to copy data to a safe place to prevent loss of data.\n";
					}
				}
				for (int i = fc_stu.count; i > 0; i--) { //clear list before using the next time to prevent data clashing
					fc_stu.remove(i);
				}

				break;
			case 9:
				cout << "Thank you for using this service.\n\n";
				break;
			default:
				nFirst_in = true;
			}
		} while (choice < 1 || choice>9);

		cout << "\n";
		system("Pause");
	} while (choice != 9);

	return 0;
}

int menu() {
	int choice = 0;
	char dumChoice[10]; //dummy choice for validation (stoi)
	for (int i = 0; i < 71; i++) {
		cout << "=";
	}
	cout << "\n||" << right << setw(48) << "UNIVERSITI TUNKU ABDUL RAHMAN" << setw(22) << "||\n";
	cout << "||" << setw(59) << "FACULTY OF INFORMATION AND COMMUNICATION TECHONOLGY" << setw(11) << "||\n";
	cout << "||" << setw(48) << "Student Administration System" << setw(22) << "||\n";
	for (int i = 0; i < 71; i++) {
		cout << "=";
	}
	cout << "\n";
	for (int i = 0; i < 71; i++) {
		cout << "_";
	}
	cout << "\n1. Create Student List\n2. Delete Student\n3. Print Student List\n";
	cout << "4. Insert Exam Result\n5. Print Exam Statistics\n6. Filter Student\n";
	cout << "7. Update Student's ID and Phone\n8. Find Potential First Class Student\n9. Exit\n";
	for (int i = 0; i < 71; i++) {
		cout << "_";
	}
	cout << "\nPlease choose a task to be done (1-9)\n";
	cout << "*ps: It is recommended to Create Student List (1) first and Insert Exam Results (4) before conducting any other functions.\n\n";
	cout << "Choice: ";
	cin.getline(dumChoice, 10);
	choice = input_valid(dumChoice);
	return choice;
}

bool CreateStuList(const char* input, List* list) {
	ifstream inFile(input);
	char s[30];
	bool checkDuplicate;

	if (!inFile.fail()) {

		while (!inFile.eof()) { //continue read
			Student newStudent;

			for (int i = 0; i < 3; i++) { //get id
				inFile >> s;
			}
			inFile >> newStudent.id;

			for (int i = 0; i < 2; i++) { //get name
				inFile >> s;
			}
			inFile.ignore();
			inFile.getline(newStudent.name, 30);

			for (int i = 0; i < 2; i++) { //get course
				inFile >> s;
			}

			inFile >> newStudent.course;

			for (int i = 0; i < 3; i++) { //get phone no
				inFile >> s;
			}

			inFile >> newStudent.phone_no;

			checkDuplicate = false;//reset if previous record is duplicated

			//check duplicated student id
			Node* cur = list->head;
			while (cur != NULL) {
				if (strcmp(cur->item.id, newStudent.id) == 0) {
					checkDuplicate = true;
					cout << "Error to create " << newStudent.id << " (" << newStudent.name << ") " << "student info due to duplicate Student ID." << endl;
				}
				cur = cur->next;
			}
			if (cur == NULL && checkDuplicate == false) {
				list->insert(newStudent); //insert info to a node of the list
			}

		}

		if (strcmp(list->head->item.name, "1") < 0) { //remove 1st node after sorting as error of file reading, read the last empty line into list, and will be sorted to the 1st node
			list->remove(1);
		}

		inFile.close();
		return true;
	}
	else {
		cout << "Cannot Open the file" << endl;
		return false;
	}

};

bool DeleteStudent(List* list, char* id) {
	Student stu;
	if (list->empty()) { //check if list is empty
		cout << "List is empty. Please try inserting some info first.\n\n";
		return false;
	}
	else {
		for (int i = 1; i <= list->size(); i++) {
			list->get(i, stu);

			if (strcmp(stu.id, id) == 0) {
				list->remove(i);
				cout << "Student record " << stu.id << " " << "( " << stu.name << " ) removed successfully.\n\n";
				return true;
			}
		}
	}
	return false;
}

bool PrintList(List list, int source) {
	Student student;
	int studentCount = list.size();

	if (!list.empty()) {
		if (source == 1) {//output to screen

			for (int i = 1; i < studentCount + 1; i++) {
				cout << "\n*******************************************STUDENT " << i << "****************************************************";
				list.get(i, student);
				student.print(cout);

				if (student.exam_cnt != 0) {


					cout << "\n\n--------------------------------------------------PAST EXAM RESULT--------------------------------------------------------" << endl;
					for (int i = 0; i < student.exam_cnt; i++) {
						student.exam[i].print(cout);
					}

				}
				else {
					cout << "THIS STUDENT HAVENT'T TAKEN ANY EXAM YET. " << endl;
				}
				cout << "*******************************************STUDENT " << i << "****************************************************\n\n\n";
			}

		}
		else {//output to text file
			char f_name3[] = "student_result.txt";
			ofstream outFile(f_name3);

			for (int i = 1; i < studentCount + 1; i++) {
				outFile << "*******************************************STUDENT " << i << "****************************************************";
				list.get(i, student);

				if (student.exam_cnt != 0) {
					student.print(outFile);
					outFile << "\n\n--------------------------------------------------PAST EXAM RESULT--------------------------------------------------" << endl;
					for (int i = 0; i < student.exam_cnt; i++) {
						student.exam[i].print(outFile);
					}
					outFile << "*******************************************STUDENT " << i << "****************************************************\n\n\n\n";
				}
				else {
					outFile << "THIS STUDENT HAVENT'T TAKEN ANY EXAM YET. " << endl;
				}
			}
			cout << "Results are exported successfully. Please check the text file (" << f_name3 << ") given.\n\n";
			outFile.close();
		}

		return true;
	}
	else {
		cout << "The list is empty" << endl;
		return false;
	}
}

bool InsertExamResult(const char* input, List* list) {

	List dum1, dum2, dum3; //dummy list for compiling output error student record
	Student Stu;
	int ex_cnt = 0;

	ifstream inFile(input);
	if (!inFile.fail()) {
		while (!inFile.eof()) {
			bool duplicateDum2 = false, duplicateDum3 = false;
			bool checkExistID = false, checkExceed = false, checkDuplicate = false;

			//read whole line into a reference variable
			Student Stu_ref;
			inFile >> Stu_ref.id;
			inFile >> Stu_ref.exam[0].trimester >> Stu_ref.exam[0].year >> Stu_ref.exam[0].numOfSubjects;
			for (int i = 0; i < Stu_ref.exam[0].numOfSubjects; i++) {
				inFile >> Stu_ref.exam[0].sub[i].subject_code >> Stu_ref.exam[0].sub[i].subject_name >> Stu_ref.exam[0].sub[i].credit_hours >> Stu_ref.exam[0].sub[i].marks;
			}


			for (int i = 1; i <= list->size(); i++) { //loop reference to match id
				list->get(i, Stu);

				if (Stu.compareID(Stu_ref)) {
					strcpy(Stu_ref.name, Stu.name);
					if (Stu.exam_cnt < 10) {//check exam count, if larger than 10, will not be inserted

						//check same exam trimester and year
						for (int j = 0; j < Stu.exam_cnt; j++) {
							if (Stu_ref.exam[0].trimester == Stu.exam[j].trimester && Stu_ref.exam[0].year == Stu.exam[j].year) {
								checkDuplicate = true;
								dum1.insert(Stu_ref);
							}
						}

						//copy data from reference variable
						if (!checkDuplicate) {
							ex_cnt = Stu.exam_cnt;
							Stu.exam[ex_cnt].trimester = Stu_ref.exam[0].trimester;
							Stu.exam[ex_cnt].year = Stu_ref.exam[0].year;
							Stu.exam[ex_cnt].numOfSubjects = Stu_ref.exam[0].numOfSubjects;
							for (int j = 0; j < Stu_ref.exam[0].numOfSubjects; j++) {
								strcpy(Stu.exam[ex_cnt].sub[j].subject_code, Stu_ref.exam[0].sub[j].subject_code);
								strcpy(Stu.exam[ex_cnt].sub[j].subject_name, Stu_ref.exam[0].sub[j].subject_name);

								Stu.exam[ex_cnt].sub[j].credit_hours = Stu_ref.exam[0].sub[j].credit_hours;
								Stu.exam[ex_cnt].sub[j].marks = Stu_ref.exam[0].sub[j].marks;
							}
							Stu.exam_cnt++;

							for (int j = 0; j < Stu.exam_cnt; j++) {
								Stu.exam[j].calculateGPA();
							}
							Stu.calculateCurrentCGPA();

							//sort past exam by year from a student
							bool checkSort;
							Exam sort_temp;
							do {
								checkSort = true;

								if (Stu.exam_cnt > 1) {

									for (int j = 0; j < Stu.exam_cnt - 1; j++) {
										if (Stu.exam[j].year > Stu.exam[j + 1].year ||
											(Stu.exam[j].year == Stu.exam[j + 1].year && Stu.exam[j].trimester > Stu.exam[j + 1].trimester)) { // (check year or ( check trisemester && in same year))
											sort_temp = Stu.exam[j];
											Stu.exam[j] = Stu.exam[j + 1];
											Stu.exam[j + 1] = sort_temp;
											checkSort = false;
										}
									}
								}

							} while (!checkSort);

							list->set(i, Stu);
						}
					}
					else {
						checkExceed = true;
					}
					checkExistID = true;
					break;
				}
				else {
					checkExistID || false;
				}
			}

			if (checkExceed) {
				if (strcmp(Stu_ref.id, "0") > 0) {// check if the reference id is empty
					if (dum2.size() > 0) {//check if dummy list is empty, if not then only check for duplication, else just proceed to insert id
						for (int i = 1; i <= dum2.size(); i++) {
							dum2.get(i, Stu);
							if (Stu.compareID(Stu_ref)) {
								duplicateDum2 = true;
							}
						}
					}
					if (!duplicateDum2) {
						dum2.insert(Stu_ref);
					}
				}
			}

			if (!checkExistID) {
				if (strcmp(Stu_ref.id, "0") > 0) {// check if the reference id is empty
					if (dum3.size() > 0) {//check if dummy list is empty, if not then only check for duplication, else just proceed to insert id
						for (int i = 1; i <= dum3.size(); i++) {
							dum3.get(i, Stu);
							if (Stu.compareID(Stu_ref)) {
								duplicateDum3 = true;
							}
						}
					}
					if (!duplicateDum3) {
						dum3.insert(Stu_ref);
					}
				}
			}
		}

		// output 3 type of error after read whole exam.txt
		if (dum1.size() > 0) {
			cout << "\nExam Duplication Error" << endl;
			cout << "-----------------------\n\n";
			Node* cur = dum1.head;
			while (cur != NULL) {

				cout << "Error to insert " << cur->item.id << " ( " << left << setw(20) << cur->item.name << ") " << cur->item.exam[0].printTrimester() << " " << cur->item.exam[0].year << " exam info due to duplication.\n\n";

				cur = cur->next;
			}

		}

		if (dum2.size() > 0) {
			cout << "\nExam Excced 10 Record" << endl;
			cout << "-----------------------\n\n";
			cout << "**Please be noted that any exam records after the 10th exam of that particular student or repetitive records will be ignored.\n\n";
			for (int i = 1; i <= dum2.size(); i++) {
				dum2.get(i, Stu);
				cout << "Error to insert " << Stu.id << " (" << left << setw(20) << Stu.name << ") " << Stu.exam[0].printTrimester() << " " << Stu.exam[0].year << " exam info due to exceed 10 exam records.\n\n";

			}
		}

		if (dum3.size() > 0) {
			cout << "\nStudent Not Found" << endl;
			cout << "-----------------\n\n";
			for (int i = 1; i <= dum3.size(); i++) {
				dum3.get(i, Stu);
				cout << "No student with ID " << Stu.id << ". Failed to insert exam infomation.\n\n";
			}
		}

		inFile.close();
		return true;
	}
	else {
		cout << "File cannot open. " << endl;
		return false;
	}
}



bool PrintStatistic(List list) {
	int totalStudent = 0, totalSemester = 0;
	double  totalSubject = 0, totalCredits = 0, totalCGPA = 0, AverageCGPA, AverageSubject, AverageCredit;
	Student student;
	const char* course[]{ "CS","IA","IB","CN","CT" };

	int courseCount[5]{};
	totalStudent = list.size();
	Node* cur = list.head;

	if (cur == NULL) {
		cout << "List is empty. Please try inserting some info first.\n\n";
		return false;
	}

	while (cur != NULL) {
		cur->item.course;
		for (int i = 0; i < 5; i++) {
			if (strcmp(cur->item.course, course[i]) == 0) { // compare course to make statistic
				courseCount[i]++;
				break;
			}
		}
		totalCGPA += cur->item.current_cgpa;

		totalSemester += cur->item.exam_cnt;
		totalCredits += cur->item.totalCreditsEarned;
		for (int j = 0; j < cur->item.exam_cnt; j++) {
			totalSubject += cur->item.exam[j].numOfSubjects;
		}
		cur = cur->next;
	}

	//calculations
	AverageCGPA = totalCGPA / totalStudent;
	AverageSubject = totalSubject / totalSemester;
	AverageCredit = totalCredits / totalSemester;

	cout << "Total Students: " << totalStudent << endl;
	for (int i = 0; i < 5; i++) {
		cout << course[i] << " Students - " << courseCount[i] << endl;
	}
	cout << "\n\nAverage CGPA: " << setprecision(5) << fixed << AverageCGPA << endl;
	cout << "Average Subjects Taken Per Semester: " << setprecision(2) << fixed << AverageSubject << endl;
	cout << "Average Credits Earned Per Semester: " << setprecision(2) << fixed << AverageCredit << endl;

	return true;
}


bool FilterStudent(List list1, List* list2, char* course, int year, int totalcredit) {
	Student stu;
	string yr;
	bool cases = true;

	if (list1.empty()) {
		cout << "\n\nList is empty. Please try inserting some info first.\n\n";
		return false;
	}
	else {

		for (int i = 1; i <= list1.size(); i++) {
			list1.get(i, stu);

			if (strcmp(course, "-1") != 0) {

				if (strcmp(stu.course, course) != 0) {
					cases = false;
				}

			}


			if (cases) {
				if (year != -1) {
					string id(stu.id); //change student id from char to string
					yr = to_string(year); //change year from int to string
					if (yr.substr(2, 2) != id.substr(0, 2)) { //compare last two char of yr to first two char of id
						cases = false;
					}

				}

			}

			if (cases) {
				if (totalcredit != -1) {
					int stu_totalcred = 0;
					for (int j = 0; j < stu.exam_cnt; j++) {
						for (int i = 0; i < stu.exam[j].numOfSubjects; i++) {
							stu_totalcred += stu.exam[j].sub[i].credit_hours;
						}
					}
					if (stu_totalcred < totalcredit) {
						cases = false;
					}

				}
			}

			if (cases) {
				list2->insert(stu);
			}
			cases = true;

		}
		if (list2->empty()) {
			cout << "No student with the given criteria is found.\n\n";
			return false;
		}
		else {
			cout << "Student filtered successfully.\n\n";
			return true;
		}
	}
}

bool UpdateIDandPhone(List* list) {
	Node* cur = list->head;
	if (cur == NULL) {
		cout << "There is no data in linked list" << endl;
		return false;
	}
	while (cur != NULL) {

		char updateID[11] = "B";
		strcat(updateID, cur->item.course); //combine B with course
		strcat(updateID, cur->item.id);//combine B + course +id
		strcpy(cur->item.id, updateID);//copy

		for (int i = 3; i < strlen(cur->item.phone_no); i++) { //remove -
			cur->item.phone_no[i] = cur->item.phone_no[i + 1];
		}

		if (cur->item.phone_no[0] % 2 == 0) {//modulus first num to do operation below
			char updatePhone[10] = "02";
			strcat(updatePhone, cur->item.phone_no); //combine 02 with number
			strcpy(cur->item.phone_no, updatePhone); //copy
		}
		else {
			char updatePhone[10] = "01";
			strcat(updatePhone, cur->item.phone_no); //combine 01 with number
			strcpy(cur->item.phone_no, updatePhone);//copy
		}

		cur = cur->next;
	}
	return true;
}

bool FindPotentialFirstClass(List list1, List* list2, char* course) {
	Student stu;
	bool check = false;
	if (list1.empty() || !list2->empty()) {
		cout << "Please check if the first list is empty or second list is not empty.\n\n";
		return false;
	}
	else {
		for (int i = 1; i <= list1.count; i++) { //traverse list1
			int high_gpa_cnt = 0;
			bool minGPA = true;
			list1.get(i, stu);
			if (strcmp(stu.course, course) == 0) {//compare course name
				if (stu.exam_cnt > 2) { //Check if student has more than 2 exams

					for (int i = 0; i < stu.exam_cnt; i++) {
						if (stu.exam[i].calculateGPA()) {
							if (stu.exam[i].gpa < 3.5) { //check if student has one GPA less than minimum
								minGPA = false;

							}
						}
					}
					if (minGPA) {
						for (int j = 0; j < stu.exam_cnt; j++) {
							int total_cred = 0;
							for (int k = 0; k < stu.exam[j].numOfSubjects; k++) { //Get total credit hours for that exam
								total_cred += stu.exam[j].sub[k].credit_hours;
							}
							if (stu.exam[j].gpa >= 3.75 && total_cred >= 12) { //record frequency of getting high GPA
								high_gpa_cnt++;
							}
						}
					}
					if (high_gpa_cnt >= 3) {
						list2->insert(stu);
						check = true;
					}
				}
			}
		}
	}
	if (!check) {
		cout << "There is no student in " << course << " that has potential to get first class.\n\n";
		return false;
	}
	else {
		cout << "Successfully get student of potential first class.\n\n";
		return true;
	}
}

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
			cout << "Please enter a correct value: ";
			cin.getline(input, 10);
		}
	} while (val == false);

	return value;
}