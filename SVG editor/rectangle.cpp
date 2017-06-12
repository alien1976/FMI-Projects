#include "rectangle.h"



rectangle::rectangle()
{
	x = 0; y = 0; width = 0; height = 0;
	fill = NULL;
}


rectangle::~rectangle()
{
	delete[]fill;
}

void rectangle::setData(std::ifstream & file)
{
	char c;
	//file.seekg(-1, std::ios::cur);
	file.read((char*)&c, sizeof(c));
	while (c != '/' && !file.eof())
	{
		if (c == ' ')file.read((char*)&c, sizeof(c));
		else {
			char *attr = checkAttr(file, c);
			if (!strcmp(attr, "x"))x = readInt(file);
			else if (!strcmp(attr, "y"))y = readInt(file);
			else if (!strcmp(attr, "width"))width = readInt(file);
			else if (!strcmp(attr, "height"))height = readInt(file);
			else if (!strcmp(attr, "fill"))fill = readString(file);
			file.read((char*)&c, sizeof(c));
			delete[]attr;
		}
	}
}

void rectangle::print()const
{
	std::cout << "rectangle " << x << " " << y << " " << width << " " << height << " ";
	if (fill)std::cout << fill;
}

void rectangle::create(bool&isCreate)
{
	std::cin >> x;
	std::cin >> y;
	std::cin >> width;
	if (width)std::cin >> height;
	else {
		std::cout << "Bad width(or can't be 0)!\n";
		return;
	}
	if (height)
	{
		fill = new char[50];
		std::cin >> fill;
	}
	else {
		std::cout << "Bad height(or can't be 0)!\n";
		return;
	}
	isCreate = true;
}

void rectangle::translate(int vertical, int horizontal)
{
	x += horizontal;
	y += vertical;
}

bool rectangle::within(char * nameFig, Figure *& BigFigure) const
{
	if (!strcmp(nameFig, "circle"))
	{
		int *dataCircle = BigFigure->getData();
		if (pow(x - dataCircle[0], 2) + pow(y - dataCircle[1], 2) <= pow(dataCircle[2], 2) &&
			pow((x + width) - dataCircle[0], 2) + pow(y - dataCircle[1], 2) <= pow(dataCircle[2], 2) &&
			pow(x - dataCircle[0], 2) + pow((y - height) - dataCircle[1], 2) <= pow(dataCircle[2], 2))
		{
			delete[]dataCircle;
			return true;
		}
		else
		{
			delete[]dataCircle;
			return false;
		}
	}
	else if (!strcmp(nameFig, "rect"))
	{
		int *dataRect = BigFigure->getData();
		if ((x >= dataRect[0]) && (y <= dataRect[1]) && ((x+width)<(dataRect[0]+dataRect[2])) &&
			((y - height)>(dataRect[1] - dataRect[3])))
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

void rectangle::deserialize(std::ofstream & save) const
{
	save << "<rect x=\"";
	save << x << "\" y=\"";
	save << y << "\" width=\"";
	if(width)save << width << "\" height=\"";
	else save<< "\" height=\"";
	if(height)save<< height << "\" fill=\"";
	else save<< "\" fill=\"";
	if (fill)save << fill << "\" />\n";
	else save << "\" />\n";
}
