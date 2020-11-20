//------------------------------------------------------------------------------
// NAME: Kajal Tomar
// STUDENT NUMBER: 7793306
// COURSE: COMP2160, SECTION: A01
// INSTRUCTOR: Dr. Mehdi Niknam
// ASSIGNMENT: 3, QUESTION: 1
// 
// REMARKS: This is the automated test suite for the table.c ADT implementation.. 
//-------------------------------------------------------------------------------

#include<stdio.h>
#include"table.h"

//-----------------------------------------------------------------------------
// CONSTANTS AND TYPES
//-----------------------------------------------------------------------------

int testsFailed = 0;
int testsExecuted = 0;

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------

void testMemoryLeaks(void);
int recount(void);

void nextItemCases(void);
void firstItemCases(void);
void searchCases(void);
void clearCases(void);
void removeCases(void);
void insertCases(void);

void testNextItem(int, bool);
void testFirstItem(int, bool);
void testSearch(int, bool);
void testClearTable(bool);
void testRemoveItem(int, bool);
void testInsertItem(int, bool);

void display(void);

int main(void)
{
	// test each function with typical and edge cases
	insertCases();	
	removeCases();
	clearCases();  
	searchCases(); 
	firstItemCases();
	nextItemCases();
	testMemoryLeaks();

	//  print out how many tests executes, passes, failed
	printf("\n----------------------------------------------------------------------------------------------------------\n");
	printf("Total number of tests executed: %i\n", testsExecuted);
	printf("Total number of tests passed: %i\n", testsExecuted - testsFailed);
	printf("Total number of tests failed: %i\n", testsFailed);
	printf("----------------------------------------------------------------------------------------------------------\n");
	
	printf("\nend of processing.\n");
	return 0;
} 


// -----------------------------------------------------------------------------
// testMemoryLeaks
// 
// PURPOSE: to test the program for any memory leaks
// -----------------------------------------------------------------------------
void testMemoryLeaks(void)
{
	bool leak = false;
	int totalEntries = 1000;
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTING FOR MEMORY LEAKS....\n");

	// first pinsert a large numver of items
	for(int i = 0; i < totalEntries; i++)
	{
		insertItem(i*totalEntries);
	}

	// does the amount of items reflect the correct amount of items
	if(recount() != totalEntries)
	{
		leak = true;
	}

	// remove all the items
	for(int i=0; i<totalEntries; i++)
	{
		removeItem(i*totalEntries);
	}
	
	// does the new number of entries reflect the actual number of entries we expect (=0)
	if(recount() != 0)
	{
		leak = true;
	}

	// print the results
	if(leak)
	{
		printf("FAILED: This program creates memory leaks.\n");
		testsFailed++;
	} 
	else
	{
		printf("Passed! This program does *not* create any memory leaks.\n");
	}
	
	testsExecuted++; 

	printf("\n----------------------------------------------------------------------------------------------------------\n");
} //testMemoryLeaksi


// -----------------------------------------------------------------------------
// recount
//
// PURPOSE: countes the amount of entries on the table
// OUTPUT: the amount of entries on the table (int)
// -----------------------------------------------------------------------------
int recount(void)
{
	int firstEntry; 
	int nextEntry;
	int recount = 0;

	if(firstItem(&firstEntry))
	{
		do
		{
			recount++;
		} while(nextItem(&nextEntry));
	}

	return recount;

} //recount

// -------------------------------------------------------------------------------------------------------
// FUNCTIONS THAT CALL THE TEST FUNCIONS TO TEST TYPICAL AND EDGE CASES
// -------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// nextItemCases
//
// PURPOSE: Calls testNextItem to test normal and edge cases
// -----------------------------------------------------------------------------
void nextItemCases(void)
{
	int first; // to hold the first item
	int i; // to iterate through the table
	int entryAmount = 5;

	printf("----------------------------------------------------------------------------------------------------------\n");
	
	printf("TESTS FOR nextItemCases()\n");
	printf("Testing typical cases.\n\n");
	// test and print out the results from the typical cases
	
	clearTable();
	
	// create a typical table
	for(i = entryAmount; i >= 1; i--)
	{
		insertItem(i*entryAmount);
	}
	display();

	firstItem(&first);
	
	for (int i = entryAmount-1; i >= 2; i--)
	{
		printf("Getting the next item...\n");
		testNextItem(i*entryAmount, true);
	}
	
	printf("---------------------------\n");
	// test and print out the results from the edge cases
	printf("Testing edge cases.\n\n");
	
	printf("Getting the last item on the table...\n");
	testNextItem(5, true);
	
	printf("\n--Reset traversal--\n");
	display();
	firstItem(&first); // reset traverseEntry
	removeItem(20);

	// removing the second entry and then tring to get the next Entry
	printf("Removed the entry in the second position (20). Getting the next item...\n");
	testNextItem(15, true);

	insertItem(13);
	printf("\nAdded an new entry right (13) after the current traverse entry. Getting next item...\n");
	testNextItem(13, true);
	display();

	clearTable();
	insertItem(5);
	firstItem(&first);
	
	printf("\nGetting next item when there is only one item one the table\n");
	testNextItem(-1, false);
	display();

	removeItem(5);

	printf("Getting next item when the table is empty\n");
	testNextItem(-1, false);
	display();

	printf("----------------------------------------------------------------------------------------------------------\n\n");
} // nextItemCases

