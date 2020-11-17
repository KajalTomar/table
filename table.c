#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include"table.h"

// -----------------------------------------------------------------------------------------------
// CONSTANTS AND TYPES
// -----------------------------------------------------------------------------------------------

typedef static struct Entry entry; 
// typedef static enum BOOL {false, true} bool;

static struct Entry 
{
	entry *next;
	int value;
};

static entry *head = NULL; // first item
static entry *traverseEntry = NULL; // used to track where we are for table traversal functions
static int totalEntries = 0;


// -----------------------------------------------------------------------------------------------
// IMPLEMENTATION PROTOTYPES
// -----------------------------------------------------------------------------------------------

static void display(void);
static void validTable(void);

// -----------------------------------------------------------------------------------------------
// FUNCTIONS
// -----------------------------------------------------------------------------------------------

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
	// PRECONDITIONS: table either doesn't exist or is valid
	// POSTCONDITIONS: table is valid (checks for sorted and each value is unique), 
	// totalEntries increased by exactly one, totalEnteries >= 1
	
	bool inserted = false; 
	bool foundSpot = false;
	
	entry * curr = head; // to iterate the table
	entry * prev = NULL; // to iterate the table
	entry * newEntry;

	if (!search(item)) // only if the new item is unique
	{
		newEntry = malloc(sizeof(entry));
		newEntry -> value = item;
		
		if(!head) // to add the first item in the table
		{
			assert(totalEntries == 0);
			
			clearTable();
			
			newEntry -> next = head;
			head = newEntry;	
			
			assert(head);
		} 
		else  // if at least 1 item (head) exists
		{
			validTable();

			// loop through the table until the correct spot to insert new item
			while (curr != NULL && !foundSpot)
			{
				if (item < curr -> value) // new item is smaller than current entry
				{	
					// then move along
					prev = curr;
					curr = curr -> next; 
				}
				else // if the new item is bigger than the current entry
				{
					foundSpot = true;
				}		
			}

			validTable();

			if (prev == NULL) // newEntry is the higher than all the entries on the table
			{
				// make newEntry the head!
				newEntry -> next = head;
				head = newEntry;
			} 
			else if (curr == NULL) // newEntry is lower than all the entries on the table
			{
				// add it to the end of the table
				prev -> next = newEntry;
				newEntry -> next = NULL;
			}
			else // newEntry is in the middle of the table
			{
				// update the pointer accordingly
				prev -> next = newEntry; 
				newEntry -> next = curr;
			}
		}
		
		totalEntries++;
		inserted = true;

		validTable();
		assert(totalEntries >= 1);
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
	entry * curr = head;
	entry * prev = NULL;

	if (head) // there needs to be at least one item
	{	
		validTable();
		assert(totalEntries >= 1);

		if (curr -> value == item) // to remove head
		{
			assert(head);
			head = head -> next;
			removed = true;
	
			totalEntries--;
			assert(totalEntries >= 0);
		}
		else if(search(item)) // item != head but does exist on the table
		{
			assert(head);
			validTable();
		
			while(curr && !removed) // loop until end of the table or until we find the spot
			{
				prev = curr;
				curr = curr -> next;

				if (curr -> value == item) // we found the match!
				{
					// update pointers to exclude the item
					curr = curr -> next;	
					prev -> next = curr;

					removed = true;
					totalEntries--;
				}					
			}
		
			assert(head);
			assert(totalEntries >= 1); // since head wasn't removed so at least 1 item remains
		}
		
		if (totalEntries == 0)
		{
			clearTable(); // just to be sure
		}
		else 
		{
			validTable(); 
		}
		
		assert(!search(item)); // the item is no longer in the table
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
		
	
	while(curr) // so only if at least one item exists
	{
		assert(head);
		assert(totalEntries >= 1);

		temp = curr;
		curr = curr -> next;

		free(temp); // be free!
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
	
	// either table is empty and head is NULL or table is not empty and head exists.
	assert((totalEntries == 0 && !head) || (totalEntries > 0 && head)); 

	// only search table if there is at least one entry
	if (head && totalEntries > 0)
	{
		validTable();
		
		// loop until the end of the table or until we find the item
		while (curr && !found)
		{
			if(curr -> value == item)
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
	// POSTCONDITION: The table is still valid, head != NULL.
	
	bool result = false; 

	if (head) // head != NULL
	{
		validTable();
		assert(head);
		assert(totalEntries >= 1);

		*item = head -> value; // asign value
		traverseEntry = head -> next;  // update traverseEntry
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
				
		*item = traverseEntry -> value; // assign value
		traverseEntry = traverseEntry -> next; // update traverseEntry
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

	if(totalEntries > 0) // only if the table exists
	{
		validTable();

		// loop until the end of the table
		while (curr)
		{	
			val = curr -> value; 
			printf("%d\n", val);
			curr = curr -> next;
		}

	       validTable();
	}	       
	else  // the table doesn't exist
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
	int countAgain = 0; // we will recount the entries
	
	entry * curr = head;
	entry * prev = NULL;
	
	assert(totalEntries >= 1);
	assert(head);
	
	if(totalEntries > 1) 
	{
		prev = curr;
		curr = curr -> next;
		
		// loop the whole table
		while (curr)
		{	
			// check that the list is sorted so far and does not repeat
			assert(prev -> value != curr -> value);
			assert(prev -> value > curr -> value);	
			
			prev = curr; 
			curr = curr -> next;
			
			countAgain++;
		} 
		
		countAgain++; // to account for the last item on the list	
		
		// confirm that countAgain is accurate
		assert(countAgain == totalEntries);
	}

} // validTable
