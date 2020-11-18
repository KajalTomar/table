#include<stdio.h>
#include"table.h"

//typedef enum BOOL {false, true} bool;
void clearCases(void);
void removeCases(void);
void insertCases(void);

void testClearTable(bool);
void testRemoveItem(int, bool);
void testInsertItem(int, bool);

void display(void);

// declaring variables.
int testsFailed = 0;
int testsExecuted = 0;

int main(void)
{
	
	insertCases(); // tests the cases for insertItem() and prints the results	
	removeCases(); // tests the cases for removeItem() and prints the results
	clearCases(); // tests the cases for clearTable() and prints the results 
	//  print out how many tests executes, passes, failed
	printf("\n----------------------------------------------------------------------------------------------------------\n");
	printf("Total number of tests executed: %i\n", testsExecuted);
	printf("Total number of tests passed: %i\n", testsExecuted - testsFailed);
	printf("Total number of tests failed: %i\n", testsFailed);
	printf("----------------------------------------------------------------------------------------------------------\n");

	return 0;
} 

// -------------------------------------------------------------------------------------------------------
// FUNCTIONS THAT CALL THE TEST FUNCIONS AND PRINT THE RESULTS
// -------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// clearCases
//
// PURPOSE: Calls testClearTable to test normal and edge cases
// -----------------------------------------------------------------------------
void clearCases(void)
{
	// inserting some items the table

	insertItem(23);
	insertItem(3);
	insertItem(2);
	insertItem(-3);

	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR clearTable()\n");
	printf("Testing typical cases.\n\n");
	// test and print out the results from the typical cases
	printf("Clearing a normal expected table with four valid values...\n");
	testClearTable(true);
	
	// inserting exactly two items in the table
	insertItem(5);
	insertItem(54);
	printf("Clearing a table with exactly two entries...\n");
	testClearTable(true);

	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	// inserting only one item in the table
	insertItem(100);
	printf("Clearing a table with exactly one entry...\n");
	testClearTable(true);

	printf("Clearing a table that was already empty...\n");
	testClearTable(true); // case where the table is already clear

	// test and print out the results from the edge cases
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
	// test and print out the results from the typical cases
	printf("Testing typical cases.\n\n");
	
	testRemoveItem(5, true);
	testRemoveItem(12, true);
	testRemoveItem(-5, true);
	
	printf("Removing an item that was not in the table...\n");
	testRemoveItem(100, false); // item not in the table
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	// test and print out the results from the edge cases
	
	printf("Removing the entry in the first position of the table...\n");
	testRemoveItem(2147483647, true); 
	
	printf("Removing the entry int the last position of the table...\n");
	testRemoveItem(-2147483648, true); 
	
	printf("Removing the last entry left in the table...\n");
	testRemoveItem(0, true); 
	
	printf("Removing an item form an empty list...\n");
	testRemoveItem(12, false); 
	
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

	// test and print out the results from the typical cases
	printf("Testing typical cases.\n\n");
	testInsertItem(5, true);
	
	printf("Inserting an entry that is not unique...\n");
	testInsertItem(5, false); // not unique
	
	testInsertItem(0, true);
	testInsertItem(12, true);
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	// test and print out the results from the edge cases
	testInsertItem(-5, true);
	
	printf("Inserting a negative entry that is not unique...\n");
	testInsertItem(-5, false); // not unique
	
	printf("Inserting the maximum value for an integer in C...\n");
	testInsertItem(2147483647, true); // max value for an int 
	
	printf("Inserting the minimum value for an integer in C...\n");
	testInsertItem(-2147483648, true); // min value for an int 
	printf("----------------------------------------------------------------------------------------------------------\n\n");
	
} // printTestInsert

// -------------------------------------------------------------------------------------------------------
// THE TEST FUNCTIONS
// -------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// testClearTable
// 
// PURPOSE: Test if the clearTable's results match the expected results then 
// display the outcome.
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
			printf("Passed! The table was cleared.\n\n");
	} 
	else
	{
		printf("FAILED: I though the table would be cleared but it's not.\n\n");
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
			printf("Passed! %i was successfully removed from the table.\n\n", item);
		}
		else
		{
			printf("Passed! %i was not removed from the table (and we didn't expect it to).\n\n", item);
		}
	}
	else 
	{
		if(testResult && !expectedResult)
		{
			printf("Failed: I thought the %i would *not* be removed, but something was removed...\n\n", item);		
		}
		else
		{
			printf("Failed: I thought the %i would be removed, but it was *not*\n\n", item);		
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
			printf("Passed! %i is a valid entry that was inserted successfully in the table.\n\n", item);
		}
		else
		{
			printf("Passed! %i is a *not* a valid (not unique) entry so it was *not* inserted in the table.\n\n", item);
		}
	}
	else 
	{
		if (testResult && !expectedResult)
		{
			printf("FAILED: I thought that the value would *not* be added to the table but it was added.\n\n");
		} 
		else 
		{
			printf("FAILED: I thought that the value would be added to the table but it was *not* added.\n\n");
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
	
	printf("\n---------\n");
	if (firstItem(&value))
	{
		do
		{
			printf("%i\n", value);
		} while (nextItem(&value));
	}
	printf("---------\n");
}
