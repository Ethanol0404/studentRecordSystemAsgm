#include	<iostream>
#include    <iomanip>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
int menu();

//menu 
bool checkChoice=true;

int main() {
	int choice = 0;

	//1 read data to BST
	char f_name[] = "student.txt";
	BST t1;
	bool restrict1=false;

	//3 display student
	int order = 0, source = 0;

	//4 clone subtree
	BST t2;
	type student;

	do {
		system("cls");
		do {
			choice = menu();
			checkChoice = true;

			switch (choice)
			{
			case 1:
				if (restrict1) {
					cout << "This function is used already, please exit the system before using it again.\n";
				}
				else {
					if (!readFile(f_name, &t1)) {
						cout << "Failed to open file.\n\n";
					}
					else {
						restrict1 = true;
					}
				}
				break;

			case 2:
				if (!t1.deepestNodes()) {
					cout << "The tree is empty. Please insert student record first.\n\n";
				};
				break;

			case 3:
				cout << "Please choose the type of order you wish to print:\n1. Ascending\n2. Descending\n\nOrder: ";
				cin >> order;
				cout << "\nPlease choose the source you wish to print:\n1. Print on screen\n2. Print on file\n\nSource: ";
				cin >> source;

				t1.display(order, source);
				break;

			case 4:
				cout << "Please key in the student ID that you wish to clone as a subtree.\n\n";
				for (int i = 0; i < 71; i++) {
					cout << "=";
				}
				cout << "\n\nThe t1 tree\n\n";
				for (int i = 0; i < 71; i++) {
					cout << "=";
				}
				t1.preOrderPrint();
				for (int i = 0; i < 71; i++) {
					cout << "=";
				}
				cout << "\n\nStudent ID that wish to clone: ";
				cin >> student.id;
				cout << "\n";
				t2.CloneSubtree(t1, student);
				
				break;

			case 5:
				if (!t1.printLevelNodes()) {
					cout << "The tree is empty. Please insert student record first.\n\n";
				}
				else {
					cout << endl << endl;
				}
				break;

			case 6:
				if (!t1.printPath()) {
					cout << "The tree is empty. Please insert student record first.\n\n";
				}
				break;

			case 7:
				cout << "Thank you for using this service.\n\n";
				break;

			default:
				checkChoice = false;
				system("cls");
				break;
			}
		} while (checkChoice == false);

		system("pause");
	} while (choice != 7);
	return 0;
}

int menu() {
	int choice = 0;
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
	cout << "\n1. Read data to BST\n2. Print deepest nodes\n3. Display student\n";
	cout << "4. Clone Subtree\n5. Print Level Nodes\n6. Print Path\n7. Exit\n";
	for (int i = 0; i < 71; i++) {
		cout << "_";
	}
	cout << "\nPlease choose a task to be done (1-6)\n";
	cout << "*ps: It is recommended to Read data to BST (1) before conducting any other functions.\n\n";

	if (checkChoice == false) {
		cout << "Please enter valid number (1-7): \n";
	}

	cout << "Choice: ";
	cin >> choice;

	return choice;
}

bool readFile(const char* name, BST* tree) {
	Student stu;
	string s;
	ifstream in(name);
	if (in.fail()) {
		return false;
	}
	else {
		while (!in.eof()) {
			in >> s >> s >> s >> stu.id; //read student id
			in >> s >> s;
			in.getline(stu.name, 30); //read student name

			in >> s >> s;
			in.getline(stu.address, 100); //read student address

			in >> s >> s >> stu.DOB; //read student DOB

			in >> s >> s >> s >> stu.phone_no; //read student phone number

			in >> s >> s >> stu.course; //read student course

			in >> s >> s >> stu.cgpa; //read student cgpa

			tree->insert(stu);

		}
		in.close();
		cout <<"\n"<< tree->count << " student records successfully read.\n\n";
		return true;
	}


}