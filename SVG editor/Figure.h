#pragma once
#include<iostream>
#include <fstream>
class Figure
{
public:
	virtual void setData(std::ifstream&file)=0;
	virtual void print()const=0;
	virtual char*getName()const = 0;
	virtual void create(bool&isCreate) = 0;
	virtual void translate(int vertical, int horizontal) = 0;
	virtual bool within(char* nameFig, Figure*&BigFigure)const=0;
	virtual int*getData()const = 0;
	virtual void deserialize(std::ofstream& save)const=0;
	char *checkAttr(std::ifstream&file,char& c)const;
	int readInt(std::ifstream&file)const;
	char*readString(std::ifstream&file)const;
};

