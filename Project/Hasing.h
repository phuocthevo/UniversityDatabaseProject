//Hashing header file: use for hash table data structure
// Written by Ba Lam Nguyen
# ifndef HASING_H
# define HASING_H

# define BUCKER_SIZE 3

# include <string>
# include "LinkedList.h"

using namespace std;

class Hash
{
private:
	University*** Hashtable;
	LinkedList<University> OverflowTable;
	int SIZE=65;
	int loadfactor;
	int collision;

public:
	unsigned int Hasing(string);
	Hash();
	void Insert(University);
	University* Search(string);
	int getSize() { return SIZE; }
	double GetLoadFactor();
	int GetCollision();
	bool Delete(string);
	void ReHash();
	~Hash();
};


// constructor
Hash::Hash()
{
	
	loadfactor = 0;
	collision = 0;

	// Dynamically allocated for 2-D array for hash table
	Hashtable = new  University**[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		Hashtable[i] = new University*[BUCKER_SIZE + 1];

		for (int j = 0; j < BUCKER_SIZE + 1; j++)
			Hashtable[i][j] = NULL;
	}
}



// hash function convert every string into
// a unique number and return that number for
// other purpose
//**********************************************
unsigned int Hash::Hasing(string str)
{
	int primes[] = { 233, 389, 521, 163, 379, 167, 503, 83, 37, 13 };  // size is 10, large enough
	unsigned int sum = 0;

	for (int i = 0; i < str.length(); i++)
	{
		sum += primes[((int)str.at(i)) % 10] * primes[i % 10] * primes[i];
	}


	sum = sum % SIZE;

	return sum;
}

void Hash::Insert(University uni)
{
	int key = Hasing(uni.getCode());

	int count = 0;



	// go to the row key in the array, check to see which collumn 
	while (count < BUCKER_SIZE + 1 && Hashtable[key][count] != 0)
		count++;

	//update collision
	collision += count;

	// if there is still place in hash table, insert it at that place
	if (count <= BUCKER_SIZE)
	{
		if (count == 0) // if the Item is loaded into the table, update the number of item is loaded
		{
			loadfactor++;
		}

		Hashtable[key][count] = new University(uni);
	}
	else
		OverflowTable.insertNode(uni);



}

University* Hash::Search(string search_key)
{
	int key = Hasing(search_key);
	int count = 0;

	// We consider row with position key, search that place and all the bucket if we have 
	// the object has seach key or not

	// In one row, if there exist a element , it will be placed at the first of the row
	// In the case we delete the first element, next elements will be moved to the left to fullfil the space
	// We check the whole row, if there is no element, check ovweflow table

	while (Hashtable[key][count] != NULL && (Hashtable[key][count]->getCode() != search_key && count < BUCKER_SIZE + 1))
		count++;

	// if that element at [key][count]  is NULL or we out of the bucket
	// now search in the linkedList
	if (Hashtable[key][count] == NULL || count >BUCKER_SIZE + 1)
	{
		University temp;
		temp.getCode() = key;
		if (OverflowTable.search(temp) != NULL)
			return OverflowTable.search(temp);
		else
			return NULL;
	}
	else
	{
		return Hashtable[key][count];
	}


}

bool Hash::Delete(string search_key)
{
	bool success = false;
	int key = Hasing(search_key);
	int count = 0;


	// traverse on the row  "key", exit the loop if we reach target element 
	while (Hashtable[key][count]->getCode()!= search_key && count < BUCKER_SIZE + 1)
		count++;

	if (count < BUCKER_SIZE + 1)
	{
		delete Hashtable[key][count];
		Hashtable[key][count] = 0;
		success = true;
	}
	else
	{
		University temp;
		temp.getCode() = search_key;
		success = OverflowTable.Delete(temp);
	}

	return success;

}

void Hash::ReHash()
{
	University*** New_Table;

	// Dynamically allocated for 2-D array for hash table
	New_Table = new  University**[SIZE * 2];
	for (int i = 0; i < SIZE * 2; i++)
	{
		New_Table[i] = new University*[BUCKER_SIZE + 1];

		for (int j = 0; j < BUCKER_SIZE + 1; j++)
			New_Table[i][j] = 0;
	}

	// Move data from old table to new table

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < BUCKER_SIZE + 1; j++)
		{
			// assign the value in hash table to new table, after that Point that 
			// element of hash table to NuLL
			New_Table[i][j] = Hashtable[i][j];
			Hashtable[i][j] = 0;
		}
	}

	// Free the old Hash table , but not the Its node
	for (int i = 0; i < SIZE; i++)
	{
		delete[] Hashtable[i];
	}
	delete[] Hashtable;


	// Assign New table to Hash table, point the New Table to 0
	Hashtable = New_Table;

	New_Table = 0;
	SIZE *= 2;

}

//***************************************
// Get the load factor of the hash table
//***************************************
double Hash::GetLoadFactor()
{
	return (double)loadfactor / SIZE * 100;
}

int Hash::GetCollision()
{
	return collision;
}


//Destructor
Hash::~Hash()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < BUCKER_SIZE; j++)
		{
			if (Hashtable[i][j] != 0)
				delete Hashtable[i][j];
		}

		delete Hashtable[i];
	}
	delete Hashtable;
}





# endif 