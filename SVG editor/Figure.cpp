#include "Figure.h"

char * Figure::checkAttr(std::ifstream&file,char& c)const
{
	char *temp = new char[20];
	int i = 0;
	while (!file.eof()&&c!= '=')
	{
		temp[i++] = c;
		file.read((char*)&c, sizeof(c));
	}
	file.read((char*)&c, sizeof(c));//preska4ame = i purvite " i otiva direktno na stoinostta
	temp[i] = '\0';
	return temp;
}

int Figure::readInt(std::ifstream & file)const
{
	int temp=0;
	file >> temp;
	file.seekg(1, std::ios::cur);//za da minem vtorite " i faila da otide na space
	return temp;
}

char * Figure::readString(std::ifstream & file)const
{
	char *temp = new char[50];
	int i = 0;
	char c;
	file.read((char*)&c, sizeof(c));
	while (!file.eof() && c != '\"')
	{
		temp[i++] = c;
		file.read((char*)&c, sizeof(c));
	}
	temp[i] = '\0';
	return temp;
}

