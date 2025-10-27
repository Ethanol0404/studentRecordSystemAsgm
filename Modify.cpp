#include	"Modify.h"

bool Modify() {
	system("cls");
	cout << "Modify \n";
	cout << "=======================\n";
	cout << "1. Edit Student Information\n2. Edit Exam Information\n3. Delete\n4. Return\n";
	int choice = 0;
	char dumChoice[10], reply;
	bool checkRedirect = true;
	do {
		cin.getline(dumChoice, 10);
		choice = input_valid(dumChoice);
		switch (choice) {
		case 1:
			if (!editStudent()) {
				cout<<"Student not found\n";
			};
			break;
		case 2:
			if (!editExam()) {
				Modify();
			}
			break;
		case 3:
			Delete();
			break;
		case 4:
			return true;
			break;
		default:
			cout << "Please enter valid number \n";
			checkRedirect = false;
		}
	} while (!checkRedirect);

	return false;
}

bool editStudent(string input) {
	Student* studentFound = nullptr;
	bool studentCheck=false;

	if (input.empty()) {
		cout << "Enter student ID to edit:\n";
		input = studentIdCheck();
	}

	for (Student& student : StuList) { //& make reference
		if (student.id == input) {
			studentFound = &student;
			break;
		}
	}
	if (studentFound == nullptr) {
		cout << "Student not found\n";
		return false;
	}
	studentFound->print(cout);
	cout << "\nPlease choose one or more following criteria to edit by leaving a space\n";
	cout << "1. ID\n2. Name\n3. course\n4. Phone\n\n";
	getline(cin, input);

	vector<int> choices = handleChoices(input, 4);

	for (int choice : choices) {
		switch (choice) {
		case 1:
			cout << "Enter new ID\n";
			studentFound->id = studentIdCheckDuplicate();
			break;
		case 2:
			cout << "Enter new Name\n";
			getline(cin, studentFound->name);
			break;
		case 3:
			cout << "Enter new Course\n";
			studentFound->course=courseCheck();
			break;
		case 4:
			cout << "Enter new Phone\n";
			studentFound->phone=phoneCheck();
			break;
		}
	}
	delay(studentFound->id+" edit successfully\n");
	cout << "Do you want to display results? (Y/N): "; //prompt user to output

	if (yesNo()) {
		cout << "Current Student list:\n";
		studentFound->print(cout);
		cout << "**Please remember to copy data to a safe place to prevent loss of data.\n\nDo you want to edit this student again? (Y/N)\n";
		if (yesNo()) {
			editStudent(studentFound->id);
		}
		else {
			cout << "Continue edit (Y/N)\n";
			if (yesNo()) {
				editStudent(); //recursive call
			}
		}
	}

	return true;
}

