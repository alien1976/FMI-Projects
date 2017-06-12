#include "Interface.h"

Interface::Interface()
{
	size = 0;
	capacity = 2;
	figures = new(std::nothrow) Figure*[capacity];
	isFileOpened = false;
}

Interface::~Interface()
{
	for (int i = 0; i < size; i++)
		delete[] figures[i];
	delete[]figures;
}

void Interface::enterCmd()
{
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << ">";
	std::cin >> command;
}

bool Interface::checkExtensionFile()const
{
	int i = 0, j = 0;
	char *extension = new char[100];
	while (fileName[i] != '.'&&fileName[i] != '\0')i++;
	if (fileName[i] == '\0')
	{
		std::cout << "The file does not have extension!\n";
		return false;
	}
	i++;
	while (fileName[i] != '\0')extension[j++] = fileName[i++];
	extension[j] = '\0';
	if (strcmp(extension, "svg"))
	{
		std::cout << "The file extension is wrong (not svg)!\n";
		delete[]extension;
		return false;
	}
	else
	{
		delete[]extension;
		return true;
	}
}

void Interface::serialize()
{
	char *tag = new char[20];
	char c;
	int curPos = 0;
	while (!file.eof())
	{
		file.read((char*)&c, sizeof(c));
		if (c == '<')
		{
			file >> tag;
			if (!strcmp(tag, "rect"))
			{
				figures[size] = createFigure("rect");
				figures[size]->setData(file);
				size++;
				resize();
			}
			else if (!strcmp(tag, "circle"))
			{
				figures[size] = createFigure("circle");
				figures[size]->setData(file);
				size++;
				resize();
			}
		}
	}
	delete[]tag;
}

bool Interface::checkTagSvg(char * tag)const
{
	if (strlen(tag) < 5)return false;
	char temp[4];
	int i;
	for (i = 0; i < 4; i++)
	{
		temp[i] = tag[i];
	}
	temp[i] = '\0';
	if (!strcmp(temp, "svg") && tag[i + 1] == '>')return true;
	return false;
}

void Interface::erase(int index)
{
	char *tempName = figures[index - 1]->getName();
	for (int i = index - 1; i < size - 1; i++)
		figures[i] = figures[i + 1];
	size--;
	resize();
	std::cout << "Erased a " << tempName << " (" << index << ")\n";
}

Figure * Interface::createFigure(char * name)
{
	if (!strcmp(name, "circle"))return new circle();
	if (!strcmp(name, "rect"))return new rectangle();
	return NULL;
}

void Interface::resize()
{
	if (figures == NULL)
	{
		figures = new(std::nothrow)Figure*[capacity];
		return;
	}
	if (size > 1)
	{
		if (size >= capacity) {
			capacity *= 2;
		}
		else if (capacity > size * 2)
		{
			capacity /= 2;
		}
		else return;
	}
	Figure **temp = new(std::nothrow) Figure*[capacity];
	if (!temp)return;
	for (int i = 0; i < size; i++)
		temp[i] =figures[i];
	delete[]figures;
	figures = temp;


}

