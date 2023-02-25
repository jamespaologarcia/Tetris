#pragma once
#include "TetrisGame.h"
#include "Gameboard.h"
#include <assert.h>
#include <sstream>
#include <string>
#include <iostream>

// MEMBER FUNCTIONS

// constructor
//   initialize/assign private member vars names that match param names
//   reset() the game
//   load font from file: fonts/RedOctober.ttf
//   setup scoreText
// - params: already specified
constexpr int TetrisGame::BLOCK_WIDTH{32};			  // pixel width of a tetris block, init to 32
constexpr int TetrisGame::BLOCK_HEIGHT{32};			  // pixel height of a tetris block, init to 32
constexpr double TetrisGame::MAX_SECONDS_PER_TICK{0.75}; // the slowest "tick" rate (in seconds), init to 0.75
constexpr double TetrisGame::MIN_SECONDS_PER_TICK{0.20}; // the fastest "tick" rate (in seconds), init to 0.20

TetrisGame::TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset) 
	: window{ window }, blockSprite{ blockSprite }, gameboardOffset{ gameboardOffset }, nextShapeOffset{ nextShapeOffset } 
{
	TetrisGame::reset();
	
	currentShape.setGridLoc(board.getSpawnLoc());
	nextShapeOffset.toString();

	if (!scoreFont.loadFromFile("fonts/RedOctober.ttf"))
	{
		assert(false && "Missing font: RedOctober.ttf");
	};
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(425, 325);
}

// Draw anything to do with the game,
//   includes the board, currentShape, nextShape, score
//   called every game loop
// - params: none
// - return: nothing
void TetrisGame::draw() {
	
	drawGameboard();
	drawTetromino(currentShape, gameboardOffset);
	drawGameboard();
	window.draw(scoreText);
}

// Event and game loop processing
// handles keypress events (up, left, right, down, space)
// - param 1: sf::Event event
// - return: nothing
void TetrisGame::onKeyPressed(const sf::Event& event) {
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
		attemptRotate(currentShape);
		break;
	case sf::Keyboard::Right:
		attemptMove(currentShape, 1, 0);
		break;
	case sf::Keyboard::Left:
		attemptMove(currentShape, -1, 0);
		break;
	case sf::Keyboard::Down:
		if (!attemptMove(currentShape, 0, 1)) {
			lock(currentShape);
		}
		break;
	case sf::Keyboard::Space:
		drop(currentShape);
		lock(currentShape);
		break;
	default:
		break;
	}
}

// called every game loop to handle ticks & tetromino placement (locking)
// - param 1: float secondsSinceLastLoop
// return: nothing
void TetrisGame::processGameLoop(const float secondsSinceLastLoop) {
	secondsSinceLastTick += secondsSinceLastLoop;
	if (secondsSinceLastTick >= MAX_SECONDS_PER_TICK)
	{
		tick();
		secondsSinceLastTick -= secondsPerTick;
		
	}
	if (shapePlacedSinceLastGameLoop)
	{
		shapePlacedSinceLastGameLoop = false;
		if (spawnNextShape())
		{
			switch (board.removeCompletedRows())
			{
			case 1:
				score += SINGLE_LINE;
				updateScoreDisplay();
				break;
			case 2:
				score += DOUBLE_LINE;
				updateScoreDisplay();
				break;
			case 3:
				score += TRIPLE_LINE;
				updateScoreDisplay();
				break;
			case 4:
				score += TETRIS_LINE;
				updateScoreDisplay();
				break;
			default:
				break;
			}
			pickNextShape();
		}
		else {
			reset();
		}
	}
	
}


