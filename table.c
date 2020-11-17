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
	int value;
};

static entry *head = NULL; // first item
static entry *traverseEntry = NULL; // used to track where we are for table traversal functions
static int totalEntries = 0;


// -----------------------------------------------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------------------------------------------

bool insertItem(int);
bool removeItem(int); 
void clearTable(void);
bool search(int);
bool firstItem(int * const);
bool nextItem(int * const);

static void display(void);
static void validTable(void);

int main(void)
{
	
	//entry *newEntry = NULL; 
	int i;
	int size = 5;
	int value; 

	for(i = 0; i <= size; i++)
	{
	//	newEntry = malloc( sizeof(entry));
	//	newEntry -> value = i*size;
	//	newEntry -> next = head;
		
	//	head = newEntry;
	//	totalEntries++;
		printf("What number do you want to add? " );
		scanf("%i", &value);
		printf("%i\n",insertItem(value));
		display();
	}

	//printf("\nLooking for 0: %i\n", search(0));
	//printf("\nLooking for 5: %i\n", search(5));
	//printf("\nLooking for 10: %i\n", search(10));
	//printf("\nLooking for 15: %i\n", search(15));
	//printf("\nLooking for 20: %i\n", search(20));
	//printf("\nLooking for 25: %i\n", search(25));
	//printf("\nLooking for 30: %i\n", search(30));
	//printf("\ndeleting 20: %i\n", removeItem(20));
	//display();
	//printf("\ndeleting 35: %i\n", removeItem(35));
	//display();
	//printf("\ndeleting 15: %i\n", removeItem(15));
	//display();
	//printf("\ndeleting 20: %i\n", removeItem(20));
	//display();
	//printf("\nDeleting 25: %i\n", removeItem(25));
	//display();
	//printf("\nDeleting 0: %i\n", removeItem(0));
	//display();

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
	
	bool inserted = false; 
	bool foundSpot = false;
	entry * curr = head; 
	entry * prev = NULL;
	entry * newEntry;

	if (!search(item))
	{
		newEntry = malloc(sizeof(entry));
		newEntry -> value = item;

		if(!head)
		{
			newEntry -> next = head;
			head = newEntry;	
		} 
		else  
		{
			while (curr != NULL && !foundSpot )
			{
				if (item < curr -> value)
				{
					prev = curr;
					curr = curr -> next; 
				}
				else 
				{
					foundSpot = true;
				}		
			}

			if (prev == NULL) // newEntry is the higher than all the entries on the table
			{
				newEntry -> next = head;
				head = newEntry;
			} 
			else if (curr == NULL) // newEntry is lower than all the entries on the table
			{
				prev -> next = newEntry;
				newEntry -> next = NULL;
			}
			else // newEntry is in the middle of the table
			{
				prev -> next = newEntry; 
				newEntry -> next = curr;
			}
		}

		totalEntries++;
		inserted = true;
	}

	return inserted;	
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
	
	bool removed = false;
	entry * currPtr = head;
	entry * prevPtr = NULL;
	int currVal = currPtr -> value;

		
	if (currVal == item)
	{
		assert(head);
		head = head -> next;
		removed = true;
	
		totalEntries--;
		assert(totalEntries >= 0);
	}
	else if(search(item))
	{
		assert(head);
		validTable();
		
		while(currPtr && !removed)
		{
			prevPtr = currPtr;
			
			currPtr = currPtr -> next;
			currVal = currPtr -> value;

			if (currVal == item)
			{
				currPtr = currPtr -> next;	
				prevPtr -> next = currPtr;
				removed = true;
				totalEntries--;
			}				
		}
		
		validTable();
		assert(head);
		assert(totalEntries >= 0);
	}		

	if(totalEntries > 0)
	{
		assert(head);
		validTable();
	} 
	else 
	{
		assert(!head);
	}

	return removed;

} // removeItem

