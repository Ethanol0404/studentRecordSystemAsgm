#include	<algorithm>
#include	"Student.h"
#include	"Display.h"
#include	"InputValid.h"
#include	"Insert.h"
#include	"Filter.h"
#include	"Modify.h"
#include	"View.h"

using namespace std;
char Redirect();
vector<Student>StuList;
int main() {
	// Menu system
	char reply;
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

		reply=Redirect();

	} while (tolower(reply) == 'y');
	//outputFile();
	fasterdelay("===================================================================================");
	delay("All student's informations are record successfully. Thank you for using our service");
	fasterdelay("===================================================================================");

	system("pause");
	return 0;
}

char Redirect() {
	cout << "Enter 1-4 that you wish to proceed: ";
	int choice = 0;
	char dumChoice[10],reply;
	bool checkRedirect = true, skipReply=false;
	do {
		cin.getline(dumChoice, 10);
		choice = input_valid(dumChoice);
		switch (choice) {
		case 1:
			skipReply=Insert(); //when user enter return
			break;
		case 2:
			skipReply = mainFilter();
			break;
		case 3:
			skipReply = Modify();
			break;
		case 4:
			skipReply = View();
			break;
		default:
			cout << "Please enter valid number \n";
			checkRedirect = false;
		}
	} while (!checkRedirect);

	if (skipReply) {
		return 'y';
	}
	else {
		cout << endl;
		cout << "Do you want to return to menu? (Press Y to return. Press any key to quit): ";
		cin >> reply;
		cin.ignore();
		cout << endl;
		return reply;
	}
}