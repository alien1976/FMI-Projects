#include <iostream>
#include "File.h"


void File::resizebuffer()
{
	char *temp;
	if (buffer == NULL)
	{
		buffer = new char[cnt_line+2];
		return;
	}
	temp = new char[strlen(buffer) + cnt_line + 3];
	for (int i = 0; i < strlen(buffer) + 1; i++)
	{
		temp[i] = buffer[i];
	}
	delete[]buffer;
	buffer = temp;
}

void File::open(char * name)
{
	delete[]this->name;
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
	readFile.open(this->name, std::ios::in);
	if (!readFile)return;
	for (int i = 0; !readFile.eof(); i++)
	{
		line = new char[1000];
		readFile.getline(line, 1000);
		cnt_line = strlen(line);
		line[cnt_line] = '\n';
		line[cnt_line + 1] = '\0';
		resizebuffer();
		if (i == 0)strcpy_s(buffer, cnt_line + 2, line);
		else {
			int i = strlen(buffer), j = 0;
			buffer[i] = line[j]; i++; j++;
			while (true) {
				buffer[i] = line[j]; i++; j++;
				if (line[j] == '\0') {
					buffer[i] = line[j];
					break;
				}
			}
		}
		delete[]line;
	}
	readFile.close();
}
