//------------------------------------------------------------------------------
// REMARKS: This is the header file the table.c. It's interface and contains
// the function declarations and the macro definitios for table.c.
//-------------------------------------------------------------------------------

#ifndef _TABLE_H
#define _TABLE_H

//-----------------------------------------------------------------------------
// CONSTANTS AND TYPES
//-----------------------------------------------------------------------------

typedef enum BOOL { false, true } bool;

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------

// add an element to the table
// Return TRUE if the item is in the table
// Return FALSE if the item is *not* in the table
bool insertItem( int item );
// removes the int from the table
bool removeItem( int item );
// empty the table so that we clear all memory and can start a fresh table
void clearTable( );
// tells us whether or not the given item is in the table
bool search( int item );
// table iterators
// Return TRUE if item was assigned
// Return FALSE if item was *not* assigned
bool firstItem( int * const item );
bool nextItem( int * const item );

#endif // _TABLE_H
