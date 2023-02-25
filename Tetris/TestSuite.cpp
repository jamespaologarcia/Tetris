#include "TestSuite.h"

#ifdef POINT
#include "Point.h"
#endif

#ifdef TETROMINO
#include "Tetromino.h"
#endif 

#ifdef GAMEBOARD
#include "Gameboard.h"
#endif

#ifdef GRIDTETROMINO
#include "GridTetromino.h"
#endif

#include <cassert>
#include <iostream>
#include <string>



void TestSuite::runTestSuite()
{
	std::cout << "=== Running TestSuite =========================" << "\n";
	// run some sanity tests on our classes to ensure they're working as expected.
	//std::cout << "uncomment the #define statements in TestSuite.h when ready to test.\n\n";
	testPointClass();
	testTetrominoClass();
	testGameboardClass();
	testGridTetrominoClass();
	std::cout << "=== TestSuite complete ========================" << "\n\n";
}

void TestSuite::announceTest(const std::string& className) {
	std::cout << "Testing " << className << " class...";
}

void TestSuite::announceTestCompletion() {
	std::cout << "passed!\n\n";
}

void TestSuite::announceNotTested(const std::string& className)
{
	std::cout << "Class not tested: " << className << ".  ";
	std::cout << "(uncomment #define ";
	// convert to uppercase
	for (int i = 0; i < className.length(); i++)
	{
		char ucChar = className[i];
		if (ucChar >= 'a' && ucChar <= 'z') {
			ucChar = ucChar - ('a' - 'A');
		}
		std::cout << ucChar;
	}
	std::cout << " in TestSuite.h to test)\n\n";
}





void TestSuite::testPointClass()
{
#ifdef POINT
	announceTest("Point");
	//std::cout << "testPointClass()...\n";

	Point p;

	// test our initial values are 0,0
	assert(p.getX() == 0 && "Point ctor - x not initialized to 0");
	assert(p.getY() == 0 && "Point ctor - y not initialized to 0");

	// test setX()
	p.setX(1);
	assert(p.getX() == 1 && "Point::setX() failed");
	p.setX(-1);
	assert(p.getX() == -1 && "Point::setX() failed");

	// test setY()
	p.setY(2);
	assert(p.getY() == 2 && "Point::setY() failed");
	p.setY(-2);
	assert(p.getY() == -2 && "Point::setY() failed");

	// test setXY()
	p.setXY(3, 4);
	assert(p.getX() == 3 && p.getY() == 4 && "Point::setXY() failed");
	p.setXY(-3, -4);
	assert(p.getX() == -3 && p.getY() == -4 && "Point::setXY() failed");

	// test constructor with 2 params
	Point q(3, 4);
	assert(q.getX() == 3 && q.getY() == 4 && "Point::ctor failed to set default params");

	// test swapXY()
	q.swapXY();
	assert(q.getX() == 4 && q.getY() == 3 && "Point::swapXY() failed");

	// test multiplyX()
	q.multiplyX(-1);
	assert(q.getX() == -4 && "Point::multiplyX() failed");

	// test multiplyY()
	q.multiplyY(-1);
	assert(q.getY() == -3 && "Point::multiplyY() failed");

	// test copy constructor
	q.setXY(1, 2);
	Point r = q;
	assert(r.getX() == q.getX() && r.getY() == q.getY() && "Point copy ctor failed");
	r.setXY(3, 4);
	assert(r.getX() == 3 && r.getY() == 4
		&& q.getX() == 1 && q.getY() == 2 && "Point::setXY() failed");

	Point s{ 5,6 };
	std::cout << "expected:\t[5,6]\n";
	std::cout << "actual: \t" << s.toString() << "\n";

	// ensure const methods are actually const
	// These lines will cause compile time errors you have methods in your Point class that
	// should be labelled as const (because the methods don't change the internal member
	// variables of yoru class).
	// The solution: make these const methods!  (see LearnCpp 13.2- const class objects and member functions)
	const Point cPoint{};
	cPoint.getX();
	cPoint.getY();
	cPoint.toString();

	announceTestCompletion();
#else
	announceNotTested("Point");
#endif

}



