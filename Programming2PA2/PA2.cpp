#include"pa2.h"
#include <stdio.h>

using namespace std;

static int* released = new int;


void userMenu(int* userNum) {

	while (!((*userNum == 1) || (*userNum == 2) || (*userNum == 3) || (*userNum == 4) || (*userNum == 5))) {
		cout << "1. Add program " << endl;
		cout << "2. Kill program " << endl;
		cout << "3. Fragmentation" << endl;
		cout << "4. Print memory " << endl;
		cout << "5. Exit" << endl;
		cout << endl;
		cout << "choice - ";
		cin >> *userNum;
		if (!((*userNum == 1) || (*userNum == 2) || (*userNum == 3) || (*userNum == 4) || (*userNum == 5))) {

			cout << endl;
			cout << "Be serious." << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			*userNum = 0;
			cout << endl;
		}
	}
}



int main(int argc, char**argv) {
	int userInput;
	int* userNum = &userInput;
	int numPages;
	string * strategy = new string;
	list linkedlist;
	for (int i = 0; i < 32; i++) {
		linkedlist.append1("Free");
	}

	if ((strcmp(argv[1], "worst") == 0) || ((strcmp(argv[1], "Worst") == 0)) || (strcmp(argv[1], "WORST") == 0)) {
		cout << "Using worst fit algorithm." << endl;
		*strategy = "a";
	}
	else if ((strcmp(argv[1], "best") == 0) || (strcmp(argv[1], "Best") == 0) || (strcmp(argv[1], "BEST") == 0)) {
		cout << "Using best fit algorithm." << endl;
	}
	else {
		cout << "Invalid or missing arguments." << endl;
		return 0;
	}


	do {
		userMenu(userNum);
		switch (*userNum) {
		case 1: {//addition

			string nameProgram = "666";
			int programSize = 666;

			cout << "Program name - ";
			cin >> nameProgram;

			if (linkedlist.checkexistence(nameProgram)) {//check if there is already a file with the same name.
				cout << endl;
				cout << "Invalid input." << endl;
				cout << endl;
				*userNum = 0;
				break;
			}

			cout << "Program size (KB) - ";
			cin >> programSize;
			cout << endl;

			if (programSize % 4 != 0) {//determine how many pages to be used
				numPages = programSize / 4 + 1;
			}
			else {
				numPages = programSize / 4;
			}
			if ((numPages > 32) || (!linkedlist.hasSpace(numPages))) {//check if there is space
				cout << "Error, not enough memory for Program " << nameProgram << " or invalid input." << endl;
				cout << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				programSize = 0;
				*userNum = 0;
				break;
			}

			if (numPages != 0) {
				int position;
				if (*strategy == "a")
					position = linkedlist.findholesforworst(numPages);
				else
					position = linkedlist.findholesforbest(numPages);
				cout << "Program " << nameProgram << " added successfully. " << numPages << " page(s) used." << endl;
				for (int i = 0; i < numPages; i++) {
					linkedlist.insert(position + i, nameProgram);

				}
			}
			else {
				cout << "No pages added" << endl;
			}

			cout << endl;
			*userNum = 0;
			break;

		}case 2: {//deletion
			string nameProgram = "666";
			if (linkedlist.checkallfree()) {
				cout << endl;
				cout << "Linkedlist totally empty." << endl;
				cout << endl;
				*userNum = 0;
				break;
			}
			cout << "Program name - ";
			cin >> nameProgram;
			*released = 0;
			if ((!linkedlist.checkexistence(nameProgram)) || (nameProgram == "Free")) {
				cout << "Invalid input." << endl;
				cout << endl;
				*userNum = 0;
				break;
			}
			linkedlist.searchanddestroy(released, nameProgram);
			cout << endl;
			cout << "Program " << nameProgram << " successfully killed, " << *released << " page(s) reclaimed." << endl;
			cout << endl;
			*userNum = 0;
			break;
		}case 3: {//Fragmentation
			cout << endl;
			cout << "There are " << linkedlist.numFrags() << " fragment(s)." << endl;
			cout << endl;
			*userNum = 0;
			break;
		}case 4: {//Print
			cout << endl;
			linkedlist.print();
			cout << endl;
			*userNum = 0;
			break;
		}userMenu(userNum);
		}
	} while (*userNum != 5);
	return 0;
}