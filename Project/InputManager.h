
//This is the Input Menu that reads the file, shows the display Menu and links all the Classes
//The basic options are: Open File, Print Data, Search Data depends on keys, Remove Data, Save File
// Written by The Vo, (Dan Nguyen)

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#define COMMAND_OPEN "O"
#define COMMAND_SAVE "S"
#define COMMAND_SEARCH "SU"
#define COMMAND_LIST "L"
#define COMMAND_INSERT "I"
#define COMMAND_DELETE "D"
#define COMMAND_ABOUT "A"
#define COMMAND_QUIT "Q"
#define PATH_RECOVERY "database.txt"

#include <iostream>
#include <fstream>
#include<iomanip>
#include <string>
#include "University.h"
#include "BinarySearchTree.h"
#include "Hasing.h"


void capitalizeString(string&);
void visitindented(University*&, int);
void visit(University*&);

class InputManager {
	BinarySearchTree<University*>* CodeTree = nullptr;
	BinarySearchTree<University*>* NameTree = nullptr;
	Hash* UniversityTable = nullptr;
protected:
	void insertUniversity();

	void deleteUniversity();
	
	bool readFile(string&);
	
	void saveToFile(const string&);
	
	void ListMenu();
	
	void SearchMenu();
	
	void searchNameTree();
	
	void searchSymbolTree();
	
	void displayHashStatistics();
	
	void displayMenu();
	
public:
	InputManager(BinarySearchTree<University*>*, BinarySearchTree<University*>*, Hash* );
	bool commandLoop();
	
};

InputManager::InputManager(BinarySearchTree<University*>* codeTree, BinarySearchTree<University*>* nameTree, Hash* UniversityTable) {
	this->CodeTree = codeTree;
	this->NameTree = nameTree;
	this->UniversityTable = UniversityTable;
}


// commandLoop: allow the user to interact with the program by choosing options on the Main Menu
bool InputManager:: commandLoop() {
		
		this->displayMenu();
		string command;
		command.clear();
		getline(cin, command,'\n');
		capitalizeString(command);

		if (command == COMMAND_OPEN) {
			cout << "Please enter filepath to open:" << endl;
			getline(cin, command);
			cout << "Opening..." << endl;
			this->readFile(command);
			cout << "Done." << endl;
		}
		else if (command == COMMAND_LIST)
			ListMenu();
		else if (command == COMMAND_SEARCH)
			SearchMenu();

		else if (command == COMMAND_SAVE) {
			cout << "Please enter filepath to save:" << endl;
			getline(cin, command);
			cout << "Saving..." << endl;
			this->saveToFile(command);
			cout << "Done." << endl;
		}

		else if (command == COMMAND_INSERT) {
			this->insertUniversity();
			cout << "=====\tPress ENTER to continue...\t=====" << endl;
			getline(cin, command);
		}
		else if (command == COMMAND_DELETE) {
			this->deleteUniversity();
			cout << "=====\tPress ENTER to continue...\t=====" << endl;
			getline(cin, command);
		}

		else if (command == COMMAND_ABOUT) {
			this->displayHashStatistics();
			cout << endl;
			cout << "CIS-22C Team 6 Group Project" << endl;
			cout << "Team Project: University Database.\n";
			cout << "\nTeam members:\n";
			cout << "\tThe Vo\n";
			cout << "\tBa Lam Nguyen\n";
			cout << "\tHuy Vo\n";
			cout << "\tDan Nguyen\n";
			cout << "=====\tPress ENTER to continue...\t=====" << endl;
			getline(cin, command);
		}
		else if (command == COMMAND_QUIT) {
			cout << "Quitting..." << endl;
			this->saveToFile(PATH_RECOVERY);
			cout << "Done." << endl;
			return false;
		}
		else {
			cout << "\nError unrecognized command!" << endl;
		}
		return true;
		
	}
// insertUniversity: check data and insert a valid data to tree and hash table