void TestSuite::testTetrominoClass()
{
#ifdef TETROMINO
	announceTest("Tetromino");

	Tetromino t;


	assert(t.getColor() == TetColor::RED ||
		t.getColor() == TetColor::ORANGE ||
		t.getColor() == TetColor::YELLOW ||
		t.getColor() == TetColor::GREEN ||
		t.getColor() == TetColor::BLUE_LIGHT ||
		t.getColor() == TetColor::BLUE_DARK ||
		t.getColor() == TetColor::PURPLE &&
		"default Tetromino not initialized to valid color.");

	assert(t.getShape() == TetShape::S ||
		t.getShape() == TetShape::Z ||
		t.getShape() == TetShape::L ||
		t.getShape() == TetShape::J ||
		t.getShape() == TetShape::O ||
		t.getShape() == TetShape::I ||
		t.getShape() == TetShape::T &&
		"default Tetromino not initialized to valid shape.");

	int blockcount = BLOCK_COUNT;

	assert(t.blockLocs.size() == blockcount &&
		"default Tetromino has no blockLocs - likely because no default set in constructor");

	t.setShape(TetShape::S);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be: 4");
	t.setShape(TetShape::Z);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");
	t.setShape(TetShape::L);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");
	t.setShape(TetShape::J);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");
	t.setShape(TetShape::O);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");
	t.setShape(TetShape::I);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");
	t.setShape(TetShape::T);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");


	// test the rotate functionality of a single block
	t.blockLocs.clear();
	t.blockLocs.push_back(Point(1, 2));
	t.rotateClockwise();
	assert(t.blockLocs[0].getX() == 2 && t.blockLocs[0].getY() == -1 && "Tetromino::rotateClockwise() failed");
	t.rotateClockwise();
	assert(t.blockLocs[0].getX() == -1 && t.blockLocs[0].getY() == -2 && "Tetromino::rotateClockwise() failed");
	t.rotateClockwise();
	assert(t.blockLocs[0].getX() == -2 && t.blockLocs[0].getY() == 1 && "Tetromino::rotateClockwise() failed");
	t.rotateClockwise();
	assert(t.blockLocs[0].getX() == 1 && t.blockLocs[0].getY() == 2 && "Tetromino::rotateClockwise() failed");

	// ensure const methods are actually const
	// These lines will cause compile time errors you have methods in your Tetromino class that
	// should be labelled as const (because the methods don't change the internal member
	// variables of yoru class).
	// (see LearnCpp 13.2- const class objects and member functions)
	const Tetromino cTetromino;
	cTetromino.printToConsole();
	cTetromino.getColor();
	cTetromino.getShape();

	// Test const 
	announceTestCompletion();
#else
	announceNotTested("Tetromino");
#endif

}

#ifdef GAMEBOARD
bool isGameboardEmpty(Gameboard& g)
{
	for (int x = 0; x < Gameboard::MAX_X; x++) {
		for (int y = 0; y < Gameboard::MAX_Y; y++)
		{
			if (g.getContent(x, y) != Gameboard::EMPTY_BLOCK) { return false; }
		}
	}
	return true;
}
#endif


