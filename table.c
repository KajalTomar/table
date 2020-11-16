#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

// -----------------------------------------------------------------------------------------------
// CONSTANTS AND TYPES
// -----------------------------------------------------------------------------------------------

typedef struct Entry entry; 
typedef enum BOOL {false, true} bool;

struct Entry 
{
	entry *next;
	entry *prev; // previous
	int value;
};

static entry *head = NULL; // first item
static entry *tail = NULL; // last item
static entry *traverseEntry = NULL; // used to track where we are for table traversal functions
static int totalEntries = 0;


// -----------------------------------------------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------------------------------------------

bool insertItem(int);
bool removeItem(int); 
void clearTable(void);
bool search(it);
bool firstItem(int * const);
bool nextItem(int * const);

static void display(void);
static bool validValue(int);
static void validEntry(entry*);
static void validTable(void);

int main(void)
{
	
//	entry *newEntry = NULL; 
	int i;
	int size = 5;
	int value; 

//	newEntry = malloc(sizeof(entry));
//	newEntry -> value = 0;
//	newEntry -> prev = NULL;
//	newEntry -> next = NULL;
//	head = newEntry;
//	tail = newEntry;
//	totalEntries++;

	for(i = 1; i <= size; i++)
	{
	//	newEntry = malloc( sizeof(entry));
	//	newEntry -> value = i*5;
	//	newEntry -> next = NULL;
	//	newEntry -> prev = tail; 
	//	tail -> next = newEntry;	
	//	tail = newEntry;
	//	totalEntries++;
		printf("What number do you want to add?" );
		scanf("%d", &value);
		printf("%i\n",insert(value));
	}

	display();
	printf("\n");

	printf("\nend of processing.");
	return 0;

} // main

// -----------------------------------------------------------------------------------------
// insertItem
//
// PURPOSE: if the value is unique then it inserts the value in the correct spot in the table 
// (so that table is sorted).
// INPUT: an integer to insert into the table.
// OUTPUT: return true if the value was successfully inserted and false otherwise.
// -----------------------------------------------------------------------------------------
bool insertItem(int item)
{
	// PRECONDITIONS: table either doesn't exist or is valid, that newValue is a valid
	// entry
	// POSTCONDITIONS: table is valid (checks for sorted), totalEntries increased by one, 
	// totalEnteries >= 1
	
} // insertItem

// -----------------------------------------------------------------------------------------
// removeItem
//
// PURPOSE: removes the value.
// INPUT: an integer to remove from the table.
// OUTPUT: return true if the value was successfully removed and false otherwise.
// -----------------------------------------------------------------------------------------
bool removeItem(int item)
{
	// PRECONDITIONS: The table isn't empty, the table is valid, totalEntries => 1.
	// POSTCONDITIONS: The table does not include item, totalEntries => 0, table is 
	// either valid or HEAD == NULL. 
	
} // removeItem

// -----------------------------------------------------------------------------------------
// clearTable
//
// PURPOSE: empty the table so that we clear all memory (and can start a fresh table).
// -----------------------------------------------------------------------------------------
void clearTable(void)
{
	// PRECONDITION: totalEntries >= 1, head != NULL
	// POSTCONDITION: totalEntries == 0, head == NULL, TAIL == NULL
} // clearTable

// -----------------------------------------------------------------------------------------
// search
//
// PURPOSE: tells us wether or not a given item is in the table. 
// INPUT: the int to search for in the table. 
// OUTPUT: Returns true if the item was found in the table and false if it was not found.
// -----------------------------------------------------------------------------------------
bool search (int item)
{
	// PRECONDITION: The table is valid (totalEntries >= 1, the table is sorted ...)
	// POSTCONDITION: The table is still valid, table entry where the item was found is
	// still valid
	
} // search

// ---------------------------------------------------------------------------------------
// firstItem
//
// PURPOSE: table iterator. Sets traverseEntry to the head entry and sets the int input 
// item to the value of traverseEntry. Used to start traversals at the start of the table. 
// INPUT: the pointer to the int that will store traverseEntry's value.
// OUTPUT: returns true if the item was assigned a value and false if the item was *not*
// assigned a value.
// ---------------------------------------------------------------------------------------
bool firstItem(int * const item)
{
	// PRECONDITION: The table is valid, first item is a valid entry, the table has at 
	// least one item.
	// POSTCONDITION: The table is still valid, the first item is still a valid entry.
} // firstItem

// ---------------------------------------------------------------------------------------
// nextItem
//
// PURPOSE: table iterator. Sets input to the value of the current traversalEntry and 
// increments the traversalEntry. 
// INPUT: the pointer that will store traverseEntry's value. 
// OUTPUT: returns true if the item was assigned a value and false if the item was *not*
// assigned a value.
// ---------------------------------------------------------------------------------------
bool nextItem(int * const item)
{
	// PRECONDITIONS: the table is valid, totalEntries >= 2
	// POSTCONDITIONS: the table is still valid, traverseEntry is still valid
} // nextItem

// ---------------------------------------------------------------------------------------
// display
//
// PURPOSE: Prints out the entir table
// -----------------------------------------------------------------------------------------
static void display(void)
{
	// PRECONDITIONS: 
	// the table exists (head!= NULL), the table is valid (check validTable for more 
	// specifics) 
	// POSTCONDITIONS: the table is still valid
	
	assert(head!=NULL);
	validTable();

	traverseEntry = head;

	while(traverseEntry != NULL)
	{
		printf("%i\n",traverseEntry -> value);
		validEntry(traverseEntry);
		traverseEntry = traverseEntry -> next;
	}	

	printf("\nTotal Entries: %i", totalEntries);
	
	validTable();

} // display

// ----------------------------------------------------------------------------------------
// validValue
// 
// PURPOSE: validates that the value is an int and is unique
// ----------------------------------------------------------------------------------------
static bool validValue(int checkValue)
{
	bool valid = true;

	traverseEntry = head;
	
	while (traverseEntry != NULL)
	{
		assert(traverseEntry -> value != checkValue);
		if (traverseEntry -> value == checkValue)
	        {
			valid = false;
			printf("not unique\n");
	        }	       
		
		traverseEntry = traverseEntry -> next;
	}

	return valid;
}

// PURPOSE: validates the entry
// INPUT: an entry pointer 
// ----------------------------------------------------------------------------------------
static void validEntry(entry *checkEntry)
{
	assert(totalEntries >= 1); 
	assert(head != NULL);
	if(totalEntries > 1)
	{
		assert(checkEntry -> prev != NULL);
	}

} // validEntry

// ----------------------------------------------------------------------------------------
// validTable
//
// PURPOSE: validates table
// ----------------------------------------------------------------------------------------
static void validTable()
{
	traverseEntry = head; // pointer
	int countAgain = 0;
	
	assert(totalEntries >= 1);
	assert(head != NULL);
	assert(tail -> next = NULL);

	while(traverseEntry != NULL)
	{
		validEntry(traverseEntry);
		countAgain++;
		if (totalEntries > 1)
		{
			// that the list is sorted so far and does not repeat
			assert((traverseEntry -> value) < ((traverseEntry -> prev) -> value));
		}
	
		traverseEntry = traverseEntry -> next;
	}

	assert(countAgain == totalEntries);
	
} // validTable
