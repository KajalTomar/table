#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

// table entry definition
typedef struct Entry entry; 

struct Entry 
{
	entry *next;
	entry *prev; // previous
	int value;
};

static entry *head = NULL; // first item
static entry *tail = NULL; // last item
static int totalEntries = 0;

static void display(void);
static void validEntry(entry*);
static void validTable(void);

int main(void)
{
	
	entry *newEntry = NULL; 
	int i;
	int size = 4;
	
	newEntry = malloc(sizeof(entry));
	newEntry -> value = 0;
	newEntry -> prev = NULL;
	newEntry -> next = NULL;
	head = newEntry;
	tail = newEntry;
	totalEntries++;

	for(i = 1; i <= size; i++)
	{
		newEntry = malloc( sizeof(entry));
		newEntry -> value = i*5;
		newEntry -> next = NULL;
		newEntry -> prev = tail; 
		tail -> next = newEntry;	
		tail = newEntry;
		totalEntries++;
	}

	display();
	printf("\n");

	printf("\nend of processing.");
	return 0;
}

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

	entry *p = head;

	while(p != NULL)
	{
		printf("%i\n",p -> value);
		validEntry(p);
		p = p -> next;
	}	

	printf("\nTotal Entries: %i", totalEntries);
	
	validTable();
}

// ----------------------------------------------------------------------------------------
// validEntry
//
// PURPOSE: validates the entry
// INPUT: an entry pointer 
// ----------------------------------------------------------------------------------------
static void validEntry(entry *checkEntry)
{
	assert(totalEntries >= 1); 
	assert(head != NULL);
	assert(isdigit(checkEntry -> value));
	if(totalEntries > 1)
	{
		assert(checkEntry -> prev != NULL);
	}
}

// ------------------------------------------------------------------------
// validTable
//
// PURPOSE: validates table
// ------------------------------------------------------------------------
static void validTable()
{
	entry *p = head; // pointer
	int countAgain = 0;
	
	assert(totalEntries >= 1);
	assert(head != NULL);
	assert(tail -> next = NULL);

	while(p != NULL)
	{
		validEntry(p);
		countAgain++;
		if (totalEntries > 1)
		{
			// that the list is sorted so far and does not repeat
			assert((p -> value) < ((p -> prev) -> value));
		}
	}

	assert(countAgain == totalEntries);
	
}
