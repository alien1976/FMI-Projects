#pragma once
#include <fstream>
class File
{
public:
	void resizebuffer();
	void open(char *name);
	char *print() { return buffer; }
private:
	char *name;
	char *buffer;
	char *line;
	int cnt_line;
	std::ifstream readFile;
};