bool editExam(string input1) {
	Student* studentFound = nullptr;
	Exam* examToEdit = nullptr;
	Subject* editSubject = nullptr;
	string input;
	char input_code[10];
	bool sameExam, studentCheck = false, existCheck;

	//sort
	bool checkSort;
	Exam sort_temp;

	//switch
	int year, trimester;
	int subjectCnt = 0; //check duplicate subject on that semester

	if (input1.empty()) {
		cout << "Enter student ID to edit:\n";
		input1 = studentIdCheck();
	}

	for (Student& student : StuList) { //& make reference
		if (student.id == input1) {
			studentFound = &student;
			break;
		}
	}
	if (studentFound == nullptr) {
		cout << "Student not found\n";
		return false;
	}
	PrintList({ *studentFound }, 1); //temporary initializer list
	cout << "Please choose one or more following criteria to edit by leaving a space\n";
	cout << "1. Exam year and trimeseter\n2. Subject Code\n3. Subject Name\n4. Subject Credit Hours\n5. Subject Marks\n";
	getline(cin, input);
	vector<int> choices = handleChoices(input, 5);

	//confirm to edit same year and trimester in all option
	cout << "Do you want to edit field with same year and trimester (Y/N)\n";

	if (yesNo()) {
		sameExam = true;
		cout << "Select year from student record\n";
		year = yearCheck();
		trimester = trimesterCheck();

		//check exist
		for (int i = 0; i < studentFound->exam_cnt; i++) {
			if (year == studentFound->exam[i].year && trimester == studentFound->exam[i].trimester) {
				examToEdit = &studentFound->exam[i];
				break;
			}
		}

		if (examToEdit == nullptr) {
			cout << "\n\nExam not found\n";
			cout << "Do you want to modify again? (y/n)\n";
			if (yesNo()) {
				editExam(studentFound->id);
			}
			else {
				Modify();
			}
		}
	}
	else {
		sameExam = false;
	}

	for (int choice : choices) {
		if (!sameExam) {
			cout << "\nchoice " << choice << "\n";
			cout << "Select year from student record\n";
			year = yearCheck();
			trimester = trimesterCheck();

			//check exist
			for (int i = 0; i < studentFound->exam_cnt; i++) {
				if (year == studentFound->exam[i].year && trimester == studentFound->exam[i].trimester) {
					examToEdit = &studentFound->exam[i];
					break;
				}
			}

			if (examToEdit == nullptr) {
				cout << "\n\nExam not found\n";
				cout << "Do you want to modify again? (y/n)\n";
				if (yesNo()) {
					editExam(studentFound->id);
				}
				else {
					Modify();
				}
			}
		}

		switch (choice) {
		case 1:
			cout << "Enter a year and trimester to change\n";
			year = yearCheck();
			trimester = trimesterCheck();

			//check exist
			existCheck = false;
			for (int i = 0; i < studentFound->exam_cnt; i++) {
				if (year > 0 && year == studentFound->exam[i].year) {
					if (trimester == studentFound->exam[i].trimester) {
						existCheck = true;
						break;
					}
				}
			}
			if (!existCheck) {
				examToEdit->year = year;
				examToEdit->trimester = trimester;

				//sort
				do {
					checkSort = true;

					if (studentFound->exam_cnt > 1) {
						sort(studentFound->exam, studentFound->exam + studentFound->exam_cnt, [](const Exam& a, const Exam& b) {
							if (a.year != b.year) {
								return a.year < b.year;
							}
							else {
								return a.trimester < b.trimester;
							}
							});
					}

				} while (!checkSort);
			}
			else {
				cout << year << " " << trimester << " existed. Failed to modify.\n";
			}

			break;



		case 2:
			existCheck = false;
			subjectCnt = 0;
			cout << "Enter subject code to edit\n";
			cin.getline(input_code, 10);
			for (int i = 0; i < examToEdit->numOfSubjects; i++) {
				if (strcmp(input_code, examToEdit->sub[i].subject_code) == 0) {
					editSubject = &examToEdit->sub[i];
					subjectCnt++;
					if (subjectCnt == 1) {
						existCheck = true;
					}
					else { //subjectCnt>1
						cout << "Duplicate subject code " << input_code << " in this semester. Failed to modify.\n";
						existCheck = false;
						break;
					}
				}
			}
			if (existCheck) {
				cout << "Enter new subject code\n";
				cin.getline(input_code, 10);
				strcpy(editSubject->subject_code, input_code);
			}
			else {
				cout << "This subject code not exist\n";
			}

			break;
		case 3:
			existCheck = false;
			cout << "Enter subject code to verify\n";
			cin.getline(input_code, 10);
			for (int i = 0; i < examToEdit->numOfSubjects; i++) {
				if (strcmp(input_code, examToEdit->sub[i].subject_code) == 0) {
					editSubject = &examToEdit->sub[i];
					existCheck = true;
					break;
				}
			}
			if (existCheck) {
				cout << "Enter subject name to edit\n";
				cin.getline(editSubject->subject_name, 256);
			}
			else {
				cout << "This subject code not exist\n";
			}
			break;
		case 4:
			existCheck = false;
			cout << "Enter subject code to verify\n";
			cin.getline(input_code, 10);
			for (int i = 0; i < examToEdit->numOfSubjects; i++) {
				if (strcmp(input_code, examToEdit->sub[i].subject_code) == 0) {
					editSubject = &examToEdit->sub[i];
					existCheck = true;
					break;
				}
			}
			if (existCheck) {
				cout << "Enter subject credit hours to edit\n";
				getline(cin, input);
				editSubject->credit_hours = input_valid_string(input);
			}
			else {
				cout << "This subject code not exist\n";
			}
			break;
		case 5:
			existCheck = false;
			cout << "Enter subject code to verify\n";
			cin.getline(input_code, 10);
			for (int i = 0; i < examToEdit->numOfSubjects; i++) {
				if (strcmp(input_code, examToEdit->sub[i].subject_code) == 0) {
					editSubject = &examToEdit->sub[i];
					existCheck = true;
					break;
				}
			}
			if (existCheck) {
				cout << "Enter subject mark to edit\n";
				do {
					getline(cin, input);
					editSubject->marks = input_valid_double(input);
					if (editSubject->marks < 0 || editSubject->marks>100) {
						cout << "invalid mark\n";
					}
				} while (editSubject->marks < 0 || editSubject->marks>100);
			}
			else {
				cout << "This subject code not exist\n";
			}
			break;
		}
	}
	
	examToEdit->calculateGPA();
	studentFound->calculateCurrentCGPA();

	printResult({ *studentFound });
	cout << "\nDo you want to edit this student exam again? (Y/N)\n";
	if (yesNo()) {
		editExam(studentFound->id);
	}
	else {
		cout << "Continue edit (Y/N)\n";
		if (yesNo()) {
			editExam(); //recursive call
		}
	}
	//studentFoundVector.clear();
	//studentFoundVector.push_back(*studentFound);
	//printResult(studentFoundVector);
	return true;
}