void Interface::run()
{
	std::cout << ">";
	std::cin >> command;
	while (true)
	{
		if (!strcmp(command, "open")) {
			if (isFileOpened) {
				std::cout << "Another file is opened!\n";
				enterCmd();
				continue;
			}
			/*fileName = new char[256];*/
			std::cin >> fileName;
			if (!checkExtensionFile())
			{
				enterCmd();
				continue;
			}
			file.open(fileName);
			if (!file)continue;
			isFileOpened = true;
			serialize();
			std::cout << fileName << " has opened successfully!\n";
			file.close();
			enterCmd();
		}
		else if (!strcmp(command, "print"))
		{
			if (!isFileOpened) {
				std::cout << "Open file first!\n";
				enterCmd();
				continue;
			}
			for (int i = 0; i < size; i++)
			{
				std::cout << i + 1 << ". ";
				figures[i]->print();
				std::cout << std::endl;
			}
			enterCmd();

		}
		else if (!strcmp(command, "create"))
		{
			if (!isFileOpened) {
				std::cout << "Open file first!\n";
				enterCmd();
				continue;
			}
			std::cin >> figure;
			figures[size] = createFigure(figure);
			if (!figures[size])
			{
				std::cout << "Can't create " << figure << "!\n";
				delete[] figures[size];
				enterCmd();
				continue;
			}
			else {
				bool isCreate = false;
				figures[size]->create(isCreate);
				if (!isCreate)delete[] figures[size];
				else {
					size++;
					resize();
					std::cout << "Successfully created " << figure << "(" << size << ")\n";
				}
			}
			enterCmd();
		}
		else if (!strcmp(command, "erase"))
		{
			if (!isFileOpened) {
				std::cout << "Open file first!\n";
				enterCmd();
				continue;
			}
			int index;
			std::cin >> index;
			if (index - 1 < 0 || index - 1 > size - 1) {
				std::cout << "There is no figure number " << index << "!\n";
				enterCmd();
				continue;
			}
			erase(index);
			enterCmd();

		}
		else if (!strcmp(command, "translate"))
		{
			if (!isFileOpened) {
				std::cout << "Open file first!\n";
				enterCmd();
				continue;
			}
			int index, vertical, horizontal;
			if (!std::cin)
			{
				enterCmd();
				continue;
			}
			std::cin >> index;
			if (index - 1 < -1 || index - 1 > size - 1) {
				std::cout << "There is no figure number " << index << "!\n";
				enterCmd();
				continue;
			}
			std::cin >> vertical;
			if (!vertical) {
				std::cout << "Translate must have vertical/(!=0) parameter!\n";
				enterCmd();
				continue;
			}

			std::cin >> horizontal;
			if (!horizontal) {
				std::cout << "Translate must have horizontal/(!=0) parameter!\n";
				enterCmd();
				continue;
			}
			if (index == 0)
			{
				for (int i = 0; i < size; i++)
				{
					figures[i]->translate(vertical, horizontal);
				}
				std::cout << "Translated all figures\n";
			}
			else {
				figures[index-1]->translate(vertical, horizontal);
				std::cout << "Traslated (" << index << ") figure\n";
			}
			enterCmd();

		}
		else if (!strcmp(command, "within"))
		{
			if (!isFileOpened) {
				std::cout << "Open file first!\n";
				enterCmd();
				continue;
			}
			std::cin >> figure;
			Figure*tempFigure = createFigure(figure);
			if (!tempFigure)
			{
				std::cout << "Does not have " << figure << " in implementation!\n";
				enterCmd();
				continue;
			}
			bool isCreate = false;
			tempFigure->create(isCreate);
			if (!isCreate)delete tempFigure;
			else {
				int cnt = 1;
				for (int i = 0; i < size; i++)
				{
					if (figures[i]->within(figure, tempFigure))
					{
						std::cout << cnt++ << ". ";
						figures[i]->print();
						std::cout<< std::endl;
					}
				}
			}
			enterCmd();

		}
		else if (!strcmp(command, "save"))
		{
			std::ofstream save(fileName,std::ios::trunc);
			if (!save) {
				std::cout << "Can't Save " << fileName << std::endl;
				enterCmd();
				continue;
			}
			save << header;
			for (int i = 0; i < size; i++)
			{
				save << "  ";
				figures[i]->deserialize(save);
			}
			save << "</svg>";
			save.close();
			std::cout << "Successfully saved changes for "<< fileName << std::endl;
			enterCmd();
		}
		else if (!strcmp(command, "saveas"))
		{
			char name[100];
			std::cin >> name;
			std::ofstream save(name, std::ios::trunc);
			if (!save) {
				std::cout << "Can't Save " << fileName << std::endl;
				enterCmd();
				continue;
			}
			save << header;
			for (int i = 0; i < size; i++)
			{
				save << "  ";
				figures[i]->deserialize(save);
			}
			save << "</svg>";
			save.close();
			std::cout << "Successfully saved another " << name << std::endl;
			enterCmd();
		}
		else if (!strcmp(command, "close"))
		{
			for (int i = 0; i < size; i++)
			{
				delete[]figures[i];
			}
			delete[]figures;
			size = 0;
			capacity = 2;
			figures = new(std::nothrow) Figure*[capacity];
			std::cout << "Successfully closed " << fileName << std::endl;
			isFileOpened = false;
			enterCmd();
		}
		else if (!strcmp(command, "exit"))
		{
			break;
		}
		else {
			std::cout << "Bad command!\n";
			enterCmd();
		}
	}
}
