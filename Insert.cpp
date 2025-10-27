#include	"Insert.h"
#include	"Display.h"
#include	<fstream>
#include	<vector>
#include	<algorithm>

bool checkStudent = false;
bool Insert() {
	system("cls");
	cout << "Insert Students data \n";
	cout << "=======================\n";
	cout << "1. Read student record from txt file\n2. Read exam record from txt file\n3. Insert new student profile\n4. Insert exam profile\n5. Return\n\nChoice: ";
	int choice = 0;
	char dumChoice[10];
	bool checkRedirect = true;
	do {
		cin.getline(dumChoice, 10);
		choice = input_valid(dumChoice);
		switch (choice) {
		case 1:
			if (readStuRecord()) {
				checkStudent = true;
				cout << "Stuents created successfully\n\nDo you want to continue insert?(y/n)";
				if (yesNo()) {
					Insert();
				}
			}
			else {
				cout << "The file doesn't exist.\n";
			}
			break;
		case 2:
			if (!checkStudent) {
				cout<<"Please insert student record first\n";
				break;
			}
			if (readStuExam()) {
				cout << "Exam information created successfully\n\nDo you want to continue insert?(y/n)";
				if (yesNo()) {
					Insert();
				}
			}
			else {
				cout << "The file doesn't exist.\n";
			}
			break;
		case 3:
			system("cls");
			insertNewStudent();
			break;
		case 4:
			system("cls");
			insertNewExam();
			break;
		case 5:
			return true;
		default:
			cout << "Please enter valid number \n";
			checkRedirect = false;
		}
	} while (!checkRedirect);

	return false;
}


bool readStuRecord() { //1. Read student record from txt file
	string f_name;
	cout << "Enter file name: ";
	getline(cin, f_name);
	ifstream inFile(f_name);
	char s[30];
	bool checkDuplicate;
	if (!inFile.fail()) {
		while (!inFile.eof()) {
			Student newStu;
			for (int i = 0; i < 3; i++) { //get id
				inFile >> s;
			}
			inFile >> newStu.id;

			for (int i = 0; i < 2; i++) { //get name
				inFile >> s;
			}
			inFile.ignore();
			getline(inFile, newStu.name);

			for (int i = 0; i < 2; i++) { //get course
				inFile >> s;
			}

			inFile >> newStu.course;

			for (int i = 0; i < 3; i++) { //get phone no
				inFile >> s;
			}

			inFile >> newStu.phone;

			checkDuplicate = false;//reset if previous record is duplicated

			//check duplicated student id
			for (int i = 0; i < StuList.size(); i++) {
				if (newStu.id.compare(StuList[i].id) == 0) {
					checkDuplicate = true;
					cout << "Error to create " << newStu.id << " (" << newStu.name << ") " << "student info due to duplicate Student ID.\n";
				}
			}
			if (!checkDuplicate) {
				StuList.push_back(newStu);
			}
		}
		StuList.pop_back();
		inFile.close();
		sort(StuList.begin(), StuList.end(), [](const Student& a, const Student& b) {
			return a.id < b.id;  // ascending order
			});

		return true;
	}
	else {
		return false;
	}
}

