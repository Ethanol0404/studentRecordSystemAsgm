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
				Modify();
			};
			break;
		case 2:
			editExam();
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

bool editStudent() {
	Student* studentFound = nullptr;
	string input;
	bool format, format1,inputCheck, studentCheck=false, duplicateCheck;
	do {
		format = true, format1 = true;
		cout << "Enter Student ID to edit\n";
		getline(cin, input);
		if (input.length() != 7) {
			cout << "Student ID must be exact 7 character\n";
			format = false;
		}
		for (int i = 0; i < input.length(); i++) {
			if (!isdigit(input[i])) {
				format = false;
				format1 = false;
			}
		}
		if (!format1) {
			cout << "Student ID must digit only\n";
		}
	} while (!format);

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
	cout << "Please choose one or more following criteria to edit by leaving a space\n";
	cout << "1. ID\n2. Name\n3. course\n4. Phone\n\n";
	getline(cin, input);

	vector<int> choices = handleChoices(input, 4);

	for (int choice : choices) {
		switch (choice) {
		case 1:
			cout << "Enter new ID\n";
			do {
				inputCheck = true;
				getline(cin, input);
				for (Student student : StuList) {
					if (input == student.id && &student != studentFound) {
						cout << "ID duplicated. Please try again\n";
						inputCheck = false;
					}
				}
				studentFound->id = input;
			} while (!inputCheck);
			break;
		case 2:
			cout << "Enter new Name\n";
			getline(cin, studentFound->name);
			break;
		case 3:
			cout << "Enter new Course\n";
			getline(cin, studentFound->course);
			break;
		case 4:
			cout << "Enter new Phone\n";
			getline(cin, studentFound->phone);
			break;
		}
	}
	cout << "Do you want to display results? (Y/N): "; //prompt user to output
	char printChoice = ' ';
	do {//Input validation
		cin >> printChoice;
		cin.ignore();
		if (tolower(printChoice) != 'y' && tolower(printChoice) != 'n') {
			cout << "\nPlease input only Y or N: ";
		}
	} while (tolower(printChoice) != 'y' && tolower(printChoice) != 'n');

	if (tolower(printChoice) == 'y') {
		cout << "Current Student list:\n";
		studentFound->print(cout);
		cout << "**Please remember to copy data to a safe place to prevent loss of data.\n";
	}

	return true;
}