// A tick() forces the currentShape to move (if there were no tick,
// the currentShape would float in position forever). This should
// call attemptMove() on the currentShape.  If not successful, lock() 
// the currentShape (it can move no further).
// - params: none
// - return: nothing
	void TetrisGame::tick() {
		
		if (!TetrisGame::attemptMove(currentShape, 0, 1)) {
			TetrisGame::lock(this->currentShape);
		}
	}

	// reset everything for a new game (use existing functions) 
	//  - set the score to 0 and call updateScoreDisplay()
	//  - call determineSecondsPerTick() to determine the tick rate.
	//  - clear the gameboard,
	//  - pick & spawn next shape
	//  - pick next shape again (for the "on-deck" shape)
	// - params: none
	// - return: nothing
	void TetrisGame::reset()
	{
		score = 0;
		updateScoreDisplay();
		determineSecondsPerTick();
		board.empty();
		pickNextShape();
		spawnNextShape();
		pickNextShape();
	}

	// assign nextShape.setShape a new random shape  
	// - params: none
	// - return: nothing
	void TetrisGame::pickNextShape()
	{
		nextShape.setShape(Tetromino::getRandomShape());
	}

	// copy the nextShape into the currentShape (through assignment)
	//   position the currentShape to its spawn location.
	// - params: none
	// - return: bool, true/false based on isPositionLegal()
	bool TetrisGame::spawnNextShape() {
		currentShape = nextShape;
		currentShape.setGridLoc(board.getSpawnLoc());
		return isPositionLegal(currentShape);
	}

	// Test if a rotation is legal on the tetromino and if so, rotate it. 
	//  To accomplish this:
	//	 1) create a (local) temporary copy of the tetromino
	//	 2) rotate it (temp.rotateClockwise())
	//	 3) test if temp rotation was legal (isPositionLegal()), 
	//      if so - rotate the original tetromino.
	// - param 1: GridTetromino shape
	// - return: bool, true/false to indicate successful movement
	bool TetrisGame::attemptRotate(GridTetromino& shape) {
		GridTetromino temp{ shape };
		temp.rotateClockwise();
		if (isPositionLegal(temp) && static_cast<int>(shape.getShape()) != 4)
		{
			shape.rotateClockwise();
		}
		return true;
	}

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
	bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) {
		
		GridTetromino temp{ shape };
		temp.move(x, y);
		if (isPositionLegal(temp))
		{
			shape.move(x, y);
			return true;
		}
		return false;
	}

	// drops the tetromino vertically as far as it can 
	//   legally go.  Use attemptMove(). This can be done in 1 line.
	// - param 1: GridTetromino shape
	// - return: nothing;
	void TetrisGame::drop(GridTetromino& shape) {
		while (attemptMove(shape, 0, 1));
	}

	// copy the contents (color) of the tetromino's mapped block locs to the grid.
		//	 1) get the tetromino's mapped locs via tetromino.getBlockLocsMappedToGrid()
		//   2) use the board's setContent() method to set the content at the mapped locations.
		//   3) record the fact that we placed a shape by setting shapePlacedSinceLastGameLoop
		//      to true
		// - param 1: GridTetromino shape
		// - return: nothing
	void TetrisGame::lock(const GridTetromino& shape) {
		for (Point p : shape.getBlockLocsMappedToGrid())
		{
			board.setContent(p, static_cast<int>(shape.getColor()));
		}
		shapePlacedSinceLastGameLoop = true;
	}

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
	void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, TetColor color) const {
		//std::cout << "this is the x position" << static_cast<int>(topLeft.getX() + xOffset * BLOCK_WIDTH) << std::endl;
		//std::cout << topLeft.getX() + xOffset * BLOCK_WIDTH << " " << topLeft.getY() + yOffset * BLOCK_HEIGHT << std::endl;
		blockSprite.setPosition(topLeft.getX() + xOffset * BLOCK_WIDTH, topLeft.getY() + yOffset * BLOCK_HEIGHT);
		blockSprite.setTextureRect(sf::IntRect(static_cast<int>(color) * BLOCK_WIDTH, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
		window.draw(blockSprite);
	}

	// Draw the gameboard blocks on the window
	//   Iterate through each row & col, use drawBlock() to 
	//   draw a block if it isn't empty.
	// params: none
	// return: nothing
	void TetrisGame::drawGameboard() {
		for (int y = 0;y < Gameboard::MAX_Y; y++)
		{
			for (int x = 0; x < Gameboard::MAX_X; x++)
			{
				if (board.getContent(x, y) != Gameboard::EMPTY_BLOCK) {
					drawBlock(gameboardOffset, x, y, static_cast<TetColor>(board.getContent(x, y)));
				}
			}
		}
	}

	// Draw a tetromino on the window
	//	 Iterate through each mapped loc & drawBlock() for each.
	//   The topLeft determines a 'base point' from which to calculate block offsets
	//      If the Tetromino is on the gameboard: use gameboardOffset
	// param 1: GridTetromino tetromino
	// param 2: Point topLeft
	// return: nothing
	void TetrisGame::drawTetromino(const GridTetromino& tetromino, const Point& topLeft) {

		for (const Point& point : tetromino.getBlockLocsMappedToGrid()) {
		
			 drawBlock(topLeft, point.getX(), point.getY(), tetromino.getColor());
		}
	}

	// update the score display
	// form a string "score: ##" to display the current score
	// user scoreText.setString() to display it.
	// params: none:
	// return: nothing
	void TetrisGame::updateScoreDisplay() {
		std::stringstream msg;
		std::string message;
		msg << "Score: " << score;
		message = msg.str();

		scoreText.setString(message);
	}

	// State & gameplay/logic methods ================================

	// Determine if a Tetromino can legally be placed at its current position
	// on the gameboard.
	//   Tip: Make use of Gameboard's areLocsEmpty() and pass it the shape's mapped locs.
	// - param 1: GridTetromino shape
	// - return: bool, true if shape is within borders (isShapeWithinBorders()) and 
	//           the shape's mapped board locs are empty (false otherwise).
	bool  TetrisGame::isPositionLegal(const GridTetromino& shape) const {

		return board.areAllLocsEmpty(shape.getBlockLocsMappedToGrid()) && isWithinBorders(shape);
	}


	// Determine if the shape is within the left, right, & bottom gameboard borders
	//   * Ignore the upper border because we want shapes to be able to drop
	//     in from the top of the gameboard.
	//   All of a shape's blocks must be inside these 3 borders to return true
	// - param 1: GridTetromino shape
	// - return: bool, true if the shape is within the left, right, and lower border
	//	         of the grid, but *NOT* the top border (false otherwise)
	bool TetrisGame::isWithinBorders(const GridTetromino& shape) const {
		for (Point p : shape.getBlockLocsMappedToGrid())
		{
			if (p.getX() < 0 || p.getX() >= Gameboard::MAX_X ||  p.getY() >= Gameboard::MAX_Y)
			{
				return false;
			}
		}
		return true;
	}


	// set secsPerTick 
	//   - basic: use MAX_SECS_PER_TICK
	//   - advanced: base it on score (higher score results in lower secsPerTick)
	// params: none
	// return: nothing
	void TetrisGame::determineSecondsPerTick() {
		secondsPerTick = MAX_SECONDS_PER_TICK;
	}