bool Delete() {
	cout << "Delete\n1. Student Record\n2. Exam Record\n3. Subject\n";
	char deleteOption = ' ';
	string input;
	char printChoice = ' ';
	do {
		cin >> deleteOption;
		cin.ignore();
		if (deleteOption != '1' && deleteOption != '2' && deleteOption != '3') {
			cout << "invalid. try again\n";
		}
	} while (deleteOption != '1' && deleteOption != '2' && deleteOption != '3');

	if (deleteOption - '0' == 1) { //convert to intz
		cout << "Enter Student ID to delete\n";
		input = studentIdCheck();

		if (StuList.empty()) { //check if list is empty
			cout << "Student record is empty. Please try inserting some info first.\n\n";
			return false;
		}
		bool found = false;
		for (int i = 0; i < StuList.size(); i++) {
			if (StuList[i].id.compare(input) == 0) {
				cout << "Student Found\n";
				StuList[i].print(cout);
				for (int j = 0; j < StuList[i].exam_cnt; j++) {
					StuList[i].exam[j].print(cout);
				}
				cout << "Are you sure to delete " << StuList[i].id << " ? (y/n)\n";
				if (yesNo()) {
					cout << "Student record " << StuList[i].id << " " << "( " << StuList[i].name << " ) removed successfully.\n\n";
					StuList.erase(StuList.begin() + i);
					found = true;
					cout << "\nDo you want to check all student ? (y / n)\n";
					if (yesNo()) {
						printResult(StuList);
					}
				}

				break;
			}
		}

		return found;
	}
	else if(deleteOption - '0' == 2){ //'2'
		Student* studentFound=nullptr;
		int year, trimester;
		bool found=false;
		cout << "Enter Student ID to verify\n";
		input = studentIdCheck();


		if (StuList.empty()) { //check if list is empty
			cout << "Student record is empty. Please try inserting some info first.\n\n";
			return false;
		}

		for (int i = 0; i < StuList.size(); i++) {
			if (StuList[i].id.compare(input) == 0) {
				cout << "Student Found\n";
				studentFound = &StuList[i];
				break;
			}
		}

		if (studentFound == nullptr) {
			cout << "Student id not found\n";
			return false;
		}
		//print
		studentFound->print(cout);
		for (int j = 0; j < studentFound->exam_cnt; j++) {
			studentFound->exam[j].print(cout);
		}


		cout << "Please select year and trimester to delete.\n";
		cout << "Select year from student record\n";
			year = yearCheck();
			trimester = trimesterCheck();

		//check exist
		for (int i = 0; i < studentFound->exam_cnt; i++) {
			if (year > 0 && year == studentFound->exam[i].year) {
				if (trimester == studentFound->exam[i].trimester) {
					cout << "Are you sure to delete " << studentFound->exam[i].year<<" "<< studentFound->exam[i].trimester << " exam record? (y/n)\n";
			
					if (yesNo()) {
						cout << "Student record " << studentFound->exam[i].year << " " << studentFound->exam[i].trimester << " exam record removed successfully.\n\n";
						for (int j = i+1; j < studentFound->exam_cnt; j++) {
							studentFound->exam[j-1] = studentFound->exam[j];
						}
						found = true;
						studentFound->exam_cnt--;
						studentFound->calculateCurrentCGPA();
						cout << "\nDo you want to check this student ? (y / n)\n";
						if (yesNo()) {
							studentFound->print(cout);
							for (int i = 0; i < studentFound->exam_cnt; i++) {
								studentFound->exam[i].print(cout);
							}
						}
					}
					break;
				}
			}
		}
		return found;
	}
	else {//3
		Student* studentFound = nullptr;
		Exam* deleteExam = nullptr;
		int year, trimester;
		bool found = false;
		char input_code[10];

		cout << "Enter Student ID to verify\n";
		input = studentIdCheck();

		if (StuList.empty()) { //check if list is empty
			cout << "Student record is empty. Please try inserting some info first.\n\n";
			return false;
		}

		for (int i = 0; i < StuList.size(); i++) {
			if (StuList[i].id.compare(input) == 0) {
				cout << "Student Found\n";
				studentFound = &StuList[i];
				break;
			}
		}

		if (studentFound == nullptr) {
			cout << "Student id not found\n";
			return false;
		}

		//print
		studentFound->print(cout);
		for (int j = 0; j < studentFound->exam_cnt; j++) {
			studentFound->exam[j].print(cout);
		}


		cout << "Please select year and trimester to verify.\n";
		cout << "Select year from student record\n";
		year = yearCheck();
		trimester = trimesterCheck();

		//check exist
		for (int i = 0; i < studentFound->exam_cnt; i++) {
			if (year > 0 && year == studentFound->exam[i].year) {
				if (trimester == studentFound->exam[i].trimester) {
					 deleteExam = &studentFound->exam[i];
					 break;
				}
			}
		}

		if (deleteExam==nullptr) {
			cout << "Exam " << year << " " << trimester << " no exist. Failed to delete\n";
			return false;
		}

		cout << "Enter subject code to edit\n";
		cin.getline(input_code, 10);

		for (int i = 0; i < deleteExam->numOfSubjects; i++) {
			if (strcmp(input_code, deleteExam->sub[i].subject_code) == 0) {

				cout << "Are you sure to delete " << deleteExam->sub[i].subject_code << " exam record? (y/n)\n";
				
				if (yesNo()) {
					cout << "Student record " << deleteExam->sub[i].subject_code << " exam record removed successfully.\n\n";
					for (int j = i + 1; j < deleteExam->numOfSubjects; j++) {
						deleteExam->sub[j-1] = deleteExam->sub[j];
					}
					found = true;
					deleteExam->numOfSubjects--;
					deleteExam->calculateGPA();
					studentFound->calculateCurrentCGPA();
					cout << "\nDo you want to check this student ? (y / n)\n";
					if (yesNo()) {
						studentFound->print(cout);
						for (int i = 0; i < studentFound->exam_cnt; i++) {
							studentFound->exam[i].print(cout);
						}
					}
				}
				break;
			}
		}
		return found;
	}
}