void TestSuite::testGameboardClass()
{
#ifdef GAMEBOARD
	announceTest("Gameboard");
	Gameboard g;
	// test if grid content is initialized to empty blocks
	for (int x = 0; x < Gameboard::MAX_X; x++) {
		for (int y = 0; y < Gameboard::MAX_Y; y++) {
			assert(g.getContent(x, y) == Gameboard::EMPTY_BLOCK && "Gameboard was not initialized with empty blocks");
		}
	}

	// test setGridContent()
	g.setContent(0, 0, 1);
	assert(g.getContent(0, 0) == 1 && "Gameboard.setContent() - unexpected result");	// was grid content set?
	g.setContent(Gameboard::MAX_X - 1, Gameboard::MAX_Y - 1, 2);
	assert(g.getContent(Gameboard::MAX_X - 1, Gameboard::MAX_Y - 1) == 2 &&
		"Gameboard.setContent() - unexpected result"); // was grid content set?
	g.setContent(Gameboard::MAX_X - 1, Gameboard::MAX_Y - 1, Gameboard::EMPTY_BLOCK);
	assert(g.getContent(Gameboard::MAX_X - 1, Gameboard::MAX_Y - 1) == Gameboard::EMPTY_BLOCK &&
		"Gameboard.setContent() - unexpected result"); // was grid content set?


	// test fillRow() & isRowCompleted()
	g.fillRow(0, 1);
	assert(g.getContent(0, 0) == 1 &&
		"Gameboard.fillRow() - row should be filled with 1, but first element is not 1");	// is the first spot in the row what we expect?
	assert(g.getContent(Gameboard::MAX_X - 1, 0) == 1 &&
		"Gameboard.fillRow() - row should be filled, but last element is still 1");  // is the last spot in the row what we expect?
	assert(g.isRowCompleted(0) == true &&
		"Gameboard.fillRow() - row should be filled, but does not appear to be completed");	// was row 0 completed?

	// test isRowCompleted()
	g.setContent(0, 0, Gameboard::EMPTY_BLOCK);
	assert(g.isRowCompleted(0) == false &&
		"Gameboard.isRowCompleted() clearing a single entry should make row incomplete");	// did a single incomplete entry make the row incomplete?

	// test clearRow()
	g.fillRow(0, 1);
	assert(g.isRowCompleted(0) == true &&
		"Gameboard.fillRow() - row should be filled with 1, but does not appear to be completed");	// ensure row filled
	g.fillRow(0, Gameboard::EMPTY_BLOCK);
	assert(g.isRowCompleted(0) == false &&
		"Gameboard.fillRow() - row should be empty, but appears to be completed");	// did row 0 get cleared

	// test isEmpty
	g.empty();
	assert(isGameboardEmpty(g) == true && "Gameboard.isGameboardEmpty() returned false when true expected");
	g.setContent(0, 0, 1);
	assert(isGameboardEmpty(g) == false && "Gameboard.isGameboardEmpty() returned true when false expected");
	g.empty();
	assert(isGameboardEmpty(g) == true && "Gameboard.isGameboardEmpty() returned false when true expected");

	// test empty()
	for (int y = 0; y < Gameboard::MAX_Y; y++) {	// fill the whole board
		g.fillRow(y, 1);
	}
	g.empty();	// empty the board
	assert(isGameboardEmpty(g) == true &&
		"Gameboard.isGameboardEmpty() returned false when true expected"); // verify the board is empty

	// test copyRowIntoRow()
	g.empty();
	assert(g.isRowCompleted(1) == false);
	for (int x = 0; x < Gameboard::MAX_X; x++) {  // fill row 0 with 0, 1, 2, 3,...
		g.setContent(x, 1, x);
	}
	g.copyRowIntoRow(1, 3);					// copy row 0 into row 1
	assert(g.isRowCompleted(3) == true);	// row 3 should now be completed
	for (int x = 0; x < Gameboard::MAX_X; x++) {
		assert(g.getContent(x, 1) == g.getContent(x, 3) &&
			"Gameboard.copyRowIntoRow(), rows expected to match but do not"); // compare row 1 with row 3, does it match?
	}

	// test removeRow()
	g.fillRow(0, 0);
	g.fillRow(1, 1);
	g.fillRow(2, 2);
	g.removeRow(2);
	assert(g.getContent(0, 0) == Gameboard::EMPTY_BLOCK && "Gameboard.removeRow() expected row to be empty, but it is not");
	assert(g.getContent(0, 1) == 0 && "Gameboard.removeRow() expected row to be empty, but it is not");
	assert(g.getContent(0, 2) == 1 && "Gameboard.removeRow() expected row to be empty, but it is not");

	// test removeRows()
	g.empty();
	g.fillRow(0, 0);
	g.fillRow(1, 1);
	g.fillRow(2, 2);
	g.fillRow(3, 3);
	g.fillRow(4, 4);
	std::vector<int> rowsToRemove = { 1, 3 };
	g.removeRows(rowsToRemove);
	assert(g.getContent(0, 0) == Gameboard::EMPTY_BLOCK && "Gameboard.removeRows() seems to have failed");
	assert(g.getContent(0, 1) == Gameboard::EMPTY_BLOCK && "Gameboard.removeRows() seems to have failed");
	assert(g.getContent(0, 2) == 0 && "Gameboard.removeRows() seems to have failed");
	assert(g.getContent(0, 3) == 2 && "Gameboard.removeRows() seems to have failed");
	assert(g.getContent(0, 4) == 4 && "Gameboard.removeRows() seems to have failed");

	// test getCompletedRowIndices()
	g.empty();
	assert(g.getCompletedRowIndices().size() == 0 &&
		"Gameboard.getCompletedRowIndices() should be empty");
	g.fillRow(2, 1);	// complete row 2
	g.fillRow(4, 1);	// complete row 4
	std::vector<int> completedRows = g.getCompletedRowIndices();
	// did it return the right rows?
	assert(completedRows.size() == 2 && completedRows[0] == 2 && completedRows[1] == 4 &&
		"Gameboard.getCompletedRowIndices() does not return expected results");

	// test removeCompletedRows()
	g.empty();
	assert(g.removeCompletedRows() == 0 && "Gameboard.removeCompletedRows() should return 0");
	g.fillRow(1, 2);
	g.fillRow(3, 2);
	assert(g.removeCompletedRows() == 2 && "Gameboard.removeCompletedRows() should return 2");
	assert(isGameboardEmpty(g) == true && "Gameboard.isGameboardEmpty() should return true");

	// test if a row gets moved down by removeCompletedRows()
	g.empty();
	g.fillRow(0, 0);
	g.fillRow(1, 1);
	g.fillRow(2, 2);
	g.fillRow(3, 3);
	g.setContent(0, 0, Gameboard::EMPTY_BLOCK);
	g.setContent(0, 1, Gameboard::EMPTY_BLOCK);
	g.setContent(0, 2, Gameboard::EMPTY_BLOCK);
	// at this point row 3 is the only complete row
	g.removeCompletedRows();
	assert(g.getContent(1, 0) == Gameboard::EMPTY_BLOCK && "Gameboard.removeCompletedRows() first row should be empty");
	assert(g.getContent(1, 1) == 0 && "Gameboard.removeCompletedRows() unexpected results");	// row 0 copied into row 1
	assert(g.getContent(1, 2) == 1 && "Gameboard.removeCompletedRows() unexpected results");	// row 1 copied into row 2
	assert(g.getContent(1, 3) == 2 && "Gameboard.removeCompletedRows() unexpected results");	// row 2 copied into row 3
	assert(g.getContent(1, 4) == Gameboard::EMPTY_BLOCK && "Gameboard.removeCompletedRows() unexpected results");	// row 4 is still empty


	// test areLocsEmpty()
	g.empty();
	g.fillRow(2, 2);
	std::vector<Point> testPoints;
	testPoints.push_back(Point(0, 0));
	testPoints.push_back(Point(1, 1));
	testPoints.push_back(Point(3, 3));
	assert(g.areAllLocsEmpty(testPoints) == true &&
		"Gameboard.areAllLocsEmpty() expected true but was false");  // should return true since all points are empty
	testPoints.push_back(Point(2, 2));
	assert(g.areAllLocsEmpty(testPoints) == false &&
		"Gameboard.areAllLocsEmpty() expected false but was true");  // should return false since 2,2 contains content 2

	// throw some invalid points at areLocsEmpty and see if it ignores them
	g.empty();
	std::vector<Point> invalidPoints = { Point(-3,-20), Point(200, 23), Point(-30, 150) };
	assert(g.areAllLocsEmpty(invalidPoints) == true && "Gameboard.areAllLocsEmpty() expected true but was false");

	std::vector<Point> mixedPoints1 = { Point(-3,-20), Point(200, 23), Point(6, 6), Point(5,5) };
	assert(g.areAllLocsEmpty(mixedPoints1) == true && "Gameboard.areAllLocsEmpty() expected true but was false");

	g.fillRow(3, 3);
	std::vector<Point> mixedPoints2 = { Point(-3,-20), Point(200, 23), Point(6, 6), Point(3,3) };
	assert(g.areAllLocsEmpty(mixedPoints2) == false && "Gameboard.areAllLocsEmpty() expected false but was true");

	// lastly do a visual printout of an empty board
	g.empty();
	g.printToConsole();
	std::cout << "\n";
	// print out the board with filled in rows)
	for (int y = 0; y < Gameboard::MAX_Y; y++)
	{
		g.fillRow(y, y % 10);
	}
	g.printToConsole();
	std::cout << "\n";
	// print out the board with completed rows removed (should be empty)
	g.removeCompletedRows();
	g.printToConsole();

	// ensure methods that should be const are actually const
	// These lines will cause compile time errors if you have methods in your Gameboard class that
	// should be labelled as const (because the methods don't change the internal member
	// variables of yoru class).
	// (see LearnCpp 13.2- const class objects and member functions)
	const Gameboard g2;
	g2.getContent(0, 0);
	g2.getContent(Point(1, 1));
	std::vector<Point> pts = { Point(2,2) };
	g2.areAllLocsEmpty(pts);
	g2.printToConsole();
	g2.isRowCompleted(2);
	g2.getCompletedRowIndices();
	g2.isValidPoint(1, 1);
	g2.isValidPoint(Point(3, 3));


	// These methods should ignore invalid points
	// undefined behaviour would result if they didn't.
	Gameboard g3;
	std::cout << "Testing gameboard.setContent() methods()...";
	g3.setContent(-1, -1, 1);
	g3.setContent(25, 25, 1);
	g3.setContent(Point(-1, -1), 1);
	g3.setContent(Point(25, 25), 1);
	std::vector<Point> invalidPoints2{ Point(-5,-5), Point(50,50) };
	g3.setContent(invalidPoints2, 1);


	announceTestCompletion();
#else
	announceNotTested("Gameboard");
#endif	
}