bool editExam() {
	Student* studentFound = nullptr;
	Exam* editExam = nullptr;
	Subject* editSubject = nullptr;
	string input;
	char input_code[10];
	bool format, format1, inputCheck, studentCheck = false, duplicateCheck, yearCheck, trimesterCheck, existCheck;

	//switch
	int year, trimester;
	int subjectCnt = 0; //check duplicate subject on that semester

	do {
		format = true, format1 = true;
		cout << "Enter Student ID to edit\n";
		getline(cin, input);
		if (input.length() != 7) {
			cout << "Student ID must be exact 7 character\n";
			format = false;
		}
		for (int i = 0; i < input.length(); i++) {
			if (!isdigit(input[i])) {
				format = false;
				format1 = false;
			}
		}
		if (!format1) {
			cout << "Student ID must digit only\n";
		}
	} while (!format);


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
	PrintList({*studentFound}, 1); //temporary initializer list
	cout << "Please choose one or more following criteria to edit by leaving a space\n";
	cout << "1. Exam year and trimeseter\n2. Subject Code\n3. Subject Name\n4. Subject Credit Hours\n5. Subject Marks\n";
	getline(cin, input);
	vector<int> choices = handleChoices(input, 5);

	//confirm to edit same year and trimester in all option
	cout << "Do you want to edit field with same year and trimester (Y/N)\n";
	char printChoice = ' ';
	do {
		cin >> printChoice;
		cin.ignore();
		if (tolower(printChoice) != 'y' && tolower(printChoice) != 'n') {
			cout << "\nPlease input only Y or N: ";
		}
	} while (tolower(printChoice) != 'y' && tolower(printChoice) != 'n');

	if (tolower(printChoice) == 'y') {
		cout << "Select year from student record\n";
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
		cout << "Select trimester from student record\n";
		do {
			trimesterCheck = true;
			getline(cin, input);
			trimester = input_valid_string(input);
			if (trimester != 1 && trimester != 5 && trimester != 10) {
				trimesterCheck = false;
				cout << "Trimester incorrect. Try again.\n";
			}

		} while (!trimesterCheck);

		//check exist
		for (Student& student : StuList) {
			for (int i = 0; i < student.exam_cnt; i++) {
				if (year > 0 && year == student.exam[i].year) {
					if (trimester == student.exam[i].trimester) {
						editExam = &student.exam[i];
						break;
					}
				}
			}
		}
		if (editExam == nullptr) {
			cout << "Exam not found\n";
			return false;
		}
	}

	for (int choice : choices) {
		if (tolower(printChoice) == 'n') {
			cout << "choice " << choice << "\n";
			cout << "Select year from student record\n";
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
			cout << "Select trimester from student record\n";
			do {
				trimesterCheck = true;
				getline(cin, input);
				trimester = input_valid_string(input);
				if (trimester != 1 && trimester != 5 && trimester != 10) {
					trimesterCheck = false;
					cout << "Trimester incorrect. Try again.\n";
				}

			} while (!trimesterCheck);

			//check exist
			for (Student& student : StuList) {
				for (int i = 0; i < student.exam_cnt; i++) {
					if (year > 0 && year == student.exam[i].year) {
						if (trimester == student.exam[i].trimester) {
							editExam = &student.exam[i];
							break;
						}
					}
				}
			}
			if (editExam == nullptr) {
				cout << "Exam not found\n";
				continue; //skip this edit
			}
		}

		switch (choice) {
		case 1:
			cout << "Enter a year\n";
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
			cout << "Enter a trimester\n";
			do {
				trimesterCheck = true;
				getline(cin, input);
				trimester = input_valid_string(input);
				if (trimester != 1 && trimester != 5 && trimester != 10) {
					trimesterCheck = false;
					cout << "Trimester incorrect. Try again.\n";
				}

			} while (!trimesterCheck);

			//check exist
			existCheck = false;
			for (Student& student : StuList) {
				for (int i = 0; i < student.exam_cnt; i++) {
					if (year > 0 && year == student.exam[i].year) {
						if (trimester == student.exam[i].trimester) {
							cout << year << " " << trimester << " existed. Failed to modify.\n";
							existCheck = true;
							break;
						}
					}
				}
			}
			if (!existCheck) {
				editExam->year = year;
				editExam->trimester = trimester;
			}
			break;
		case 2:
			existCheck = false;
			subjectCnt = 0;
			cout << "Enter subject code to edit\n";
			cin.getline(input_code, 10);
			for (int i = 0; i < editExam->numOfSubjects; i++) {
				if (strcmp(input_code, editExam->sub[i].subject_code) == 0) {
					editSubject = &editExam->sub[i];
					subjectCnt++;
					if (subjectCnt == 1) {
						existCheck = true;
					}else{ //subjectCnt>1
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

			break;
		case 3:
			existCheck = false;
			cout << "Enter subject code to verify\n";
			cin.getline(input_code, 10);
			for (int i = 0; i < editExam->numOfSubjects; i++) {
				if (strcmp(input_code, editExam->sub[i].subject_code) == 0) {
					editSubject = &editExam->sub[i];
					existCheck = true;
					break;
				}
			}
			if (existCheck) {
				cout << "Enter subject name to edit\n";
				cin.getline(editSubject->subject_name, 256);
			}
			break;
		case 4:
			existCheck = false;
			cout << "Enter subject code to verify\n";
			cin.getline(input_code, 10);
			for (int i = 0; i < editExam->numOfSubjects; i++) {
				if (strcmp(input_code, editExam->sub[i].subject_code) == 0) {
					editSubject = &editExam->sub[i];
					existCheck = true;
					break;
				}
			}
			if (existCheck) {
				cout << "Enter subject credit hours to edit\n";
				getline(cin, input);
				editSubject->credit_hours = input_valid_string(input);
			}
			break;
		case 5:
			existCheck = false;
			cout << "Enter subject code to verify\n";
			cin.getline(input_code, 10);
			for (int i = 0; i < editExam->numOfSubjects; i++) {
				if (strcmp(input_code, editExam->sub[i].subject_code) == 0) {
					editSubject = &editExam->sub[i];
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
			break;
		}
	}
	editExam->calculateGPA();
	studentFound->calculateCurrentCGPA();

	printResult({ *studentFound });
	//studentFoundVector.clear();
	//studentFoundVector.push_back(*studentFound);
	//printResult(studentFoundVector);
	return true;
}



bool Delete() {
	cout << "Delete\n1. Student Record\n2. Exam Record\n3. Subject\n";
	char deleteOption = ' ';
	string input;
	bool format, format1;
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
		getline(cin, input);
		do {
			format = true, format1 = true;
			if (input.length() != 7) {
				cout << "Student ID must be exact 7 character\n";
				format = false;
			}
			for (int i = 0; i < input.length(); i++) {
				if (!isdigit(input[i])) {
					format = false;
					format1 = false;
				}
			}
			if (!format1) {
				cout << "Student ID must digit only\n";
			}
		} while (!format);

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
				char comfirm = ' ';
				do {
					cin >> comfirm;
					cin.ignore();
					if (tolower(comfirm) != 'y' && tolower(comfirm) != 'n') {
						cout << "invalid. Please type only 'y' and 'n'\n";
					}

				} while (tolower(comfirm) != 'y' && tolower(comfirm) != 'n');
				if (tolower(comfirm) == 'y') {
					cout << "Student record " << StuList[i].id << " " << "( " << StuList[i].name << " ) removed successfully.\n\n";
					StuList.erase(StuList.begin() + i);
					found = true;
				}
				break;
			}
		}

		printResult(StuList);

		return found;
	}
	else if(deleteOption - '0' == 2){ //'2'
		Student* studentFound=nullptr;
		int year, trimester;
		bool yearCheck, trimesterCheck, found=false;
		do {
			format = true, format1 = true;
			cout << "Enter Student ID to verify\n";
			getline(cin, input);
			if (input.length() != 7) {
				cout << "Student ID must be exact 7 character\n";
				format = false;
			}
			for (int i = 0; i < input.length(); i++) {
				if (!isdigit(input[i])) {
					format = false;
					format1 = false;
				}
			}
			if (!format1) {
				cout << "Student ID must digit only\n";
			}
		} while (!format);

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
		cout << "Select trimester from student record\n";
		do {
			trimesterCheck = true;
			getline(cin, input);
			trimester = input_valid_string(input);
			if (trimester != 1 && trimester != 5 && trimester != 10) {
				trimesterCheck = false;
				cout << "Trimester incorrect. Try again.\n";
			}

		} while (!trimesterCheck);

		//check exist
		for (int i = 0; i < studentFound->exam_cnt; i++) {
			if (year > 0 && year == studentFound->exam[i].year) {
				if (trimester == studentFound->exam[i].trimester) {
					cout << "Are you sure to delete " << studentFound->exam[i].year<<" "<< studentFound->exam[i].trimester << " exam record? (y/n)\n";
					char comfirm = ' ';
					do {
						cin >> comfirm;
						cin.ignore();
						if (tolower(comfirm) != 'y' && tolower(comfirm) != 'n') {
							cout << "invalid. Please type only 'y' and 'n'\n";
						}

					} while (tolower(comfirm) != 'y' && tolower(comfirm) != 'n');
					if (tolower(comfirm) == 'y') {
						cout << "Student record " << studentFound->exam[i].year << " " << studentFound->exam[i].trimester << " exam record removed successfully.\n\n";
						for (int j = i+1; j < studentFound->exam_cnt; j++) {
							studentFound->exam[j-1] = studentFound->exam[j];
						}
						found = true;
						studentFound->exam_cnt--;
					}
					break;
				}
			}
		}
		studentFound->calculateCurrentCGPA();
		printResult(StuList);
		return found;
	}
	else {//3
		Student* studentFound = nullptr;
		Exam* deleteExam = nullptr;
		int year, trimester;
		bool yearCheck, trimesterCheck, found = false;
		char input_code[10];
		do {
			format = true, format1 = true;
			cout << "Enter Student ID to verify\n";
			getline(cin, input);
			if (input.length() != 7) {
				cout << "Student ID must be exact 7 character\n";
				format = false;
			}
			for (int i = 0; i < input.length(); i++) {
				if (!isdigit(input[i])) {
					format = false;
					format1 = false;
				}
			}
			if (!format1) {
				cout << "Student ID must digit only\n";
			}
		} while (!format);

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
		cout << "Select trimester from student record\n";
		do {
			trimesterCheck = true;
			getline(cin, input);
			trimester = input_valid_string(input);
			if (trimester != 1 && trimester != 5 && trimester != 10) {
				trimesterCheck = false;
				cout << "Trimester incorrect. Try again.\n";
			}

		} while (!trimesterCheck);

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
				char comfirm = ' ';
				do {
					cin >> comfirm;
					cin.ignore();
					if (tolower(comfirm) != 'y' && tolower(comfirm) != 'n') {
						cout << "invalid. Please type only 'y' and 'n'\n";
					}

				} while (tolower(comfirm) != 'y' && tolower(comfirm) != 'n');
				if (tolower(comfirm) == 'y') {
					cout << "Student record " << deleteExam->sub[i].subject_code << " exam record removed successfully.\n\n";
					for (int j = i + 1; j < deleteExam->numOfSubjects; j++) {
						deleteExam->sub[j-1] = deleteExam->sub[j];
					}
					found = true;
					deleteExam->numOfSubjects--;
				}
				break;
			}
		}
		deleteExam->calculateGPA();
		studentFound->calculateCurrentCGPA();
		printResult(StuList);
		return found;
	}
}

