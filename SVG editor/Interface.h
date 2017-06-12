#pragma once
#include "Figure.h"
#include "circle.h"
#include "rectangle.h"
class Interface
{
public:
	Interface();
	~Interface();
private:
	void enterCmd();
	bool checkExtensionFile()const;
	void serialize();
	bool checkTagSvg(char* tag)const;
	void erase(int index);
	Figure *createFigure(char*name);
	void resize();
public:
	void run();
private:
	Figure **figures;
	int size;
	int capacity;
	char command[100];
	char fileName[256];
	char figure[100];
	bool isFileOpened;
	std::ifstream file;
	const char* header="<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC\"-//W3C//DTD SVG 1.1//EN\"\n\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\" >\n<svg>\n";
};

