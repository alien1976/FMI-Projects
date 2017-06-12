#pragma once
#include "Figure.h"
class circle :
	public Figure
{
public:
	circle();
	virtual ~circle();
public:
	virtual void setData(std::ifstream& file);
	virtual void print()const;
	virtual char*getName()const { return "circle"; }
	virtual void create(bool&isCreate);
	virtual void translate(int vertical, int horizontal);
	virtual bool within(char* nameFig, Figure*&BigFigure)const;
	virtual int* getData()const {
		int *data = new int[3];
		data[0] = cx; data[1] = cy; data[2] = r; 
		return data;
	}
	virtual void deserialize(std::ofstream& save)const;
private:
	int cx, cy, r;
	char *fill;
};