// -----------------------------------------------------------------------------
// firstItemCases
// 
// PURPOSE: Calls testFirstItem to test normal and edge cases
// -----------------------------------------------------------------------------
void firstItemCases(void)
{
	
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR firstItemCases()\n");

	printf("Testing typical cases.\n\n");
	// test and print out the results from the typical cases
	
	clearTable();
	insertItem(3);
	insertItem(0);
	insertItem(-5);

	printf("Getting the first item...\n");
	testFirstItem(3, true);
	display();
	
	clearTable();
	insertItem(5);
	insertItem(10);
	insertItem(15);

	printf("Getting the first item...\n");
	testFirstItem(15, true);
	display();
	
	printf("---------------------------\n");
	// test and print out the results from the edge cases
	printf("Testing edge cases.\n\n");
		
	removeItem(15);
	printf("Removed the first item. Getting the new first item...\n");
	testFirstItem(10, true);
	display();
	
	insertItem(100);
	printf("Inserted a new item [100]. Getting the first item...\n");
	testFirstItem(100, true);
	display();

	removeItem(100);
	removeItem(10);
	printf("Getting the first item when there is only one item on the table...\n");
	testFirstItem(5, true);
	display();
	
	printf("\n");
	clearTable();

	printf("Getting the first item from an empty table...\n");
	testFirstItem(-1, false); // -1 = didn't get assigned
	display();
	
	printf("----------------------------------------------------------------------------------------------------------\n\n");

} // firstItemCases


// -----------------------------------------------------------------------------
// searchCases
// 
// PURPOSE: Calls testSearch to test normal and edge cases
// -----------------------------------------------------------------------------
void searchCases(void)
{
	int entryAmount = 5;
	int i;
	clearTable();
	// making a typical table to test search with
	
	for(i = 0; i< entryAmount; i++)
	{
		insertItem(i*5);
	}

	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR search()\n");
	printf("Testing typical cases.\n\n");
	// test and print out the results from the typical cases
	
	// search for all the values on this table
	display();
	for (i = 0; i< entryAmount; i++)
	{
		printf("Searching for %i...\n", i*5);
		testSearch(i*5, true);
	}
	
	printf("\n---------------------------\n");
	printf("Testing edge cases.\n\n");

	printf("Searching for 123 (not on the table)...\n");
	testSearch(123, false);
	display();

	insertItem(50);
	printf("Inserted a new entry [50]. Searching for 50...\n");
	testSearch(50, true);
	display();

	removeItem(10);
	printf("Removed an entry [10]. Searching for 10...\n");
	testSearch(10, false);
	display();

	removeItem(50);
	printf("Removed the first entry [50]. Searching for 50...\n");
	testSearch(50, false);
	display();

	removeItem(0);
	printf("Removed the last entry [0]. Searching for 0... \n ");
	testSearch(0, false);
	display();

	clearTable();
	insertItem(5);
	printf("Searching for 5 (when the table only has one entry)...\n");
	testSearch(5, true);
	display();

	clearTable();
	printf("Searching for 77 (in an empty table)...\n");
	testSearch(77, false);
	display();
	printf("----------------------------------------------------------------------------------------------------------\n\n");

} // searchCases

// -----------------------------------------------------------------------------
// clearCases
//
// PURPOSE: Calls testClearTable to test normal and edge cases
// -----------------------------------------------------------------------------
void clearCases(void)
{
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR clearTable()\n");
	
	printf("Testing typical cases.\n\n");
	// test and print out the progress for the typical cases

	// inserting some values to make a typical table
	insertItem(23);
	insertItem(3);
	insertItem(2);
	insertItem(-3);
	display();
	
	printf("Clearing a normal expected table with four valid values...\n");
	testClearTable(true);
	display();
	
	// inserting exactly two items in the table
	insertItem(5);
	insertItem(54);
	display();
	
	printf("Clearing a table with exactly two entries...\n");
	testClearTable(true);
	display();

	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	// test and print out the progress for the edge cases
	// inserting only one item in the table
	insertItem(100);
	display();
	
	printf("Clearing a table with exactly one entry...\n");
	testClearTable(true);
	display();

	printf("Clearing a table that was already empty...\n");
	testClearTable(true); // case where the table is already clear
	display();

	printf("----------------------------------------------------------------------------------------------------------\n\n");
} //clearCases

