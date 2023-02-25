// This class encapsulates the tetris game and its drawing routines, gameplay, & control logic.
// This class was designed so with the idea of potentially instantiating 2 of them
// and have them run side by side (player vs player).
// So, anything you would need for an individual tetris game has been included here.
// Anything you might use between games (like the background, or the sprite used for 
// rendering a tetromino block) was left in main.cpp
// 
// This class is responsible for:
//   - setting up the board,
//	 - drawing game elements to the screen
//   - spawning tetrominoes,
//   - handling user input,
//   - moving and placing tetrominoes 
//
//  [expected .cpp size: ~ 275 lines]

#ifndef TETRISGAME_H
#define TETRISGAME_H

#include "Gameboard.h"
#include "GridTetromino.h"
#include <SFML/Graphics.hpp>


class TetrisGame
{
public:
	// STATIC CONSTANTS
	static const int BLOCK_WIDTH;			  // pixel width of a tetris block, init to 32
	static const int BLOCK_HEIGHT;			  // pixel height of a tetris block, int to 32
	static const double MAX_SECONDS_PER_TICK; // the slowest "tick" rate (in seconds), init to 0.75
	static const double MIN_SECONDS_PER_TICK; // the fastest "tick" rate (in seconds), init to 0.20
	const int SINGLE_LINE{ 40 };
	const int DOUBLE_LINE{ 100 };
	const int TRIPLE_LINE{ 300 };
	const int TETRIS_LINE{ 1200 };

private:	
	// MEMBER VARIABLES

	// State members ---------------------------------------------
	int score;					// the current game score.
    Gameboard board;			// the gameboard (grid) to represent where all the blocks are.
    GridTetromino nextShape;	// the tetromino shape that is "on deck".
    GridTetromino currentShape;	// the tetromino that is currently falling.
	
	// Graphics members ------------------------------------------
	sf::Sprite& blockSprite;		// the sprite used for all the blocks.
	sf::RenderWindow& window;		// the window that we are drawing on.
	const Point gameboardOffset;	// pixel XY offset of the gameboard on the screen
	const Point nextShapeOffset;	// pixel XY offset to the nextShape

	sf::Font scoreFont;				// SFML font for displaying the score.
	sf::Text scoreText;				// SFML text object for displaying the score
									
	// Time members ----------------------------------------------
	// Note: a "tick" is the amount of time it takes a block to fall one line.
	double secondsPerTick = MAX_SECONDS_PER_TICK; // the seconds per tick (changes depending on score)	

	double secondsSinceLastTick{ 0.0 };			// update this every game loop until it is >= secsPerTick,
												// we then know to trigger a tick.  Reduce this var (by a tick) & repeat.
	bool shapePlacedSinceLastGameLoop{ false };	// Tracks whether we have placed (locked) a shape on
												// the gameboard in the current gameloop	
public:
	// MEMBER FUNCTIONS

	// constructor
	//   initialize/assign private member vars names that match param names
	//   reset() the game
	//   load font from file: fonts/RedOctober.ttf
	//   setup scoreText
	// - params: already specified
	TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset);

	// Draw anything to do with the game,
	//   includes the board, currentShape, nextShape, score
	//   called every game loop
	// - params: none
	// - return: nothing
	void draw();

	// Event and game loop processing
	// handles keypress events (up, left, right, down, space)
	// - param 1: sf::Event event
	// - return: nothing
	void onKeyPressed(const sf::Event& event);

	// called every game loop to handle ticks & tetromino placement (locking)
	// - param 1: float secondsSinceLastLoop
	// return: nothing
	void processGameLoop(const float secondsSinceLastLoop);

	// A tick() forces the currentShape to move (if there were no tick,
	// the currentShape would float in position forever). This should
	// call attemptMove() on the currentShape.  If not successful, lock() 
	// the currentShape (it can move no further).
	// - params: none
	// - return: nothing
	void tick();

