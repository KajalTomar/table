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
// insert
//
// PURPOSE: inserts the value in the correct spot in the table (so that table is sorted)
// INPUT: an integer to insert into the table
// OUTPUT: return true if the value was successfully inserted and false otherwise
// -----------------------------------------------------------------------------------------

bool insertItem(int item)
{
	// PRECONDITIONS: table either doesn't exist or is valid, that newValue is a valid
	// entry
	// POSTCONDITIONS: table is valid, totalEntries increased by one, totalEnteries >= 1
	// is the newEntry valid?
	
} // insertItem

// -----------------------------------------------------------------------------------------
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