// -----------------------------------------------------------------------------
// removeCases
//
// PURPOSE: Calls testRemoveItem to test normal and edge cases
// -----------------------------------------------------------------------------
void removeCases(void)
{
	
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR removeItem()\n");
	// test and print out the progress from the typical cases
	printf("Testing typical cases.\n\n");
	display();

	testRemoveItem(5, true);
	display();
	testRemoveItem(12, true);
	display();
	testRemoveItem(-5, true);
	display();
	
	printf("Removing an item that was not in the table...\n");
	testRemoveItem(100, false); // item not in the table
	display();
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	// test and print out the progress from the edge cases
	
	printf("Removing the entry in the first position of the table...\n");
	testRemoveItem(2147483647, true); 
	display();
	
	printf("Removing the entry in the last position of the table...\n");
	testRemoveItem(-2147483648, true); 
	display();
	
	printf("Removing the last entry left in the table...\n");
	testRemoveItem(0, true); 
	display();
	
	printf("Removing an item when the table is empty...\n");
	testRemoveItem(12, false); 
	display();
	
	printf("----------------------------------------------------------------------------------------------------------\n\n");

} // removeCases

// -----------------------------------------------------------------------------
// insertCases
// 
// PURPOSE: calls the testInsertItem to test normal and edge cases
// -----------------------------------------------------------------------------
void insertCases(void)
{

	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR insertItem()\n");

	// test and print out the progress from the typical cases
	printf("Testing typical cases.\n\n");
	testInsertItem(5, true);
	display();
	
	printf("Inserting an entry that is not unique...\n");
	testInsertItem(5, false); // not unique
	display();
	
	testInsertItem(0, true);
	display();
	testInsertItem(12, true);
	display();
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	// test and print out the progress from the edge cases
	testInsertItem(-5, true);
	display();
	
	removeItem(12);
	printf("Removed entry [12].\n");
	testInsertItem(12, true);
	display();

	printf("Inserting a negative entry that is not unique...\n");
	testInsertItem(-5, false); // not unique
	display();
	
	printf("Inserting the maximum value for an integer in C...\n");
	testInsertItem(2147483647, true); // max value for an int 
	display();
	
	printf("Inserting the minimum value for an integer in C...\n");
	testInsertItem(-2147483648, true); // min value for an int 
	display();
	printf("----------------------------------------------------------------------------------------------------------\n\n");
	
} // printTestInsert

// -------------------------------------------------------------------------------------------------------
// FUNCTIONS THAT TEST AND PRINT THE RESULTS 
// -------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// testNextItem
// 
// PURPOSE:Test to see if nextItem function's results math the expected results
// and display the outcome. 
// INPUT: the expected next item (int) and the expected success of the function 
// (bool)
// -----------------------------------------------------------------------------
void testNextItem(int expectedNext, bool expectedResult)
{
	int next; // next entry 
	bool testResult;

	testResult = nextItem(&next);
	
	if(testResult == expectedResult)
	{
		if(testResult && (next = expectedNext))
		{
			printf("Passed! We found the next item and it was %i.\n", next);
		}
		else if (!next && expectedNext == -1)
		{
			printf("Passed! As expected, there is no next item.\n");
		}
	}
	else 
	{
		if(!testResult)
		{
			printf("FAILED: we expected %i to be the next value but the function did *not* find it.\n", expectedNext);
		}
		else 
		{
			printf("FAILED: we were *not* expecting a next value but the function found the next value to be %i.\n", next);
		}

		testsFailed++;
	}
	
	testsExecuted++;

} // testNextItem

// -----------------------------------------------------------------------------
// testFirstItem
// 
// PURPOSE: Test to see if firstItem function's results match the expected 
// results and display the outcome.
// INPUT: the expected first item (int) and the expected success of the function
// (bool)
// -----------------------------------------------------------------------------
void testFirstItem(int expectedFirst, bool expectedResult)
{
	int first; //first entry
	bool testResult;

	testResult = firstItem(&first);

	if(testResult == expectedResult)
	{
		if(testResult && (first == expectedFirst))
		{
			printf("Passed! We found the first item and it was %i.\n", first);
		} 
		else if (!first && expectedFirst == -1)
		{
			printf("Passed! We didn't find the first item (because the table is empty).\n");
		}
	}
	else 
	{
		if(testResult)
		{
			printf("FAILED: we were *not* expecting to have a first item but the function found %i.\n", first);
		}
		else 
		{
			printf("FAILED: we were expecting %i to be the first item but the function did *not* find it.\n", first);
		}
		testsFailed++;
	}

	testsExecuted++;

} // testFirstItem

