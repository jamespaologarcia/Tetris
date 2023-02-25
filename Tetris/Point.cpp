#include "Point.h"
#include <sstream>
Point::Point()
{

}
Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}
int Point::getX() const
{
	return this->x;
}
int Point::getY() const
{
	return this->y;
}
void Point::setX(int x)
{
	this->x = x;
}
void Point::setY(int y)
{
	this->y = y;
}
void Point::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Point::multiplyX(int factor)
{
	x = x * factor;
}
void Point::multiplyY(int factor)
{
	y = y * factor;
}
void Point::swapXY()
{
	int temp = x;
	x = y;
	y = temp;

}
std::string Point::toString() const
{
	//std::stringstream ss;
	//ss << '[' << x << ',' + y << ']';
	//return ss.str();
	//std::string returnValue = "[" + static_cast<char>(x) + 'a' + static_cast<char>(y) + ']';
	//return returnValue;
	const std::string returnString{ "[" + std::to_string(getX()) + "," + std::to_string(getY()) + "]" };
	return returnString;
}