private:
	// reset everything for a new game (use existing functions) 
	//  - set the score to 0 and call updateScoreDisplay()
	//  - call determineSecondsPerTick() to determine the tick rate.
	//  - clear the gameboard,
	//  - pick & spawn next shape
	//  - pick next shape again (for the "on-deck" shape)
	// - params: none
	// - return: nothing
	void reset();

	// assign nextShape.setShape a new random shape  
	// - params: none
	// - return: nothing
	void pickNextShape();
	
	// copy the nextShape into the currentShape (through assignment)
	//   position the currentShape to its spawn location.
	// - params: none
	// - return: bool, true/false based on isPositionLegal()
	bool spawnNextShape();																	

	// Test if a rotation is legal on the tetromino and if so, rotate it. 
	//  To accomplish this:
	//	 1) create a (local) temporary copy of the tetromino
	//	 2) rotate it (temp.rotateClockwise())
	//	 3) test if temp rotation was legal (isPositionLegal()), 
	//      if so - rotate the original tetromino.
	// - param 1: GridTetromino shape
	// - return: bool, true/false to indicate successful movement
	bool attemptRotate(GridTetromino& shape);
   
	// test if a move is legal on the tetromino, if so, move it.
	//  To do this:
	//	 1) create a (local) temporary copy of the tetromino
	//	 2) move it (temp.move())
	//	 3) test if temp move was legal (isPositionLegal(),
	//      if so - move the original.	
	// - param 1: GridTetromino shape
	// - param 2: int x;
	// - param 3: int y;
	// - return: true/false to indicate successful movement
	bool attemptMove(GridTetromino& shape, int x, int y);

	// drops the tetromino vertically as far as it can 
	//   legally go.  Use attemptMove(). This can be done in 1 line.
	// - param 1: GridTetromino shape
	// - return: nothing;
	void drop(GridTetromino& shape);

	// copy the contents (color) of the tetromino's mapped block locs to the grid.
		//	 1) get the tetromino's mapped locs via tetromino.getBlockLocsMappedToGrid()
		//   2) use the board's setContent() method to set the content at the mapped locations.
		//   3) record the fact that we placed a shape by setting shapePlacedSinceLastGameLoop
		//      to true
		// - param 1: GridTetromino shape
		// - return: nothing
	void lock(const GridTetromino& shape);
	
	// Graphics methods ==============================================
	
	// Draw a tetris block sprite on the canvas		
	// The block position is specified in terms of 2 offsets: 
	//    1) the top left (of the gameboard in pixels)
	//    2) an x & y offset into the gameboard - in blocks (not pixels)
	//       meaning they need to be multiplied by BLOCK_WIDTH and BLOCK_HEIGHT
	//       to get the pixel offset.
	//	 1) set the block color using blockSprite.setTextureRect()
	//   2) set the block location using blockSprite.setPosition()   
	//	 3) draw the block using window.draw()
	//   For details/instructions on these 3 operations see:
	//       www.sfml-dev.org/tutorials/2.5/graphics-sprite.php
	//       use member variables: window and blockSprite (assigned in constructor)
	// param 1: Point topLeft
	// param 2: int xOffset
	// param 3: int yOffset
	// param 4: TetColor color
	// return: nothing
	void drawBlock(const Point& topLeft, int xOffset, int yOffset, TetColor color) const;
										
	// Draw the gameboard blocks on the window
	//   Iterate through each row & col, use drawBlock() to 
	//   draw a block if it isn't empty.
	// params: none
	// return: nothing
	void drawGameboard();
	
	// Draw a tetromino on the window
	//	 Iterate through each mapped loc & drawBlock() for each.
	//   The topLeft determines a 'base point' from which to calculate block offsets
	//      If the Tetromino is on the gameboard: use gameboardOffset
	// param 1: GridTetromino tetromino
	// param 2: Point topLeft
	// return: nothing
	void drawTetromino(const GridTetromino& tetromino,const Point& topLeft);
	
	// update the score display
	// form a string "score: ##" to display the current score
	// user scoreText.setString() to display it.
	// params: none:
	// return: nothing
	void updateScoreDisplay();

	// State & gameplay/logic methods ================================

	// Determine if a Tetromino can legally be placed at its current position
	// on the gameboard.
	//   Tip: Make use of Gameboard's areLocsEmpty() and pass it the shape's mapped locs.
	// - param 1: GridTetromino shape
	// - return: bool, true if shape is within borders (isShapeWithinBorders()) and 
	//           the shape's mapped board locs are empty (false otherwise).
	bool isPositionLegal(const GridTetromino& shape) const;

	
	// Determine if the shape is within the left, right, & bottom gameboard borders
	//   * Ignore the upper border because we want shapes to be able to drop
	//     in from the top of the gameboard.
	//   All of a shape's blocks must be inside these 3 borders to return true
	// - param 1: GridTetromino shape
	// - return: bool, true if the shape is within the left, right, and lower border
	//	         of the grid, but *NOT* the top border (false otherwise)
	bool isWithinBorders(const GridTetromino& shape) const;


	// set secsPerTick 
	//   - basic: use MAX_SECS_PER_TICK
	//   - advanced: base it on score (higher score results in lower secsPerTick)
	// params: none
	// return: nothing
	void determineSecondsPerTick();
	friend class TestSuite;

};

#endif /* TETRISGAME_H */