void TestSuite::testGridTetrominoClass()
{
#ifdef GRIDTETROMINO
	std::cout << "testGridTetrominoClass...\n";

	GridTetromino gt;

	// check if constructor sets gridLoc to 0,0
	assert(gt.getGridLoc().getX() == 0 && gt.getGridLoc().getY() == 0);

	// test setGridLoc(x,y)
	gt.setGridLoc(4, 5);
	assert(gt.getGridLoc().getX() == 4 && gt.getGridLoc().getY() == 5);

	// test setGridLoc(Point)
	gt.setGridLoc(Point(8, 9));
	assert(gt.getGridLoc().getX() == 8 && gt.getGridLoc().getY() == 9);

	// test move()
	gt.setGridLoc(1, 2);
	gt.move(5, 5);
	assert(gt.getGridLoc().getX() == 6 && gt.getGridLoc().getY() == 7);


	// test getBlockLocsMappedToGrid()
	gt.blockLocs = { Point(1,2) };
	gt.setGridLoc(5, 5);
	std::vector<Point> locs = gt.getBlockLocsMappedToGrid();
	assert(locs[0].getX() == 6 && locs[0].getY() == 7);

	// A const gridTetromino should be able to call the following methods
	// (since these methods don't change the state of the class)
	// If these stop you from compiling, it is because you haven't labelled these
	// methods as const.
	const GridTetromino gt2;
	gt2.getGridLoc();
	gt2.getBlockLocsMappedToGrid();

	// a gridTetromino should still be able to access methods from the Tetromino class.
	gt2.getColor();

	announceTestCompletion();
#else
	announceNotTested("GridTetromino");
#endif	
}