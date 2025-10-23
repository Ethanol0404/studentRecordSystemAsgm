#include	"View.h"

bool View() {
	system("cls");
	cout << "View \n";
	cout << "=======================\n";
	cout << "1. Show All Student\n2. Print Statistic\n3. Potential First Class\n4. Save in file\n5. Return\n";
	int choice = 0, choice2=0;
	char dumChoice[10], reply, printChoice=' ';
	string course;
	bool checkRedirect = true;
	do {
		cin.getline(dumChoice, 10);
		choice = input_valid(dumChoice);
		switch (choice) {
		case 1:
			//cout << "Please select how do you want to display the results: On Screen (1) / In Text File (2): ";
			//do {//input validation
			//	cin.getline(dumChoice, 10);
			//	choice2 = input_valid(dumChoice);
			//	if (choice2 != 1 && choice2 != 2) {
			//		cout << "\nPlease input only 1 or 2.:";
			//	}
			//} while (choice2 != 1 && choice2 != 2);
			//PrintList(StuList, choice2);
			//cout << "**Please remember to copy data to a safe place to prevent loss of data.\n";
			PrintList(StuList, 1);
			break;
		case 2:
			printStatistic();
			break;
		case 3:
			cout << "Insert course: ";
			getline(cin, course);
			findPotentialFirstClass(course);
			break;
		case 4:
			PrintList(StuList, 2);
			break;
		case 5:
			return true;
			break;
		default:
			cout << "Please enter valid number \n";
			checkRedirect = false;
		}
	} while (!checkRedirect);

	return false;
}

bool printStatistic() {
	int totalStudent = 0, totalSemester = 0;
	double  totalSubject = 0, totalCredits = 0, totalCGPA = 0, AverageCGPA, AverageSubject, AverageCredit;
	Student student;
	const char* course[]{ "CS","IA","IB","CN","CT" };

	int courseCount[5]{};
	totalStudent = StuList.size();

	if (StuList.empty()) {
		cout << "List is empty. Please try inserting some info first.\n\n";
		return false;
	}

	for (Student student : StuList) {
		for (int i = 0; i < 5; i++) {
			if (student.course.compare(course[i]) == 0) { // compare course to make statistic
				courseCount[i]++;
				break;
			}
		}
		totalCGPA += student.current_cgpa;

		totalSemester += student.exam_cnt;
		totalCredits += student.totalCreditsEarned;
		for (int j = 0; j < student.exam_cnt; j++) {
			totalSubject += student.exam[j].numOfSubjects;
		}
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

bool findPotentialFirstClass(string course) {
	vector<Student> potentialList;
	bool check = false;
	for (int i = 1; i <= StuList.size(); i++) { //traverse list1
		int high_gpa_cnt = 0;
		bool minGPA = true;
		if (StuList[i].course.compare(course) == 0) {//compare course name
			if (StuList[i].exam_cnt > 2) { //Check if student has more than 2 exams

				for (int i = 0; i < StuList[i].exam_cnt; i++) {
					if (StuList[i].exam[i].calculateGPA()) {
						if (StuList[i].exam[i].gpa < 3.5) { //check if student has one GPA less than minimum
							minGPA = false;

						}
					}
				}
				if (minGPA) {
					for (int j = 0; j < StuList[i].exam_cnt; j++) {
						int total_cred = 0;
						for (int k = 0; k < StuList[i].exam[j].numOfSubjects; k++) { //Get total credit hours for that exam
							total_cred += StuList[i].exam[j].sub[k].credit_hours;
						}
						if (StuList[i].exam[j].gpa >= 3.75 && total_cred >= 12) { //record frequency of getting high GPA
							high_gpa_cnt++;
						}
					}
				}
				if (high_gpa_cnt >= 3) {
					potentialList.push_back(StuList[i]);
					check = true;
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
		char printChoice = ' ';
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
			PrintList(potentialList, 1);
			cout << "**Please remember to copy data to a safe place to prevent loss of data.\n";
		}
		potentialList.clear();
		return true;
	}

}




