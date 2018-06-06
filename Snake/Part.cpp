#include <iostream>
#include "Part.h"

Part::Part()
{
	c = 'o';
	x = 0;
	y = 0;
	points = 0;
}

Part & Part::operator=(const Part & rhs)
{
	if (this == &rhs)return *this;
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}


Part::~Part()
{
}

bool Part::operator==(const Part & rhs)
{
	if (this->x == rhs.y && this->y == rhs.x)return true;
	return false;
}

void Part::setXY(int x,int y)
{
	this->x = x;
	this->y = y;
}

void Part::setPoints()
{
	this->points = rand() % 100 + 50;
}

void Part::move(int x, int y)
{
	this->x += x;
	this->y += y;
}