void InputManager:: insertUniversity() {
	University* newUniversity = new University();
	string input, check;
	
	// Check and Insert University Code:
	bool valid = false;
	while (!valid)
	{
		cout << "Enter the University Code: " << endl;
		getline(cin, input);
		University* found = nullptr;
		capitalizeString(input);
		newUniversity->setCode(input);
		if (!this->UniversityTable->Search(input)) // check dublicate
			valid = true;
		else
			cout << " Error: University with that code already exists!\n";
	}
	
	// Check and Insert University Name
	valid = false;
	while (!valid)
	{
		cout << "Enter the University Name: " << endl;
		getline(cin, input);
		University* found = nullptr;
		newUniversity->setName(input);
		if ((this->NameTree->getEntry(newUniversity, found, key::SECONDKEY, visit)) == false)
			valid = true;
		else
		{
			cout << " University with that code already exists!\n"
				<< " Do you want to re-enter? (Y/N)\n";
			check = "N";
			getline(cin, check);
			if (check == "N" || check == "n")
				valid = true;
		}

	}
	//Insert Location and Ranking
	cout << " Enter University Location: \n";
	getline(cin, input);
	newUniversity->setLocation(input);
	cout << " Enter University Ranking: \n";
	getline(cin, input);
	newUniversity->setRanking(input);
	
	//Check and Insert Tuition 
	valid = false;
	cout << " Enter University Tuition: \n";
	while (!valid) {
		getline(cin, input);
		try {
			newUniversity->setTuition(stof(input)); //check if input is a number
			valid = true;
		}
		catch (invalid_argument e) {
			cout << "That is not a number. Please try again:";
		}
	}

	cout << " Enter University Admission: \n";
	getline(cin, input);
	newUniversity->setAdmission(input);

	// Input data to tree and hash table
	NameTree->insert(newUniversity, key::SECONDKEY); // insert to BST Name
	CodeTree->insert(newUniversity, key::FIRSTKEY); // insert to BST Code
	UniversityTable->Insert(*newUniversity); // insert to Hash Table
}
// delete University 
void InputManager::deleteUniversity() {
	string code;
	cout << "Enter code of University to be removed: \n";
	getline(cin, code);
	capitalizeString(code);
	University* toRemove = this->UniversityTable->Search(code);
	University* nameRemove = nullptr;
	toRemove = new University(code);
	CodeTree->getEntry(toRemove, nameRemove, key::FIRSTKEY, visit);
	if (toRemove != NULL&& nameRemove != NULL &&NameTree->remove(nameRemove, key::SECONDKEY) && CodeTree->remove(toRemove, key::FIRSTKEY) && UniversityTable->Delete(code)) // Remove data from BST and Hash Table
		cout << " \nDetele Successful!\n";
	else
		cout << " \nUnavailable data. Can not Delete!\n";
}
// getline of input file and put into an object , then insert to the BST and Hash Table
bool InputManager::readFile(string& filePath) {
	ifstream inputFile(filePath);
	if (!inputFile.is_open()) {
		cout << "Error opening file!" << endl;
		return false;
	}
	string temp;
	int number;
	while (getline(inputFile, temp, ';')) { // get the Data 
		University* newUniversity = new University();
		
		newUniversity->setCode(temp);
		getline(inputFile, temp, ';');
		newUniversity->setName(temp);
		getline(inputFile, temp, ';');
		newUniversity->setLocation(temp);
		getline(inputFile, temp, ';');
		newUniversity->setTuition(stod(temp));
		getline(inputFile, temp, ';');
		newUniversity->setRanking(temp);
		getline(inputFile, temp, '\n');
		newUniversity->setAdmission(temp);
		
		this->UniversityTable->Insert(*newUniversity); // insert ti the Hash Table
		this->CodeTree->insert(newUniversity, key::FIRSTKEY); //insert to BST Code
		this->NameTree->insert(newUniversity, key::SECONDKEY); // insert to BST Name
	}
	inputFile.close();
	return true;
}
// save all changes of file into a new file in same location of program
void InputManager:: saveToFile(const string& filePath) {
	ofstream saveFile(filePath);
	this->CodeTree->breadthFirstTraverse([&saveFile](University* & node) { //output the file
		saveFile << node->getCode() << ";" << node->getName() << ";" << node->getLocation() << ";"<< node->getTuition() << ";" << node->getRanking()<< ";"
			 << node->getAdmission()<<  endl;
	});
	saveFile.close();
}
// DIsplay the Menu options for the user
void InputManager::ListMenu()
{
	string input;
	University* node;
	do {
		cout << "-----------------------------------------------------------------------------------------------" << endl;
		cout << "                                                OPTION" << endl;
		cout << "-----------------------------------------------------------------------------------------------" << endl;

		cout << "1. List Name Tree\n" << "2. List Name Tree Indented\n" << "3. List Code Tree\n"
			<< "4. List Code Tree Indented\n" << "5. List Data Unsorted\n" << "6. Exit\n" << "Your Choice: ";
		cin >> input;
		if (input == "1" || input == "2" || input == "3" || input == "4" || input == "5")
		{
			if (input == "1" || input == "3" || input == "5")
			{
				cout << setfill('-') << setw(6) << "Code" << setw(30) << "Name" << setw(30) << "Location"
					<< setw(30) << "Admission" << setw(20) << "Ranking" << setw(15) << "Tuition" << endl;
				for (int i = 0; i < 100; i++) { cout << '-'; }
				cout << endl << setfill(' ');
			}
			if (input == "1")
				this->NameTree->inOrder(visit);
			else if (input == "2")
				this->NameTree->printIndented(visitindented); // Print Indented List
			else if (input == "3")
				this->CodeTree->inOrder(visit); // Print all data in order
			else if (input == "4")
				this->CodeTree->printIndented(visitindented);// Print Indented List
			else if (input == "5")
				this->CodeTree->breadthFirstTraverse(visit); // Print all data
		}
		else if (input == "6")
			cout << " \nBack to main menu\n";
		else
			cout << "\nPlease enter either 1 to 5 or 6 to exit" << endl;
	} while (input != "6");
	cin.clear();
	cin.ignore();
}
// Search the Code-> Hash Table or the Name->BST  
void InputManager::SearchMenu()
{
	string input;
	do {
		cout << "1. Search by Name\n" << "2. Search by Code\n" << "3. Exit\n" << "=> Your Choice: ";
		cin >> input;
		if (input == "1" || input == "2")
		{
			if (input == "1")
				searchNameTree();
			else if (input == "2")
				searchSymbolTree();
		}
		else if (input == "3")
			cout << " \nBack to main menu\n";
		else
			cout << "\nPlease enter either of these option" << endl;
	} while (input != "3");
	cin.clear();
	cin.ignore();
}
// Search the Name by the BST 
void InputManager:: searchNameTree() {
	string toSearch;
	University* node = nullptr;
	cout << "Enter University name:" << endl;
	cin.ignore();
	getline(cin, toSearch);
	cout << "Searching..." << endl;
	University search;
	search.setName(toSearch); // Search Name BST
	if (this->NameTree->getEntry(&search, node, key::SECONDKEY, visit)) {
		cout << "\nDone." << endl;
	}
	else {
		cout << "\nDone. ERROR: University with name " << toSearch << " not found..." << endl;
	}
}
// Search the Cody by the Hash Table
void InputManager:: searchSymbolTree() {
	string toSearch;
	University* node = nullptr;
	cout << "Enter University code:" << endl;
	cin.ignore();
	getline(cin, toSearch);
	cout << "Searching..." << endl;
	node = this->UniversityTable->Search(toSearch);//Search Code Hash
	if (node != NULL) {
		visit(node);
		cout << "\nDone." << endl;
	}
	else {
		cout << "\nDone. ERROR: University with symbol " << toSearch << " not found..." << endl;
	}
}
//Display the Collision, Size and LoadFactor
void InputManager::displayHashStatistics() {
	cout << "***Statistics***" << endl
		<< "Collisions: " << this->UniversityTable->GetCollision() << endl
		<< "Default Bucket Size: " << this->UniversityTable->getSize() << endl
		<< "Load Factor: " << this->UniversityTable->GetLoadFactor() << endl;
}
//Display the Menu text
void InputManager::displayMenu() {
	
	for (int i = 0; i < 150; i++)cout << "-";
	cout << endl << "\t\t                                --MAIN MENU-- \n";
	for (int i = 0; i < 150; i++)cout << "-";
	cout << endl;
	cout <<right << "O- Opensaved database file." << setw(56) << " S- Save current database.\n";
	cout <<right << "L- List database menu." << setw(60) << "SU- Search database menu\n";
	cout <<right << "I- Insert new item into database" << setw(54) << "D- Remove item from database\n" << "A-Author& Statistic\n" << "Q-Quit\n";
	cout <<right << "\n=> Enter command: ";
}
// Capitalize option input
void capitalizeString(string& toCapitalize) {
	for (int i = 0; i < toCapitalize.length(); i++) {
		toCapitalize[i] = (char)toupper(toCapitalize[i]);
	}
}
// Display the object of a University in indented 
void visitindented(University*& node, int level)
{
	cout<< right << setw(5 * level) << "Level:" << level<<" Name: " << node->getName() << "(" << node->getCode() << ")\n";
	cout<< right << setw(5 * level) << "->Location: " << node->getLocation() << endl;
	cout<< right << setw(5 * level) << "->Admission: " << node->getAdmission() << "%\n";
	cout<< right << setw(5 * level) << "->Ranking: " << node->getRanking() << "\n";
	cout<< right << setw(5 * level) << "->Tuition: " << node->getTuition() << endl;
}

// Display the University object
void visit(University*& node)
{
	cout << left << setw(8) << node->getCode() << setw(50) << node->getName() << setw(30) << node->getLocation()
		<< setw(20) << node->getAdmission() << setw(20) << node->getRanking() << setw(15) << node->getTuition() << endl;
}
#endif INPUTMANAGER_H
