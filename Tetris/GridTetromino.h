// The GridTetromino extends the basic Tetromino
// Functionality added:
//  - The concept of the tetromino's location on the gameboard/grid. (gridLoc)
//  - The ability to change a tetromino's location
//  - The ability to retrieve a vector of tetromino block locations mapped to the gridLoc.
//
//  [expected .cpp size: ~ 40 lines]

#ifndef GRIDTETROMINO_H
#define GRIDTETROMINO_H

#include "Tetromino.h"


// Make this class extend (inherit from) the Tetromino class.
// Complete each method signature below
// Implement the methods below in a GridTetromino.cpp file.
class GridTetromino : public Tetromino
{

	// MEMBER VARIABLES
private:
	Point gridLoc;	// the [x,y] location of this tetromino on the grid/gameboard. 
	// This loc changes each time the tetromino moves.

public:
	// constructor, initialize gridLoc to 0,0
	GridTetromino();

	// a getter for the tetromino's location
	// - params: none
	// - return: a Point (the private member variable gridLoc) 
	Point getGridLoc() const;

	// a setter for the tetronimo's location 
	// - param 1: int x
	// - param 2: int y
	// return: nothing
	void setGridLoc(int x, int y);

	// a setter for the tetromino's location
	// param 1: a Point (the new gridLoc)
	// return: nothing
	void setGridLoc(const Point& newGridLoc);

	// transpose the gridLoc of this shape
	//	(1,0) represents a move to the right (x+1)
	//	(-1,0) represents a move to the left (x-1)
	//	(0,1) represents a move down (y+1)
	// - param 1: int xOffset, the x offset (distance) to move
	// - param 2: int yOffset, the y offset (distance) to move
	// - return: nothing
	void move(int xOffset, int yOffset);

	// Build and return a vector of Points to represent our inherited
	// blockLocs vector mapped to the gridLoc of this object instance.
	// You will need to provide this class access to blockLocs (from the Tetromino class).
	// eg: if we have a Point [x,y] in our vector,
	// and our gridLoc is [5,6] the mapped Point would be [5+x,6+y].
	// params: none:
	// return: a vector of Point objects.
	 std::vector<Point> getBlockLocsMappedToGrid() const;
	 
};

#endif /* GRIDTETROMINO_H */