bool readStuExam() {  //2.Read exam record from txt file
	vector<Student>dum1, dum2, dum3;
	int examCount = 0;
	string f_name;
	cout << "Make sure student inserted before add exam infrormation\n";
	cout << "Enter file name: ";
	getline(cin, f_name);
	ifstream inFile(f_name);
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


			for (int i = 0; i < StuList.size(); i++) { //loop reference to match id

				if (StuList[i].compareID(Stu_ref)) {
					Stu_ref.name = StuList[i].name;
					if (StuList[i].exam_cnt >= 10) {//check exam count, if larger than 10, will not be inserted
						checkExceed = true;
					}
					else {
						//dum1: check same exam trimester and year
						for (int j = 0; j < StuList[i].exam_cnt; j++) {
							if (Stu_ref.exam[0].trimester == StuList[i].exam[j].trimester && Stu_ref.exam[0].year == StuList[i].exam[j].year) {
								checkDuplicate = true;
								dum1.push_back(Stu_ref);
							}
						}

						//copy data from reference variable
						if (!checkDuplicate) {
							examCount = StuList[i].exam_cnt;
							StuList[i].exam[examCount].trimester = Stu_ref.exam[0].trimester;
							StuList[i].exam[examCount].year = Stu_ref.exam[0].year;
							StuList[i].exam[examCount].numOfSubjects = Stu_ref.exam[0].numOfSubjects;
							for (int j = 0; j < Stu_ref.exam[0].numOfSubjects; j++) {
								strcpy(StuList[i].exam[examCount].sub[j].subject_code, Stu_ref.exam[0].sub[j].subject_code);
								strcpy(StuList[i].exam[examCount].sub[j].subject_name, Stu_ref.exam[0].sub[j].subject_name);

								StuList[i].exam[examCount].sub[j].credit_hours = Stu_ref.exam[0].sub[j].credit_hours;
								StuList[i].exam[examCount].sub[j].marks = Stu_ref.exam[0].sub[j].marks;
							}
							StuList[i].exam_cnt++;

							for (int j = 0; j < StuList[i].exam_cnt; j++) {
								StuList[i].exam[j].calculateGPA();
							}
							StuList[i].calculateCurrentCGPA();

							//sort past exam by year from a student
							bool checkSort;
							Exam sort_temp;
							do {
								checkSort = true;

								if (StuList[i].exam_cnt > 1) {
									sort(StuList[i].exam, StuList[i].exam + StuList[i].exam_cnt, [](const Exam& a, const Exam& b) {
										if (a.year != b.year) {
											return a.year < b.year;
										}
										else {
											return a.trimester < b.trimester;
										}
										});
									//first exam array to last exam array and define how two Exam objects should be compared for sorting.



									//for (int j = 0; j < Stu.exam_cnt - 1; j++) {
									//	if (Stu.exam[j].year > Stu.exam[j + 1].year ||
									//		(Stu.exam[j].year == Stu.exam[j + 1].year && Stu.exam[j].trimester > Stu.exam[j + 1].trimester)) { // (check year or ( check trisemester && in same year))
									//		sort_temp = Stu.exam[j];
									//		Stu.exam[j] = Stu.exam[j + 1];
									//		Stu.exam[j + 1] = sort_temp;
									//		checkSort = false;
									//	}
									//}
								}

							} while (!checkSort);
							//list->set(i, Stu);
						}
					}

					checkExistID = true;
					break;
				}
				else {
					checkExistID=false;
				}
			}

			//dum2 check exceed
			if (checkExceed) {
				if (Stu_ref.id.compare("0") > 0) {// check if the reference id is empty
					if (dum2.size() > 0) {//check if dummy list is empty, if not then only check for duplication, else just proceed to insert id
						for (int i = 1; i <= dum2.size(); i++) {
							//dum2.get(i, Stu);
							if (StuList[i].compareID(Stu_ref)) {
								duplicateDum2 = true;
							}
						}
					}
					if (!duplicateDum2) {

						//dum2.insert(Stu_ref);
						dum2.push_back(Stu_ref);
					}
				}
			}

			//dum3 check exist id
			if (!checkExistID) {
				if (Stu_ref.id.compare("0") > 0) {// check if the reference id is empty
					if (dum3.size() > 0) {//check if dummy list is empty, if not then only check for duplication, else just proceed to insert id
						for (int i = 1; i <= dum3.size(); i++) {
							//dum3.get(i, Stu);
							if (StuList[i].compareID(Stu_ref)) {
								duplicateDum3 = true;
							}
						}
					}
					if (!duplicateDum3) {
						dum3.push_back(Stu_ref);
					}
				}
			}
		}

		// output 3 type of error after read whole exam.txt
		if (dum1.size() > 0) {
			cout << "\nExam Duplication Error" << endl;
			cout << "-----------------------\n\n";
			for (Student student : dum1) {

				cout << "Error to insert " << student.id << " ( " << left << setw(20) << student.name << ") " << student.exam[0].printTrimester() << " " << student.exam[0].year << " exam info due to duplication.\n\n";

			}

		}

		if (dum2.size() > 0) {
			cout << "\nExam Excced 10 Record" << endl;
			cout << "-----------------------\n\n";
			cout << "**Please be noted that any exam records after the 10th exam of that particular student or repetitive records will be ignored.\n\n";
			for (Student student : dum2) {

				cout << "Error to insert " << student.id << " (" << left << setw(20) << student.name << ") " << student.exam[0].printTrimester() << " " << student.exam[0].year << " exam info due to exceed 10 exam records.\n\n";

			}
		}

		if (dum3.size() > 0) {
			cout << "\nStudent Not Found" << endl;
			cout << "-----------------\n\n";
			for (Student student : dum3) {
				cout << "No student with ID " << student.id << ". Failed to insert exam infomation.\n\n";
			}
		}

		inFile.close();
		return true;
	}
	else {
		return false;
	}
}