// -----------------------------------------------------------------------------
// testSearch
//
// PURPOSE: Test if search function's results match the expected results and
// display the outcome. 
// INPUT: The int to search for in the table and the expected outcome (bool)
// -----------------------------------------------------------------------------
void testSearch(int lookFor, bool expectedResult)
{
	bool testResult;
	testResult = search(lookFor);

	if(testResult == expectedResult)
	{
		if(testResult)
		{
			printf("Passed! We found %i as expected.\n", lookFor);
		} 
		else 
		{
			printf("Passed! We didn't find %i (just like we expected).\n", lookFor);
		}
	}
	else 
	{
		if(testResult)
		{
			printf("FAILED: we though we would *not* find %i, but the function found something.\n", lookFor);
		}
		else
		{
			printf("FAILED: we thought we would would %i, but we didn *not*.\n", lookFor);
		}
		testsFailed++;
	}

	testsExecuted++;

}// testSearch

// -----------------------------------------------------------------------------
// testClearTable
// 
// PURPOSE: Test if the clearTable function's results match the expected results  
// and display the outcome.
// INPUT: The expected result (bool)
// -----------------------------------------------------------------------------
void testClearTable(bool expectedResult)
{
	bool testResult;
	int head;
	
	clearTable();

	if(firstItem(&head)) // at least one item exists, the table is not clear
	{
		testResult = false;
	} 
	else 
	{
		testResult = true; // the table was cleared (there is no firstItem)
	}

	if(testResult == expectedResult)
	{
			printf("Passed! The table was cleared.\n");
	} 
	else
	{
		printf("FAILED: I though the table would be cleared but it's not.\n");
		testsFailed++;
	}
	
	testsExecuted++;
}

// -----------------------------------------------------------------------------
// testRemoveItem
//
// PURPOSE: Test if the removeItem's results match the expected results then 
// display the outcome
// INPUT: int item is the item to be removed, the expected reults (bool) to
// test against
// -----------------------------------------------------------------------------
void testRemoveItem(int item, bool expectedResult)
{

	bool testResult = removeItem(item);

	printf("Removing %i...\n", item);
	
	if(testResult == expectedResult)
	{
		if(testResult)
		{
			printf("Passed! %i was successfully removed from the table.\n", item);
		}
		else
		{
			printf("Passed! %i was not removed from the table (and we didn't expect it to).\n", item);
		}
	}
	else 
	{
		if(testResult && !expectedResult)
		{
			printf("FAILED: I thought the %i would *not* be removed, but something was removed...\n", item);		
		}
		else
		{
			printf("FAILED: I thought the %i would be removed, but it was *not*\n", item);		
		}
		testsFailed++;
	}
	
	testsExecuted++;

} // testRemoveItem

// -----------------------------------------------------------------------------
// testInsertItem
// 
// PURPOSE: Test if the removeItem's results match the expected results then 
// display the outcome.
// INPUT: int item is the item to be inserted, the expected results (bool) to 
// test against
// -----------------------------------------------------------------------------

void testInsertItem(int item, bool expectedResult)
{
	bool testResult = insertItem(item);
	
	printf("Inserting %i...\n", item);
	
	if(testResult == expectedResult)
	{
		if(testResult)
		{
			printf("Passed! %i is a valid entry that was inserted successfully in the table.\n", item);
		}
		else
		{
			printf("Passed! %i is a *not* a valid (not unique) entry so it was *not* inserted in the table.\n", item);
		}
	}
	else 
	{
		if (testResult && !expectedResult)
		{
			printf("FAILED: I thought that the value would *not* be added to the table but it was added.\n");
		} 
		else 
		{
			printf("FAILED: I thought that the value would be added to the table but it was *not* added.\n");
		}
		testsFailed++;
	}

	testsExecuted++;
} // testInsertItem

// -----------------------------------------------------------------------------
// display
//
// PURPOSE: Prints out the entire table. 
// -----------------------------------------------------------------------------
void display(void)
{
	int value;
	
	printf("[ ");
	if (firstItem(&value))
	{
		do
		{
			printf("%i ", value);
		} while (nextItem(&value));
	}
	printf("]\n\n");
}
