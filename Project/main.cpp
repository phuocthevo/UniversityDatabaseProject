// Main function: Create two BST and Hash variables to insert into InputManger and process the program
// Written by The Vo
#include <iostream>
#include"University.h"
#include "InputManager.h"

using namespace std;
int main() {

	BinarySearchTree<University*> nameTree;
	BinarySearchTree<University*> codeTree;
	Hash UniversityTable;
	InputManager manager(&codeTree, &nameTree, &UniversityTable);
	while (manager.commandLoop());
	return 0;
}
