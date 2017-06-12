#pragma once
#include "Figure.h"
class rectangle :
	public Figure
{
public:
	rectangle();
	virtual ~rectangle();
public:
	virtual void setData(std::ifstream& file);
	virtual void print()const;
	virtual char*getName()const { return "rectangle"; }
	virtual void create(bool&isCreate);
	virtual void translate(int vertical, int horizontal);
	virtual bool within(char* nameFig, Figure*&BigFigure)const;
	virtual int* getData()const { 
		int *data = new int[4];
		data[0] = x; data[1] = y; data[2] = width; data[3] = height;
		return data;
	}
	virtual void deserialize(std::ofstream& save)const;
private:
	int x, y,width,height;
	char *fill;
};

