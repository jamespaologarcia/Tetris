#include "Tetromino.h"
#include <iostream>
#include <ctime>
Tetromino::Tetromino()
{
	setShape(TetShape::L);
}
TetColor Tetromino::getColor() const
{
	return color;
}
TetShape Tetromino::getShape() const
{
	return shape;
}
void Tetromino::setShape(TetShape shape)
{

	this->shape = shape;
	color = static_cast<TetColor>(shape);
	switch (shape)
	{
		case TetShape::O:
		{
			blockLocs = { Point{0, 0}, Point{1, 1}, Point{0, 1}, Point{1, 0} };
			break;
		}
		case TetShape::I:
		{
			blockLocs = { Point{0, 0}, Point{0, -1}, Point{0, 1}, Point{0, 2} };
			break;
		}
		case TetShape::S:
		{
			blockLocs = { Point{0, 0}, Point{-1, 0}, Point{0, 1}, Point{1, 1} };
			break;
		}
		case TetShape::Z:
		{
			blockLocs = { Point{0, 0}, Point{0, 1}, Point{-1, 1}, Point{1, 0} };
			break;
		}
		case TetShape::L:
		{
			blockLocs = { Point{0, 0}, Point{0, -1}, Point{1, -1}, Point{0, 1} };
			break;
		}
		case TetShape::J:
		{
			blockLocs = { Point{0, 0}, Point{0, -1}, Point{-1,-1}, Point{0, 1} };
			break;
		}
		case TetShape::T:
		{
			blockLocs = { Point{0, 0}, Point{-1, 0}, Point{1, 0}, Point{0, -1} };
			break;
		}
	}
}
TetShape Tetromino::getRandomShape(){
	
	int randShape = rand() % static_cast<int>(TetShape::COUNT);
	return static_cast<TetShape>(randShape);
}
void Tetromino::rotateClockwise()
{
	for (Point& point : blockLocs) {
		point.multiplyX(-1);
		point.swapXY();
	}
}
void Tetromino::printToConsole() const
{

	for (int y = 3; y >= -3; y--)
	{
		std::cout << '\n';
		for (int x = -3; x <= 3; x++)
		{
			char entry = '.';
			for (Point point : blockLocs) {
				point.multiplyX(-1);
				point.swapXY();
				if (point.getX() == x and point.getY() == y)
				{
					entry = 'x';
				}
			}
			std::cout << entry;
			

		}
	}
	std::cout << '\n';

	//std::cout << Tetromino::blockLocs[0].toString();
}