void insertNewStudent() {//3.Insert new student profile
	Student newStudent;

	cout << "Student ID:";
	newStudent.id = studentIdCheckDuplicate();

	cout << "Student Name:";
	getline(cin, newStudent.name);

	cout << "Course: ";

	newStudent.course = courseCheck();

	newStudent.phone = phoneCheck();

	StuList.push_back(newStudent);
	sort(StuList.begin(), StuList.end(), [](const Student& a, const Student& b) {
		return a.id < b.id;  // ascending order
		});

	cout << "Student Information Inserted Successfully.\n\n";
	char dumChoice[10];
	int choice = 0;
	bool checkRedirect = false;
	do {
		checkRedirect = true;
		cout << "Do you wish to\n\t1. Show the student information\n\t2. Add student " << newStudent.id << " exam information \n\t3. Add new student information\n\t4. Return\n";
		cin.getline(dumChoice, 10);
		choice = input_valid(dumChoice);
		switch (choice) {
		case 1:
			newStudent.print(cout);
			for (int i = 0; i < newStudent.exam_cnt; i++) {
				newStudent.exam[i].print(cout);
			}
			break;
		case 2:
			insertNewExam_id(newStudent.id);
			checkRedirect = false;
			break;
		case 3:
			insertNewStudent();
			break;
		case 4:
			Insert();
			break;
		default:
			cout << "Please enter valid number \n";
			checkRedirect = false;
		}
	} while (!checkRedirect);

}

bool insertNewExam() { //4.Insert exam profile
	Student student;
	string id;
	cout << "Enter student ID to add exam information:\n ";
	id = studentIdCheck();
	for (int i = 0; i < StuList.size(); i++) {
		if (id.compare(StuList[i].id) == 0) {
			if (StuList[i].exam_cnt >= 10) { //check exceed exam first
				cout << StuList[i].id << " exam record exceed 10\n";
				return false;
			}
			string input;
			int examCnt=StuList[i].exam_cnt;
			bool numSubsCheck = true;
			cout << "Enter Exam Information\n";
			cout << "Insert year and trimester\n";
			StuList[i].exam[examCnt].year = yearCheck();
			StuList[i].exam[examCnt].trimester = trimesterCheck();

			for (int j = 0; j < examCnt; j++) {
				if (StuList[i].exam[examCnt].trimester == StuList[i].exam[j].trimester && 
					StuList[i].exam[examCnt].year == StuList[i].exam[j].year) {
					cout << "Error. Duplicate exam year and trimester\n";
					return false;
				}
			}

			cout << "Enter number of subject (max 6)\n";
			do {
				numSubsCheck = true;
				getline(cin, input);
				StuList[i].exam[examCnt].numOfSubjects = input_valid_string(input);
				if (StuList[i].exam[examCnt].numOfSubjects > 6 || StuList[i].exam[examCnt].numOfSubjects <= 0) {
					cout << "Invalid subjects number. Try again.\n";
					numSubsCheck = false;
				}
			} while (!numSubsCheck);
			for (int k = 0; k < StuList[i].exam[examCnt].numOfSubjects; k++) {
				char input_code[10];
				bool duplicateSubject;
				do {
					duplicateSubject = false;
					cout << "Subject code " << k + 1 << " \n";
					cin.getline(input_code, 10);
					for (int l = 0; l < k; l++) {
						if (strcmp(StuList[i].exam[examCnt].sub[l].subject_code, input_code) == 0) {
							cout << "Duplictaed subject code in that semester. Failed to insert\n";
							duplicateSubject = true;

							break;
						}
					}
				} while (duplicateSubject);

				if (!duplicateSubject) {
					strcpy(StuList[i].exam[examCnt].sub[k].subject_code, input_code);
				}
				
				cout << "Subject name " << k+1 << " \n";
				cin.getline(StuList[i].exam[examCnt].sub[k].subject_name, 256);

				cout << "Subject credit hours " << k+1 << " \n";
				getline(cin, input);
				StuList[i].exam[examCnt].sub[k].credit_hours = input_valid_string(input);

				cout << "Subject "<<k+1<<" marks \n";
				getline(cin, input);
				StuList[i].exam[examCnt].sub[k].marks = input_valid_double(input);
				cout << "\n\n";
			}
			StuList[i].exam[examCnt].calculateGPA();
			StuList[i].exam_cnt++;
			StuList[i].calculateCurrentCGPA();

			//sort
			sort(StuList[i].exam, 
				StuList[i].exam+StuList[i].exam_cnt,
				[](const Exam& a, const Exam& b) { //lambda function comparing two exam
				if (a.year == b.year) {
					return a.trimester < b.trimester; //sort by ascending
				}
				return a.year < b.year;
				});

			cout << "\nExam added successfully for student " << StuList[i].id << ".\n";
			char dumChoice[10];
			int choice = 0;
			bool checkRedirect = false;
			do {
				checkRedirect = true;
				cout << "Do you wish to\n\t1. Show student information\n\t2. Add student " << StuList[i].id << " exam information \n\t3. Return\n";
				cin.getline(dumChoice, 10);
				choice = input_valid(dumChoice);
				switch (choice) {
				case 1:
					StuList[i].print(cout);
					for (int j = 0; j < StuList[i].exam_cnt; j++) {
						StuList[i].exam[j].print(cout);
					}
					break;
				case 2:
					insertNewExam_id(StuList[i].id);
					checkRedirect = false;
					break;
				case 3:
					Insert();
					break;
				default:
					cout << "Please enter valid number \n";
					checkRedirect = false;
				}
			} while (!checkRedirect);
			return true;
		}
	}
	//no student found, outside for loop
	cout << "The student id invalid\n";
	return false;
}


