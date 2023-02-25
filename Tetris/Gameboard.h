#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "Point.h"

class Gameboard
{
public:
	static const int MAX_X = 10;		// gameboard x dimension
	static const int MAX_Y = 19;		// gameboard y dimension
	static const int EMPTY_BLOCK = -1;	// contents of an empty block
	// METHODS -------------------------------------------------
// 
// constructor - empty() the grid
	Gameboard();

// fill the board with EMPTY_BLOCK 
//   (iterate through each rowIndex and fillRow() with EMPTY_BLOCK))
// - params: none
// - return: nothing
	void empty();

	/* print the grid contents to the console (for debugging purposes)
	   use std::setw(2) to space the contents out
	   (google it, you'll need to #include <iomanip>).
	   If the content == EMPTY_BLOCK, print a '.', otherwise print the content.
	 - params: none
	 - return: nothing*/
	void printToConsole() const;

	// get the content at a given point 
	// assert the point is valid (use isValidPoint())
	// - param 1: a Point (the XY of the content weant to retrieve)
	// - return: an int, the content from the grid at the specified point 
	 int getContent(Point content) const;

	// get the content at a given XY location
	// assert the point is valid (use isValidPoint())
	// - param 1: an int for X (column)
	// - param 2: an int for Y (row)
	// - return: an int, the content from the grid at the specified XY
	int getContent(int x, int y) const;

	// set the content at a given point (ignore invalid points)
	// - param 1: a Point
	// - param 2: an int representing the content we want to set at this location.
	void setContent(Point point, int content);

	// set the content at an x,y position (ignore invalid points)
	// - param 1: an int for X (column)
	// - param 2: an int for Y (row)
	// - param 3: an int representing the content we want to set at this location	
	void setContent(int x, int y, int content);

	// set the content for a set of points (ignore invalid points)
	// - param 1: a vector of Points representing locations
	// - param 2: an int representing the content we want to set.
	void setContent(const std::vector<Point>& locations, int content);

	// Determine if (valid) all points passed in are empty
	// *** IMPORTANT: Assume invalid x,y values can be passed to this method.
	// Invalid meaning outside the bounds of the grid.
	// * ONLY TEST VALID POINTS (use isValidPoint()). Ignore invalid Points.
	// Using invalid points to index into the grid would cause undefined behaviour. 
	// - param 1: a vector of Points representing locations to test
	// - return: true if the content at ALL VALID points is EMPTY_BLOCK, false otherwise
	bool areAllLocsEmpty(const std::vector<Point>& locations) const;

	// Remove all completed rows from the board
	//   use getCompletedRowIndices() and removeRows() 
	// - params: none
	// - return: the count of completed rows removed
	int removeCompletedRows();

	// A getter for the spawn location
	// - params: none
	// - returns: a Point, representing our private spawnLoc
	Point getSpawnLoc();

private:
	/* MEMBER VARIABLES -------------------------------------------------

	 the gameboard - a grid of X and Y offsets.  
	  ([0][0] is top left, [MAX_Y-1][MAX_X-1] is bottom right) 

	 the gameboard offset to spawn a new tetromino at.*/
	const Point spawnLoc{ MAX_X / 2, 0 };
	int grid[MAX_Y][MAX_X];
	// Determine if a given Point is a valid grid location
	// - param 1: a Point object
	// - return: true if the point is a valid grid location, false otherwise
	bool isValidPoint(Point point) const;

	// Determine if a given XY is a valid grid location
	// - param 1: an int representing x
	// - param 2: an int representing y
	// - return: true if the x,y is a valid grid location, false otherwise
	bool isValidPoint(int x, int y) const;

	// return a bool indicating if a given row is full (no EMPTY_BLOCK in the row)
	// assert the row index is valid
	// - param 1: an int representing the row index we want to test
	// - return: bool representing if the row is completed
	bool isRowCompleted(int row) const;

	// fill a given grid row with specified content
	// - param 1: an int representing a row index
	// - param 2: an int representing content
	// - return: nothing
	void fillRow(int rowIndex, int content);

	// scan the board for completed rows.
	// Iterate through grid rows and use isRowCompleted(rowIndex)
	// - params: none
	// - return: a vector of completed row indices (integers).
	std::vector<int> getCompletedRowIndices() const;

	// copy a source row's contents into a target row.
	// - param 1: an int representing the source row index
	// - param 2: an int representing the target row index
	// - return: nothing
	void copyRowIntoRow(int sourceRow, int targetRow);

	// In gameplay, when a full row is completed (filled with content)
	// it gets "removed".  To be exact, the row itself is not removed
	// but the content from the row above it is copied into it.
	// This continues all the way up the grid until the first row is copied
	// into the second row.  Finally, the first row is filled with EMPTY_BLOCK
	// Given a row index:
	//   1) Assert the row index is valid
	//   2) Starting at rowIndex, copy each row above the removed
	//     row "one-row-downwards" in the grid.
	//     (loop from y=rowIndex-1 down to 0, and copyRowIntoRow(y, y+1)).
	//   3) call fillRow() on the first row (and place EMPTY_BLOCKs in it).
	// - param 1: an int representing a row index
	// - return: nothing
	void removeRow(int rowIndex);

	// given a vector of row indices, remove them. 
	//   Iterate through the vector, call removeRow() on each row index. 
	// - param 1: a vector of integers representing row indices we want to remove
	// - return: nothing
	void removeRows(std::vector<int>& rows);

	friend class TestSuite;
};

#endif /* GAMEBOARD_H */

#pragma once
