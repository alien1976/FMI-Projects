#include "circle.h"



circle::circle()
{
	cx = 0; cy = 0; r = 0;
	fill = NULL;
}


circle::~circle()
{
	delete[]fill;
}

void circle::setData(std::ifstream & file)
{
	char c;
	file.read((char*)&c, sizeof(c));
	while (c != '/' && !file.eof())
	{
		if (c == ' ')file.read((char*)&c, sizeof(c));
		else {
			char *attr = checkAttr(file, c);
			if (!strcmp(attr, "cx"))cx = readInt(file);
			else if (!strcmp(attr, "cy"))cy = readInt(file);
			else if (!strcmp(attr, "r"))r = readInt(file);
			else if (!strcmp(attr, "fill"))fill = readString(file);
			file.read((char*)&c, sizeof(c));
			delete[]attr;
		}
	}
}

void circle::print()const
{
	std::cout << "circle " << cx << " " << cy << " " << r << " ";
	if (fill)std::cout << fill;
}

void circle::create(bool & isCreate)
{
	std::cin >> cx;
	std::cin >> cy;
	std::cin >> r;
	if (r) {
		fill = new char[50];
		std::cin >> fill;
	}
	else {
		std::cout << "Bad radius(or can't be 0)!\n";
		return;
	}
	isCreate = true;
}

void circle::translate(int vertical, int horizontal)
{
	cx += horizontal;
	cy += vertical;
}

bool circle::within(char * nameFig, Figure *& BigFigure) const
{
	if (!strcmp(nameFig, "circle"))
	{
		int *dataCircle = BigFigure->getData();
		int distance = sqrt(pow((dataCircle[0] - cx), 2) - pow((dataCircle[1] - cy), 2));
		if (r > distance + dataCircle[2])
		{
			delete[]dataCircle;
			return false;
		}
		else {
			delete[]dataCircle;
			return true;
		}
	}
	else if (!strcmp(nameFig, "rect"))
	{
		int *dataRect = BigFigure->getData();
		if (((cx - dataRect[0]) > 0 && (cx - dataRect[0]) < dataRect[2] && r <= (cx - dataRect[0])) &&
			((dataRect[1] - cy) > 0 && (dataRect[1] - cy) < dataRect[3] && r <= (dataRect[1] - cy)))
		{
			delete[]dataRect;
			return true;
		}
		else {
			delete[]dataRect;
			return false;
		}

	}
	return false;
}

void circle::deserialize(std::ofstream & save) const
{
	save << "<circle cx=\"";
	save<<cx<< "\" cy=\"";
	save<<cy << "\" r=\"";
	if (r)save <<r<< "\" fill=\"";
	else save<< "\" fill=\"";
	if(fill)save<< fill << "\" />\n";
	else save<< "\" />\n";
}
