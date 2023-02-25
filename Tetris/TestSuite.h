#ifndef TESTSUITE_H
#define TESTSUITE_H

// This class runs some automated testing for Point and Tetromino classes
// Two steps are required to activate it:
// 1) Call TestSuite::runTestSuite() from main()
// 2) Uncomment the #define statements directly below:
//-----------------------------------------------------------------------
#define POINT
#define TETROMINO
#define GAMEBOARD
#define GRIDTETROMINO

#include <string>

class TestSuite {

private:
	static const int BLOCK_COUNT{ 4 };	// # of blocks in a Tetromino
	static void testPointClass();		// tests for the Point class
	static void testTetrominoClass();	// tests for the Tetromino class
	static void testGameboardClass();
	static void testGridTetrominoClass(); // tests for the GridTetromino class

	static void announceTest(const std::string& className);
	static void announceTestCompletion();
	static void announceNotTested(const std::string& className);

public:
	// This will run a series of tests on the Point and Tetromino classes
	// when the #define statements at the top of this file are active.
	static void runTestSuite();
};


#endif // !TESTSUITE_H