// -----------------------------------------------------------------------------------------
// clearTable
//
// PURPOSE: empty the table so that we clear all memory (and can start a fresh table).
// -----------------------------------------------------------------------------------------
void clearTable(void)
{
	// PRECONDITION: totalEntries >= 1, head != NULL
	// POSTCONDITION: totalEntries == 0, head == NULL.
	
	entry * curr = head;
	entry * temp = NULL;
		
	assert(totalEntries >= 1);
	
	while(curr)
	{
		assert(head);

		temp = curr;
		curr = curr -> next;

		free(temp);
		temp = NULL;
		totalEntries--;
	}
	
	head = NULL;

	assert(totalEntries == 0);
	assert(head == NULL);

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
	// PRECONDITION: The table is valid (totalEntries >= 1, the table is sorted ...) or 
	// doesn't exist
	// POSTCONDITION: The table is still valid
	
	bool found = false;
	entry * curr = head;
	int val; 
	
	// either table is empty and head is NULL or table is not empty and head exists.
	assert((totalEntries == 0 && !head) || (totalEntries > 0 && head)); 

	// only validate table if there is at least one entry
	if (totalEntries > 0)
	{
		validTable();
	
		while (curr)
		{
			val = curr -> value;
			if(val == item)
			{
				assert(curr -> value == item);
				found = true;	
			}	
		
			curr = curr -> next;
		}

		validTable();
	}

	return found;
} // search

// ---------------------------------------------------------------------------------------
// firstItem
//
// PURPOSE: table iterator. Sets the input item to the first value (head) of the table. 
// Sets traverseEntry to the next (second) entry.
// Used to start traversals at the start of the table. 
// INPUT: the pointer to the int that will store traverseEntry's value.
// OUTPUT: returns true if the item was assigned a value and false if the item was *not*
// assigned a value.
// ---------------------------------------------------------------------------------------
bool firstItem(int * const item)
{
	// PRECONDITION: The table is valid, head is not NULL, the table has at 
	// least one item.
	// POSTCONDITION: The table is still valid, the first item is still a valid entry.
	
	bool result = false; 

	if (head) // head != NULL
	{
		validTable();
		assert(head);
		assert(totalEntries >= 1);

		*item = head -> value; 
		traverseEntry = head -> next; 
		result = true;
	
		validTable();
		assert(totalEntries >= 1);
		assert(head);
	}

	return result;
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
	// POSTCONDITIONS: the table is still valid, totalEntries >= 2
	
	bool result = false;
	
	if (traverseEntry) // is not NULL
	{
		validTable();
		assert(totalEntries >= 2);
				
		*item = traverseEntry -> value; 
		traverseEntry = traverseEntry -> next;
		result = true;
	
		validTable();
		assert(totalEntries >= 2);
	}

	return result; 
} // nextItem

// ---------------------------------------------------------------------------------------
// display
//
// PURPOSE: Implementation method. Prints out the entire table.
// -----------------------------------------------------------------------------------------
static void display(void)
{
	// PRECONDITIONS: the table is valid (check validTable for more specifics) 
	// POSTCONDITIONS: the table is still valid
	
	entry * curr = head;
	int val;

	if(totalEntries > 0)
	{
		validTable();
		while (curr)
		{	
			val = curr -> value; 
			printf("%d\n", val);
			curr = curr -> next;
		}
	       validTable();
	}	       
	else 
	{
		assert(totalEntries == 0);
		assert(!head);
		printf("The table is empty. \n");
	}

	printf("\nTotal Entries: %i\n", totalEntries);

} // display

// ----------------------------------------------------------------------------------------
// validTable
//
// PURPOSE: validates table
// ----------------------------------------------------------------------------------------
static void validTable()
{
	int countAgain = 0;
	
	entry * curr = head;
	entry * prev = NULL;
	
	assert(totalEntries >= 1);
	assert(head);
	
	if(totalEntries > 1)
	{
		prev = curr;
		curr = curr-> next;

		while (curr)
		{	
			// that the list is sorted so far and does not repeat
			assert(prev -> value != curr -> value);
			assert(prev -> value > curr -> value);	
			
			prev = curr; 
			curr = curr -> next;
			countAgain++;
		} 
		
		countAgain++; // to account for the last item on the list	
		assert(countAgain == totalEntries);
	}
} // validTable
