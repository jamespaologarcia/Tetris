#include "Gameboard.h"
#include <iostream>
#include <iomanip>
#include <cassert>
Gameboard::Gameboard()
{
	empty();
}
void Gameboard::empty()
{
	for (int col{ 0 }; col < MAX_Y; col++)
	{
		fillRow(col, EMPTY_BLOCK);
	}
}
void Gameboard::fillRow(int rowIndex, int content)
{
	for (int x = 0; x < MAX_X; x++)
	{
		grid[rowIndex][x] = content;
	}
}
void Gameboard::printToConsole() const
{
    for (int y{ 0 }; y < MAX_Y; ++y)
    {
        for (int x{ 0 }; x < MAX_X; ++x)
        {
            if (grid[y][x] == EMPTY_BLOCK)
            {
                std::cout << '.' << std::setw(2);
            }
            else {
                std::cout << grid[y][x] << std::setw(2);
            }
        }
        std::cout << '\n';
    }
}
 int Gameboard::getContent(Point point) const
{
    assert(isValidPoint(point));
    return grid[point.getY()][point.getX()];
}
 int Gameboard::getContent(int x, int y) const
{
    assert(isValidPoint(x, y));
    return grid[y][x];
}
bool Gameboard::isValidPoint(Point point) const
{
    return (point.getY() >= 0 && point.getY() < MAX_Y && point.getX() >= 0 && point.getX() < MAX_X);
}
bool Gameboard::isValidPoint(int x, int y) const
{
    return (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y);
}
void Gameboard::copyRowIntoRow(int sourceRow, int targetRow)
{
    for (int x{ 0 }; x < MAX_X; x++)
    {
        grid[targetRow][x] = grid[sourceRow][x];
    }
}
void Gameboard::removeRow(int rowIndex)
{
    assert(rowIndex >= 0 && rowIndex < MAX_Y);

    for (int y{ rowIndex - 1 }; y >= 0; y--)
    {
        copyRowIntoRow(y, y + 1);
    }
    fillRow(0, EMPTY_BLOCK);
}

void Gameboard::removeRows(std::vector<int>& row)
{
    for (int i{ 0 }; i < row.size(); i++)
    {
        removeRow(row[i]);
    }
}
void Gameboard::setContent(int x, int y, int content) 
{
    if (isValidPoint(x, y))
    {
        grid[y][x] = content;
    }
}
void Gameboard::setContent(Point p, int content)
{
    if (isValidPoint(p))
    {
        grid[p.getY()][p.getX()] = content;
    }
    
}
void Gameboard::setContent(const std::vector<Point>& locations, int content)
{
    for (const Point& p : locations)
    {
        grid[p.getY()][p.getX()] = content;
    }
}
bool Gameboard::areAllLocsEmpty(const std::vector<Point>& locations) const
{
    for (const Point& point : locations)
    {
        if (isValidPoint(point))
        {
            if (grid[point.getY()][point.getX()] != EMPTY_BLOCK)
            {
                return false;
            }
        }
    }
    return true;
}
bool Gameboard::isRowCompleted(int row) const
{
    assert(row >= 0 && row < MAX_Y);
    for (int x{ 0 }; x < MAX_X; x++)
    {
        if (grid[row][x] == EMPTY_BLOCK)
        {
            return false;
        }
    }
    return true;
}
std::vector<int> Gameboard::getCompletedRowIndices() const
{
    std::vector<int> completedRows;

    for (int y{ 0 }; y < Gameboard::MAX_Y; y++)
    {
        if (isRowCompleted(y))
        {
            completedRows.push_back(y);
        }
    }
    return completedRows;
}
//	// Remove all completed rows from the board
//	//   use getCompletedRowIndices() and removeRows() 
//	// - params: none
//	// - return: the count of completed rows removed
int Gameboard::removeCompletedRows()
{
    std::vector<int> completedRows = getCompletedRowIndices();
    removeRows(completedRows);
    return completedRows.size();
}

Point Gameboard::getSpawnLoc()
{
    return spawnLoc;
}
