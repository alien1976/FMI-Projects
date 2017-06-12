#include <iostream>
#include <fstream>
#include "Basic.h"
#include "Formatting.h"
#include "Lists.h"
#include "Style.h"

void cd(char *command)
{
	std::cout << ">";
	std::cin.sync();
	std::cin.getline(command, 1000);
	return;
}
void resizebuffer(char *&buffer,int cnt_line)
{
	char *temp;
	if (buffer == NULL)
	{
		buffer = new char[cnt_line + 2];
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
void openFile(char *&buffer, char *&line, int &cnt_line,std::fstream&readFile)
{
	
	for (int i = 0; !readFile.eof(); i++)
	{
		line = new char[1000];
		readFile.getline(line, 1000);
		cnt_line = strlen(line);
		line[cnt_line] = '\n';
		line[cnt_line + 1] = '\0';
		resizebuffer(buffer,cnt_line);
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
}
Tag* createTag(char*name) {
	for (int i = 0; basic[i] != "0"; i++)
	{
		if (!strcmp(basic[i], name))return new Basic();
	}
	for (int i = 0; formatting[i] != "0"; i++)
	{
		if (!strcmp(formatting[i], name))return new Formatting();
	}
	for (int i = 0; lists[i] != "0"; i++)
	{
		if (!strcmp(lists[i], TagNoId(name)))return new Lists();
	}
	for (int i = 0; style[i] != "0"; i++)
	{
		if (!strcmp(style[i], TagNoId(name)))return new Style();
	}
	return NULL;
}
void resizeTags(Tag **&tags,int cnt_tags)
{
	Tag **temp = new Tag*[cnt_tags + 1];
	for (int i = 0; i < cnt_tags; i++)
	{
		temp[i] = tags[i];
	}
	delete[]tags;
	tags = temp;
}
void openFileObject(Tag **&tags, int &cnt_tags, char *buffer, std::fstream&readFile)
{
	int cnt_name = 0;
	int cnt_close_tag = 0;
	int end = 0;
	for (int i = 0;i<strlen(buffer); i++)
	{
		char name_tag[15] = {0};
		if (buffer[i] == '<'&&buffer[i+1]!='/') {
			cnt_name = 0; i++;
			while (buffer[i] != '>') {
				name_tag[cnt_name] = buffer[i];
				cnt_name++; i++;
			}
			name_tag[cnt_name] = '\0';
			i++;
			if (isTag(name_tag)) {
				resizeTags(tags, cnt_tags);
				tags[cnt_tags]=createTag(name_tag);
				cnt_tags++;
				cnt_close_tag = 0;
				char close_tag[14] = {0};
				for (int j = i; j < strlen(buffer); j++)
				{
					if (buffer[j] == '<'&&buffer[j+1]=='/') {
						cnt_close_tag = 0; j+=2;
						while (buffer[j] != '>') {
							close_tag[cnt_close_tag] = buffer[j];
							cnt_close_tag++; j++;
						}
						close_tag[cnt_close_tag] = '\0';
					}
					if (!strcmp(name_tag, close_tag)) {
						end = j+1;
						tags[cnt_tags-1]->setData(buffer,name_tag, i, end); 
						i = end;
						break;
					}
				}
			}
		}
	}
}
char *getCommand(char *command)
{
	char new_command[10];
	int i = 0;
	while (command[i] != ' '&&command[i] != '\0')
	{
		new_command[i] = command[i];
		i++;
	}
	new_command[i] = '\0';
	return new_command;
}
char *getNameId(char *buff)
{
	char *id = new char[1000];
	int i = 0;
	while (buff[i] != '#'&&buff[i] != '\0')i++;
	if (buff[i] == '\0')return id = NULL;
	int j = 0;
	i++;
	while (buff[i] != '\0'&&buff[i]!=' ')
	{
		id[j] = buff[i];
		i++; j++;
	}
	id[j] = '\0';
	return id;
}
bool isCorrectName(char *new_name)
{
	char file[6] = "xhtml";
	int i = 0;
	while (new_name[i] != '.'&&new_name[i] != '\0')i++;
	if (new_name[i] == '\0')return false;
	i++;
	if (new_name[i] == '\0')return false;
	int j = 0;
	while (new_name[i] != '\0')
	{
		if (new_name[i] != file[j])return false;
		i++; j++;
	}
	if (new_name[i] != '\0')return false;
	return true;
}
char *getId(char *buff)
{
	char *new_id=new char[100];
	int i = 0;
	while (buff[i] != '#'&&buff[i] != '\0')i++;
	if (buff[i] == '#')
	{
		while (buff[i+1] != ' '&&buff[i+1] != '\0')
		{
			new_id[i] = buff[i+1];
			i++;
		}
		new_id[i] = '\0';
		return new_id;
	}
	else return NULL;
}
bool isFileExist(char *name)
{
	std::ifstream file(name);
	return file.good();
}
int main()
{
	char command[1000];
	Tag **tags = NULL;
	int cnt_tags = 0;
	char *line=NULL;
	char *buffer = NULL;
	int cnt_line = 0;
	bool isClosed=true;
	cd(command);
	while (true)
	{
		if (!strcmp(getCommand(command), "open"))
		{
			isClosed = false;
			char *name= getCommandBuff(command);
			if (name == NULL) {
				std::cout << "Bad input!\n";
				cd(command);
				continue;
			}
			std::fstream readFile(name, std::ios::in);
			if (!readFile)return 1;
			else openFile(buffer, line, cnt_line, readFile);
			openFileObject(tags, cnt_tags,buffer,readFile);
			std::cout << "Successsfully opened " << name << std::endl;
			cd(command);
			while (true)
			{
				if (!strcmp(getCommand(command), "save"))
				{
					readFile.close();
					std::ofstream writeFile(name,std::ios::out);
					if (!writeFile) { std::cout << "problem openning"; break; }
					writeFile << "<!DOCTYPE html>\n";
					for (int i = 0; i < cnt_tags; i++)
					{
						writeFile << "<" << tags[i]->getName();
						if (tags[i]->getId() != NULL) {
							writeFile << " id=\"" << tags[i]->getId() << "\"";
						}
						writeFile << ">";
						tags[i]->saveData(writeFile);
						writeFile << "</" << tags[i]->getName() << ">";
					}
					writeFile.close();
					std::cout << "The file " << name << " has been saved!\n";
					readFile.open(name, std::ios::in);
					if (!readFile)return 1;
					else { 
						delete[]buffer;
						buffer = NULL;
						openFile(buffer, line, cnt_line, readFile); 
					}
					cd(command);
				}
				else if (!strcmp(getCommand(command), "saveas"))
				{
					char *new_name = getCommandBuff(command);
					if (isFileExist(new_name))
					{
						std::cout << "The file allready exist!\n";
					}
					else if (isCorrectName(new_name)) {
						readFile.close();
						std::ofstream writeFile(new_name, std::ios::out);
						if (!writeFile) { std::cout << "problem openning"; break; }
						writeFile << "<!DOCTYPE html>\n";
						for (int i = 0; i < cnt_tags; i++)
						{
							writeFile << "<" << tags[i]->getName();
							if (tags[i]->getId() != NULL) {
								writeFile << " id=\"" << tags[i]->getId() << "\"";
							}
							writeFile << ">";
							tags[i]->saveData(writeFile);
							writeFile << "</" << tags[i]->getName() << ">";
						}
						writeFile.close();
						std::cout << "The file " << new_name << " has been saved!\n";
						readFile.open(name, std::ios::in);
						if (!readFile)return 1;
						else {
							delete[]buffer;
							buffer = NULL;
							openFile(buffer, line, cnt_line, readFile);
						}
						delete[]new_name;
					}
					else {
						std::cout << "The file extension is wrong! Use .xhtml\nFile is not saved!\n";
					}
					cd(command);
				}
				else if (!strcmp(getCommand(command), "close"))
				{
					readFile.close();
					for (int i = 0; i < cnt_tags; i++)
						delete tags[i];
					delete[]tags;
					delete[]buffer;
					buffer = NULL;
					tags = NULL;
					//delete[]line;
					cnt_tags = 0;
					isClosed = true;
					std::cout<<name << " has been closed!\n";
					delete[]name;
					cd(command);
					break;
				}
				else if (!strcmp(getCommand(command), "print"))
				{
					std::cout << "<!DOCTYPE html>\n";
					for (int i = 0; i < cnt_tags; i++)
					{
						std::cout << "<" << tags[i]->getName();
						if (tags[i]->getId() != NULL) { 
							std::cout<<" id=\""<< tags[i]->getId() << "\""; }
						std::cout << ">";
						tags[i]->readData();
						std::cout << "</" << tags[i]->getName() << ">\n";
					}
					cd(command);
				}
				else if (!strcmp(getCommand(command), "create"))
				{
					char *path = getCommandBuff(command);
					int cnt_tags_path = 1;
					char *tag = getTagFromPath(path, cnt_tags_path, 0);
					int allTagsInPath = getCntTagsPath(path);
					for (int i = 0; i < cnt_tags; i++)
					{
						if (isTag(tag) && cnt_tags_path != allTagsInPath)
						{
							if (!strcmp(tag, tags[i]->getName()))
							{
								tags[i]->createContent(path, cnt_tags_path, strlen(tag) + 1, allTagsInPath);
							}
						}
					}
					delete[]tag;
					delete[]path;
					cd(command);
				}
				else if (!strcmp(getCommand(command), "erase"))
				{
					char *path = getCommandBuff(command);
					int cnt_tags_path = 1;
					char *tag = getTagFromPath(path, cnt_tags_path, 0);
					int allTagsInPath = getCntTagsPath(path);
					for (int i = 0; i < cnt_tags; i++)
					{
						if (isTag(tag) && cnt_tags_path != allTagsInPath)
						{
							if (!strcmp(tag, tags[i]->getName()))
							{
								tags[i]->erase(path, cnt_tags_path,strlen(tag)+1,allTagsInPath);
							}
						}
					}
					delete[]tag;
					delete[]path;
					cd(command);
				}
				else if (!strcmp(getCommand(command), "add"))
				{
					char *buff_add = getCommandBuff(command);
					if (buff_add != NULL) {
						char *id = getId(buff_add);
						if (id != NULL) {
							char *content = getCommandBuff(buff_add);
							if (content != NULL) {
								for (int i = 0; i < cnt_tags; i++)
								{
									tags[i]->findIdAdd(id, content);
								}
								delete[]content;
								delete[]id;
								delete[]buff_add;
							}
							else {
								std::cout << "Bad content!\n";
								delete[]id;
								delete[]buff_add;
							}
						}
						else {
							std::cout << "Bad Id!\n";
							delete[]buff_add;
						}
					}else std::cout << "No Id and content!\n";
					cd(command);
				}
				else if (!strcmp(getCommand(command), "find"))
				{
					char *tag = getCommandBuff(command);
					for (int i = 0; i < cnt_tags; i++)
					{
						if (!strcmp(tags[i]->getName(), tag))
						{
							std::cout << "<" << tags[i]->getName();
							if (tags[i]->getId() != NULL) {
								std::cout << " id=\"" << tags[i]->getId() << "\"";
							}
							std::cout << ">";
							tags[i]->readData();
							std::cout << "</" << tags[i]->getName() << ">\n";
						}
						else
						{
							tags[i]->find(tag);
						}
					}
					delete[]tag;
					cd(command);
				}
				else if (!strcmp(getCommand(command), "within"))
				{
					char *path = getCommandBuff(command);
					int cnt_tags_path = 1;
					char *tag = getTagFromPath(path, cnt_tags_path, 0);
					int allTagsInPath = getCntTagsPath(path);
					for (int i = 0; i < cnt_tags; i++)
					{
						if (isTag(tag) && cnt_tags_path != allTagsInPath)
						{
							if (!strcmp(tag, tags[i]->getName()))
							{
								tags[i]->within(path, cnt_tags_path, strlen(tag) + 1, allTagsInPath);
							}
						}
					}
					delete[]tag;
					delete[]path;
					cd(command);
				}
				else if (!strcmp(command, "exit"))
				{
					if (!isClosed) {
						readFile.close();
						/*for (int i = 0; i < cnt_tags; i++)
							delete tags[i];
						delete[]tags;*/
						delete[]buffer;
						buffer = NULL;
						tags = NULL;
						cnt_tags = 0;
						isClosed = true;
						std::cout << name << " has been closed!\n";
						delete[]name;
					}
					break;
				}
				else
				{
					if (!strcmp(command, "open"))std::cout << "There are already file open!\n";
					else std::cout << "Bad command!\n";
					std::cin.clear();
					cd(command);
				}
			}
		}
		else if (!strcmp(command, "exit"))
		{
			std::cout << "The program is exiting...\n";
			break;
		}
		else
		{
			if (!strcmp(getCommand(command), "save") || !strcmp(getCommand(command), "saveas") || !strcmp(getCommand(command), "close") ||
				!strcmp(getCommand(command), "print") || !strcmp(getCommand(command), "create") || !strcmp(command, "erase") ||
				!strcmp(getCommand(command), "add") || !strcmp(getCommand(command), "find") || !strcmp(getCommand(command), "within"))
				std::cout << "There are no open file!\n";
			else std::cout << "Bad command!\n";
			std::cin.clear();
			cd(command);
		}
	}
	return 0;
}
