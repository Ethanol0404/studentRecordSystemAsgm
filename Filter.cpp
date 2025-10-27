#include	"Filter.h"

vector<Student>FilterList;


bool mainFilter() {
	system("cls");
	cout << "Filter/ Search \n";
	cout << "=======================\n";
	cout << "1. Standard Filter\n2. Range Filter\n3. Search\n4. Multi-Search\n5. Return\n";
	int choice = 0;
	char dumChoice[10];
	bool checkRedirect = true;
	do {
		cin.getline(dumChoice, 10);
		choice = input_valid(dumChoice);
		switch (choice) {
		case 1:
			if (!Standard_Filter()) {
				cout << "The result is empty.\n";
			}
			break;
		case 2:
			if (!Range_Filter()) {
				cout << "The result is empty.\n";
			}
			break;
		case 3:
			if (!Search()) {
				cout << "The result is empty.\n";
			}
			break;
		case 4:
			if (!multiSearch()) {
				cout << "The result is empty.\n";
			};
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


bool Standard_Filter() {
	string year_str, course;
	bool cases = true;
	int year = 0, totalCredit = 0;
	cout << "Please input '-1' if you do not want to filter that particular criteria.\n\n";
	cout << "Insert course to filter: ";
	getline(cin, course);
	cout << "\nInsert year to filter: ";
	cin >> year;
	cin.ignore();
	cout << "\nInsert total credit hours to filter: ";
	cin >> totalCredit;
	cin.ignore();

	if (StuList.empty()) {
		cout << "\n\nStudent record is empty. Please try inserting some info first.\n\n";
		return false;
	}
	else {

		for (int i = 0; i < StuList.size(); i++) {

			if (course.compare( "-1") != 0) {

				if (StuList[i].course.compare(course) != 0) {
					cases = false;
				}

			}


			if (cases) {
				if (year != -1) {
					string id(StuList[i].id); //change student id from char to string
					year_str = to_string(year); //change year from int to string
					if (year_str.substr(2, 2) != id.substr(0, 2)) { //compare last two char of yr to first two char of id
						cases = false;
					}

				}

			}

			if (cases) {
				if (totalCredit != -1) {
					int stu_totalcred = 0;
					for (int j = 0; j < StuList[i].exam_cnt; j++) {
						for (int k = 0; k < StuList[i].exam[j].numOfSubjects; k++) {
							stu_totalcred += StuList[i].exam[j].sub[k].credit_hours;
						}
					}
					if (stu_totalcred < totalCredit) {
						cases = false;
					}

				}
			}

			if (cases) {
				FilterList.push_back(StuList[i]);
			}
			cases = true;
		}
		if (FilterList.empty()) {
			return false;
		}
		else {
			delay("Filter done\n");
			printResult(FilterList);
			FilterList.clear();
			return true;
		}
	}
}

bool Range_Filter() {
	string inputFrom, inputTo, idFrom, idTo;
	double cgpaFrom, cgpaTo;
	int creditFrom, creditTo, yearFrom, yearTo;
	bool checkId=false,  checkCredit = false,  checkCGPA = false,  checkYear = false;
	cout << "Input '-1' if you do not want to filter that particular criteria, it will skip it.\n\n";
	cout << "Input '-' if you don't want to set limit\n";
	cout << "ID From\n";
	getline(cin, inputFrom);
	if (inputFrom != "-1") {
		cout << "ID To\n";
		getline(cin, inputTo);
		if (inputTo != "-1") {
			if (inputFrom == "-") {
				inputFrom = "";
			}
			else {
				idFrom = inputFrom;
			}
			if (inputTo == "-") {
				inputTo = "9999999";
			}
			else {
				idTo = inputTo;
			}
			checkId = true;
		}
	}
	
	cout << "Total credit hour From\n";
	getline(cin, inputFrom);
	if (inputFrom != "-1") {
		cout << "Total credit hour To\n";
		getline(cin, inputTo);
		if (inputTo != "-1") {
			creditFrom = (inputFrom == "-") ? INT_MIN : stoi(inputFrom);
			creditTo = (inputTo == "-") ? INT_MAX : stoi(inputTo);
			checkCredit = true;
		}
	}
	
	cout << "Total CGPA From\n";
	getline(cin, inputFrom);
	if (inputFrom != "-1") {
		cout << "Total CGPA To\n";
		getline(cin, inputTo);
		if (inputTo != "-1") {
			cgpaFrom = (inputFrom == "-") ? -DBL_MAX : stod(inputFrom);
			cgpaTo = (inputTo == "-") ? DBL_MAX : stod(inputTo);
			checkCGPA = true;
		}
	}
	
	cout << "Exam Year From\n";
	getline(cin, inputFrom);
	if (inputFrom != "-1") {
		cout << "Exam Year To\n";
		getline(cin, inputTo);
		if (inputTo != "-1") {
			yearFrom = (inputFrom == "-") ? INT_MIN : stoi(inputFrom);
			yearTo = (inputTo == "-") ? INT_MAX : stoi(inputTo);
			if (yearFrom > yearTo) {
				cout << "logic error, year search skipped\n";
				checkYear = false;
			}
			checkYear = true;
		}
	}
	
	if (!checkId && !checkYear && !checkCredit && !checkCGPA) {
		return false;
	}
	
	for (Student student : StuList) {
		bool match = true;
		if (checkId && (student.id<idFrom || student.id>idTo)) {
			match = false;
		}
		if (checkCredit && (student.totalCreditsEarned<creditFrom || student.totalCreditsEarned>creditTo)) {
			match = false;
		}
		if (checkCGPA && (student.current_cgpa<cgpaFrom || student.current_cgpa>cgpaTo)) {
			match = false;
		}
		if (checkYear && student.exam_cnt > 0) {
			int minYear = student.exam[0].year;
			int maxYear = 0;
			for (int i = 0; i < student.exam_cnt; i++) {
				minYear = min(minYear, student.exam[i].year);
				maxYear = max(maxYear, student.exam[i].year);
			}
			if (minYear<yearFrom || maxYear>yearTo) {
				match = false;
			}
		}

		
		if (match) {
			FilterList.push_back(student);
		}
	}
	if (FilterList.empty()) {
		return false;
	}
	else {
		delay("Filter done\n");
		printResult(FilterList);
		FilterList.clear();
		return true;
	}
}

bool Search() {
	int choice = 0;
	char dumChoice[10];

	//switch
	int decimalPlaces, year, trimester, minCredit, maxCredit, subjectCredit;
	string input, subjectName;
	char input_code[10];
	size_t pos;
	double cgpa, lower, upper;
	bool yearCheck, yearMatch, trimesterCheck, trimesterMatch, subjectMatch;

	cout << "Please choose following criteria to search\n";
	cout << "1. Name\n2. ID\n3. course\n4. Phone\n5. CGPA\n6. Total Credit Hours\n7. Exam year\n8. Exam trimester\n9. Subject code\n 10. Subject name\n 11. Subject credit hours\n\n";
	cin.getline(dumChoice, 10);
	choice = input_valid(dumChoice);
	while (choice < 1 || choice>11) {
		cout << "invalid. try again\n";
		cin.getline(dumChoice, 10);
		choice = input_valid(dumChoice);
	}
	switch (choice) {
	case 1:
		cout << "Enter Name to search. Enter -1 to back to menu\n";
		getline(cin, input);
		if (input == "-1") {
			Search();
		}
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		for (Student student : StuList) {
			transform(student.name.begin(), student.name.end(), student.name.begin(), ::tolower);
			if (student.name.find(input) != string::npos) {
				FilterList.push_back(student);
			}
		}
		break;
	case 2:
		cout << "Enter ID to search. Enter -1 to back to menu\n";
		getline(cin, input);
		if (input == "-1") {
			Search();
		}
		for (Student student : StuList) {
			if (student.id==input) {
				FilterList.push_back(student);
				break;
			}
		}
		break;
	case 3:
		cout << "Enter Course to search. Enter -1 to back to menu\n";
		getline(cin, input);
		if (input == "-1") {
			Search();
		}
		for (Student student : StuList) {
			if (student.course == input) {
				FilterList.push_back(student);
			}
		}
		break;
	case 4:
		cout << "Enter Phone to search. Enter -1 to back to menu\n";
		getline(cin, input);
		if (input == "-1") {
			Search();
		}
		break;
		for (Student student : StuList) {
			if (student.phone == input) {
				FilterList.push_back(student);
			}
		}
	case 5:
		cout << "Enter CGPA to search. Enter -1 to back to menu\n";
		getline(cin, input);
		if (input == "-1") {
			Search();
		}
		cgpa = stod(input);
		pos = input.find('.');
		decimalPlaces = (pos == string::npos) ? 0 : (input.size() - pos - 1);
		lower = cgpa;
		upper = cgpa + pow(10, -decimalPlaces);
		for (Student student : StuList) {
			if (student.current_cgpa == lower &&  student.current_cgpa < upper) {
				FilterList.push_back(student);
			}
		}
		break;
	case 6:
		do {
			cout << "Enter MINIMUM total credit hours to search. Enter -1 to back to menu\n";
			getline(cin, input);
			if (input == "-1") {
				Search();
			}
			minCredit = input_valid_string(input);
			cout << "Enter MAXIMUM total credit hours to search. Enter -1 to back to menu\n";
			getline(cin, input);
			if (input == "-1") {
				Search();
			}
			maxCredit = input_valid_string(input);

			if (maxCredit < minCredit) {
				cout << "logic error. try again\n";
			}

		} while (maxCredit < minCredit);

		for (Student student : StuList) {
			if (student.totalCreditsEarned >= minCredit && student.totalCreditsEarned <= maxCredit) {
				FilterList.push_back(student);
			}
		}
		break;
	case 7:
		cout << "Enter exam year to search. Enter -1 to back to menu\n";
		getline(cin, input);
		if (input == "-1") {
			Search();
		}
		do {
			yearCheck = true;
			getline(cin, input);
			if (input.size() != 4) {
				cout << "This is not a year. Please try again.\n";
				yearCheck = false;
			}
			else {
				year = input_valid_string(input);
				for (Student student : StuList) {
					yearMatch = false;
					for (int i = 0; i < student.exam_cnt; i++) {
						if (year == student.exam[i].year) {
							yearMatch = true;
						}
					}
					if (yearMatch) {
						FilterList.push_back(student);
					}
				}
			}
		} while (!yearCheck);
		break;

	case 8:
		cout << "Enter Exam trimester to search. Enter -1 to back to menu\n";
		getline(cin, input);
		if (input == "-1") {
			Search();
		}
		do {
			trimesterCheck = true;
			getline(cin, input);
			trimester = input_valid_string(input);
			if (trimester != 1 && trimester != 5 && trimester != 10) {
				trimesterCheck = false;
				cout << "Trimester incorrect. Try again.\n";
			}

		} while (!trimesterCheck);

		for (Student student : StuList) {
			trimesterMatch = false;
			for (int i = 0; i < student.exam_cnt; i++) {
				if (year == student.exam[i].year &&
					trimester== student.exam[i].trimester) {
					trimesterMatch = true;
				}
			}
			if (trimesterMatch) {
				FilterList.push_back(student);
			}
		}
		break;
	case 9:
		cout << "Enter subject code to search. Enter -1 to back to menu\n";
		cin.getline(input_code,10);
		if (strcmp(input_code, "-1")==0) {
			Search();
		}
		for (Student student : StuList) {
			for (int i = 0; i < student.exam_cnt; i++) {
				subjectMatch = false;
				for (int j = 0; j < student.exam[i].numOfSubjects; j++) {
					if (strcmp(student.exam[i].sub[j].subject_code, input_code) == 0) {
						subjectMatch = true;
					}
				}
			}
			if (subjectMatch) {
				FilterList.push_back(student);
			}
		}
		break;
	case 10:
		cout << "Enter subject Name to search. Enter -1 to back to menu\n";
		getline(cin, input);
		if (input == "-1") {
			Search();
		}
		
		for (Student student : StuList) {
			for (int i = 0; i < student.exam_cnt; i++) {
				subjectMatch = false;
				for (int j = 0; j < student.exam[i].numOfSubjects; j++) {

					subjectName=student.exam[i].sub[j].subject_name;

					if (subjectName.find(input)!=string::npos ) {
						subjectMatch = true;
					}
				}
			}
			if (subjectMatch) {
				FilterList.push_back(student);
			}
		}
		break;
	case 11:
		cout << "Enter subject credit hours to search. Enter -1 to back to menu\n";
		getline(cin, input);
		if (input == "-1") {
			Search();
		}
		subjectCredit = input_valid_string(input);

		for (Student student : StuList) {
			for (int i = 0; i < student.exam_cnt; i++) {
				subjectMatch = false;
				for (int j = 0; j < student.exam[i].numOfSubjects; j++) {
					if (student.exam[i].sub[j].credit_hours==subjectCredit) {
						subjectMatch = true;
					}
				}
			}
			if (subjectMatch) {
				FilterList.push_back(student);
			}
		}
		break;
	}

	if (FilterList.empty()) {
		return false;
	}
	else {
		delay("Search done\n");
		printResult(FilterList);
		FilterList.clear();
		return true;
	}

}

bool multiSearch() {
	//switch
	int decimalPlaces, year=-1, trimester=-1,trimesterYear=-1, minCredit=-1, maxCredit=-1, subjectCredit=-1;
	string input,name, id, course, phone, subjectName, subjectName1;
	char input_code[10];
	size_t pos;
	double cgpa=-1, lower, upper;
	bool multiSearchCheck=false, yearCheck, trimesterCheck, subjectMatch;

	cout << "Please choose one or more following criteria to search by leaving a space\n";
	cout << "1. Name\n2. ID\n3. course\n4. Phone\n5. CGPA\n6. Total Credit Hours\n7. Exam year\n8. Exam trimester\n9. Subject code\n10. Subject name\n11. Subject credit hours\n\n";
	getline(cin, input);
	
	vector<int> choices = handleChoices(input, 11);

	for (int choice : choices) {
		switch (choice) {
		case 1:
			cout << "Enter Name to search. Enter -1 to back to menu\n";
			getline(cin, name);
			if (input == "-1") {
				multiSearch();
			}
			break;
		case 2:
			cout << "Enter ID to search. Enter -1 to back to menu\n";
			getline(cin, id);
			if (input == "-1") {
				multiSearch();
			}
			break;
		case 3:
			cout << "Enter Course to search. Enter -1 to back to menu\n";
			getline(cin, course);
			if (input == "-1") {
				multiSearch();
			}
			break;
		case 4:
			cout << "Enter Phone to search. Enter -1 to back to menu\n";
			getline(cin, phone);
			if (input == "-1") {
				multiSearch();
			}
			break;
		case 5:
			cout << "Enter CGPA to search. Enter -1 to back to menu\n";
			getline(cin, input);
			if (input == "-1") {
				multiSearch();
			}
			cgpa = stod(input);
			pos = input.find('.');
			decimalPlaces = (pos == string::npos) ? 0 : (input.size() - pos - 1);
			lower = cgpa;
			upper = cgpa + pow(10, -decimalPlaces);

			break;
		case 6:
			do {
				cout << "Enter MINIMUM total credit hours to search. Enter -1 to back to menu\n";
				getline(cin, input);
				if (input == "-1") {
					multiSearch();
				}
				minCredit = input_valid_string(input);
				cout << "Enter MAXIMUM total credit hours to search. Enter -1 to back to menu\n";
				getline(cin, input);
				if (input == "-1") {
					multiSearch();
				}
				maxCredit = input_valid_string(input);

				if (maxCredit < minCredit) {
					cout << "logic error. try again\n";
				}

			} while (maxCredit < minCredit);

			break;
		case 7:
			cout << "Enter exam year to search. Enter -1 to back to menu\n";
			getline(cin, input);
			if (input == "-1") {
				multiSearch();
			}
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
			multiSearchCheck = true;
			break;

		case 8:
			cout << "Enter exam year to search. Enter -1 to back to menu\n";
			getline(cin, input);
			if (input == "-1") {
				multiSearch();
			}
			do {
				yearCheck = true;
				getline(cin, input);
				if (input.size() != 4) {
					cout << "This is not a year. Please try again.\n";
					yearCheck = false;
				}
				else {
					trimesterYear = input_valid_string(input);
				}
			} while (!yearCheck);

			cout << "Enter Exam trimester to search. Enter -1 to back to menu\n";
			getline(cin, input);
			if (input == "-1") {
				Search();
			}
			do {
				trimesterCheck = true;
				getline(cin, input);
				trimester = input_valid_string(input);
				if (trimester != 1 && trimester != 5 && trimester != 10) {
					trimesterCheck = false;
					cout << "Trimester incorrect. Try again.\n";
				}

			} while (!trimesterCheck);

			multiSearchCheck = true;
			break;
		case 9:
			cout << "Enter subject code to search. Enter -1 to back to menu\n";
			cin.getline(input_code, 10);
			if (strcmp(input_code, "-1") == 0) {
				multiSearch();
			}
			multiSearchCheck = true;

			break;
		case 10:
			cout << "Enter subject Name to search. Enter -1 to back to menu\n";
			getline(cin, subjectName1);
			if (input == "-1") {
				multiSearch();
			}
			multiSearchCheck = true;
			break;
		case 11:
			cout << "Enter subject credit hours to search. Enter -1 to back to menu\n";
			getline(cin, input);
			if (input == "-1") {
				multiSearch();
			}
			subjectCredit = input_valid_string(input);
			multiSearchCheck = true;
			break;
		}
	}
	for (Student student : StuList) {
		bool match = true;
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		string name1 = student.name;
		transform(name1.begin(), name1.end(), name1.begin(), ::tolower);
		if (!name.empty() && name1.find(name) == string::npos) {
			match = false;
		}//case1
		if (!id.empty() && student.id!=id) {
			match = false;
		}//case2
		if (!course.empty() && student.course!=course) {
			match = false;
		}//case3
		if (!phone.empty() && student.phone != phone) {
			match = false;
		}//case4
		if (cgpa>=0 && (student.current_cgpa < lower || student.current_cgpa >= upper)) {
			match = false;
		}//case5
		if ((minCredit >= 0 || maxCredit >= 0) && (student.totalCreditsEarned < minCredit || student.totalCreditsEarned > maxCredit)) {
			match = false;
		}//case6

		subjectMatch = false;
		for (int i = 0; i < student.exam_cnt; i++) {
			if (year>=0 &&(year == student.exam[i].year)) {
				subjectMatch = true;
			}//case7
			if (trimesterYear >= 0 && trimester >= 0 &&
				(trimesterYear == student.exam[i].year && trimester == student.exam[i].trimester)) {
				subjectMatch = true;
			}//case8

			for (int j = 0; j < student.exam[i].numOfSubjects; j++) {
				if (input_code[0]!='\0'&& (strcmp(student.exam[i].sub[j].subject_code, input_code) == 0)) {
					subjectMatch = true;
				}//case9

				subjectName = student.exam[i].sub[j].subject_name;
				if (!subjectName1.empty() && (subjectName.find(subjectName1) != string::npos)) {
					subjectMatch = true;
				}//case10

				if (subjectCredit>=0 && (student.exam[i].sub[j].credit_hours == subjectCredit)) {
					subjectMatch = true;
				}
			}
		
			if (multiSearchCheck && !subjectMatch) {
				match = false;
			}
		}
		if (match) {
			FilterList.push_back(student);
		}
	}

	if (FilterList.empty()) {
		return false;
	}
	else {
		delay("Search done\n");
		printResult(FilterList);
		FilterList.clear();
		return true;
	}
}