bool insertNewExam_id(string id) {
	Student student;
	for (int i = 0; i < StuList.size(); i++) {
		if (id.compare(StuList[i].id) == 0) {
			if (StuList[i].exam_cnt >= 10) { //check exceed exam first
				cout << StuList[i].id << " exam record exceed 10\n";
				return false;
			}
			string input;
			int examCnt=StuList[i].exam_cnt;
			bool numSubsCheck = true;
			cout << "Enter Exam Information\n";
			cout << "Insert year and trimester\n";

			StuList[i].exam[examCnt].year = yearCheck();
			StuList[i].exam[examCnt].trimester = trimesterCheck();

			for (int j = 0; j < examCnt; j++) {
				if (StuList[i].exam[examCnt].trimester == StuList[i].exam[j].trimester && 
					StuList[i].exam[examCnt].year == StuList[i].exam[j].year) {
					cout << "Error. Duplicate exam year and trimester\n";
					return false;
				}
			}

			cout << "Enter number of subject (max 6)\n";
			do {
				numSubsCheck = true;
				getline(cin, input);
				StuList[i].exam[examCnt].numOfSubjects = input_valid_string(input);
				if (StuList[i].exam[examCnt].numOfSubjects > 6 || StuList[i].exam[examCnt].numOfSubjects <= 0) {
					cout << "Invalid subjects number. Try again.\n";
					numSubsCheck = false;
				}
			} while (!numSubsCheck);
			for (int k = 0; k < StuList[i].exam[examCnt].numOfSubjects; k++) {
				cout << "Subject code "<<k+1<<" \n";
				cin.getline(StuList[i].exam[examCnt].sub[k].subject_code, 10);

				cout << "Subject name " << k+1 << " \n";
				cin.getline(StuList[i].exam[examCnt].sub[k].subject_name, 256);

				cout << "Subject credit hours " << k+1 << " \n";
				getline(cin, input);
				StuList[i].exam[examCnt].sub[k].credit_hours = input_valid_string(input);

				cout << "Subject "<<k+1<<" marks \n";
				do {
					getline(cin, input);
					StuList[i].exam[examCnt].sub[k].marks = input_valid_double(input);
					if (StuList[i].exam[examCnt].sub[k].marks < 0 || StuList[i].exam[examCnt].sub[k].marks>100) {
						cout << "invalid mark\n";
					}
				} while (StuList[i].exam[examCnt].sub[k].marks < 0 || StuList[i].exam[examCnt].sub[k].marks>100);

				cout << "\n\n";
			}
			StuList[i].exam[examCnt].calculateGPA();
			StuList[i].exam_cnt++;
			StuList[i].calculateCurrentCGPA();

			//sort
			sort(StuList[i].exam, 
				StuList[i].exam+StuList[i].exam_cnt,
				[](const Exam& a, const Exam& b) { //lambda function comparing two exam
				if (a.year == b.year) {
					return a.trimester < b.trimester; //sort by ascending
				}
				return a.year < b.year;
				});

			cout << "\nExam added successfully for student " << StuList[i].id << ".\n";
			char dumChoice[10];
			int choice = 0;
			bool checkRedirect = false;
			do {
				checkRedirect = true;
				cout << "Do you wish to\n\t1. Show student information\n\t2. Add student " << StuList[i].id << " exam information \n\t3. Return\n";
				cin.getline(dumChoice, 10);
				choice = input_valid(dumChoice);
				switch (choice) {
				case 1:
					StuList[i].print(cout);
					for (int j = 0; j < StuList[i].exam_cnt; j++) {
						StuList[i].exam[j].print(cout);
					}
					break;
				case 2:
					insertNewExam_id(StuList[i].id);
					checkRedirect = false;
					break;
				case 3:
					Insert();
					break;
				default:
					cout << "Please enter valid number \n";
					checkRedirect = false;
				}
			} while (!checkRedirect);
			return true;
		}
	}
	//no student found, outside for loop
	cout << "The student id invalid\n";
	return false;

}


