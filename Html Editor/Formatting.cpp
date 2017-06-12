#include <iostream>
#include <fstream>
#include "Basic.h"
#include "Formatting.h"
#include "Lists.h"
#include "Style.h"



Formatting::Formatting()
{
	tags = NULL;
	name = NULL;
	buff = NULL;
}

Formatting & Formatting::operator=(const Formatting & rhs)
{
	if (this == &rhs)return *this;
	for (int i = 0; i < cnt_tags; i++)
	{
		delete tags[i];
	}
	cnt_tags = rhs.cnt_tags;
	tags = new Tag*[cnt_tags];
	for (int i = 0; i < cnt_tags; i++)
	{
		tags[i] = rhs.tags[i];
	}
	delete[]buff;
	buff = new char[strlen(rhs.buff) + 1];
	strcpy_s(buff, strlen(rhs.buff) + 1, rhs.buff);
	delete[]name;
	name = new char[strlen(rhs.name) + 1];
	strcpy_s(name, strlen(rhs.name) + 1, rhs.name);
	return *this;
}


Formatting::~Formatting()
{
	delete[]name;
	delete[]buff;
	for (int i = 0; i < cnt_tags; i++)
		delete tags[i];
	delete[]tags;
}

Tag * Formatting::createTag(char *name)
{

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

void Formatting::resizeTags()
{
	if (cnt_tags == 0) {
		tags = new Tag*[1];
	}
	Tag **temp = new Tag*[cnt_tags + 1];
	for (int i = 0; i < cnt_tags; i++)
	{
		temp[i] = tags[i];
	}
	delete[] tags;
	tags = temp;
}

void Formatting::deleteResize(int index)
{
	if (cnt_tags == 0)return;
	if (cnt_tags == 1) {
		delete tags[index];
		delete[]tags;
		this->cnt_tags = 0;
		return;
	}
	Tag **temp = new Tag*[cnt_tags - 1];
	int j = 0;
	int i = 0;
	for (; i < cnt_tags;)
	{
		if (i >= index) {
			temp[j] = tags[i + 1];
			i++; j++;
		}
		else {
			temp[j] = tags[i];
			i++; j++;
		}
	}
	delete tags[index];
	delete[]tags;
	tags = temp;
	cnt_tags--;
}

void Formatting::setData(char * buff, char *name, int beg, int end)
{
	delete[]this->name;
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1,name);
	int cnt_name = 0;
	int cnt_close_tag = 0;
	int	cnt_buff = 0;
	int this_end = 0;
	this->buff = new char[end - beg + 1];
	for (int i = beg; i<end; i++)
	{
		char name_tag[50] = { 0 };
		if (buff[i] == '<'&&buff[i + 1] != '/') {
			this->buff[cnt_buff] = '@';
			cnt_buff++;
			cnt_name = 0; i++;
			while (buff[i] != '>') {
				name_tag[cnt_name] = buff[i];
				cnt_name++; i++;
			}
			name_tag[cnt_name] = '\0';
			i++;
			if (isTag(name_tag)) {
				resizeTags();
				tags[cnt_tags] = createTag(name_tag);
				cnt_tags++;
				cnt_close_tag = 0;
				int cnt_how_same_tags = sameTags(buff, name_tag, i, end);
				int cnt_times_to_close = 0;
				int first_close = 0;
				char close_tag[14] = { 0 };
				int how_tags = 0;
				int cnt_row = 0;
				for (int j = i; j < end; j++)
				{
					if (buff[j] == '<'&&buff[j + 1] == '/') {
						cnt_close_tag = 0; j += 2;
						while (buff[j] != '>') {
							close_tag[cnt_close_tag] = buff[j];
							cnt_close_tag++; j++;
						}
						close_tag[cnt_close_tag] = '\0';
						if (!strcmp(TagNoId(name_tag), close_tag) && cnt_how_same_tags == 0) {
							first_close = j + 1;
							break;
						}
						else if (!strcmp(TagNoId(name_tag), close_tag))
						{
							if (cnt_how_same_tags == cnt_times_to_close) {
								first_close = j + 1;
								break;
							}
							cnt_times_to_close++;
						}
					}
				}
				this_end = first_close - strlen(close_tag) - 3;
				tags[cnt_tags - 1]->setData(buff, name_tag, i, this_end);
				i = this_end + strlen(close_tag) + 2;
			}
		}
		else if (buff[i] == '<'&&buff[i + 1] == '/')
		{
			break;
		}
		else
		{
			this->buff[cnt_buff] = buff[i];
			cnt_buff++;
		}
	}
	this->buff[cnt_buff] = '\0';
}

void Formatting::readData()
{
	int index_tags = 0;
	for (int i = 0; i < strlen(buff); i++)
	{
		if (buff[i] != '@')
		{
			std::cout << buff[i];
		}
		else {
			std::cout << "<" << tags[index_tags]->getName();
			if (tags[index_tags]->getId() != NULL) {
				std::cout << " id=\"" << tags[index_tags]->getId() << "\"";
			}
			std::cout << ">";
			tags[index_tags]->readData();
			std::cout << "</" << tags[index_tags]->getName() << ">";
			index_tags++;
		}
	}
}

void Formatting::find(char * tag)
{
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
}

void Formatting::saveData(std::ofstream & file)
{
	int cnt = 0;
	if (this->buff == NULL)return;
	for (int i = 0; i < strlen(this->buff); i++) {
		if (this->buff[i] == '@'&&cnt<cnt_tags) {
			file << "<" << tags[cnt]->getName();
			if (tags[cnt]->getId() != NULL) {
				file << " id=\"" << tags[cnt]->getId() << "\"";
			}
			file << ">";
			tags[cnt]->saveData(file);
			file << "</" << tags[cnt]->getName() << ">";
			cnt++;
		}
		else {
			file << buff[i];
		}
	}
}

void Formatting::erase(char * path, int cnt_tags, int beg, int alltags)
{
	int cnt_erased = 0;
	cnt_tags++;
	char *tag = getTagFromPath(path, cnt_tags, beg);
	for (int i = 0; i <this->cnt_tags;)
	{
		if (cnt_tags == alltags) {
			if (!strcmp(tag, tags[i]->getName()))
			{
				cnt_erased++;
				deleteBuffer(i);
				deleteResize(i);
				i = 0;
				continue;
			}
		}
		else if (isTag(tag) && cnt_tags != alltags)
		{
			if (!strcmp(tag, tags[i]->getName()))
			{
				tags[i]->erase(path, cnt_tags, strlen(tag) + 1 + beg, alltags);
			}
		}
		i++;
	}
	delete[]tag;
	if (cnt_erased != 0)std::cout << "Erased " << cnt_erased << " element(s)\n";
}

void Formatting::findIdAdd(char * id, char *content)
{
	for (int i = 0; i < cnt_tags; i++)
	{
		if (!tags[i]->getId())
		{
			tags[i]->findIdAdd(id, content);
		}
		else if (!strcmp(tags[i]->getId(), id))
		{
			tags[i]->setContent(content);
			tags[i]->findIdAdd(id, content);
		}
		else
		{
			tags[i]->findIdAdd(id, content);
		}
	}
}

void Formatting::deleteBuffer(int index)
{
	int cnt = 0;
	int i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '@') {
			cnt++;
			if (!strcmp(tags[cnt - 1]->getName(), tags[index]->getName()))break;
		}
		i++;
	}
	if (cnt != 0)
	{
		int j = i + 1;
		while (buff[j] == '\n' || buff[j] == ' '&&buff[j] != '\0')j++;
		while (buff[i] != '\0')
		{
			buff[i] = buff[j];
			i++; j++;
		}
	}
	else return;
}

void Formatting::resizeBuffer(char * content, int & end_buff, int number_more)
{
	char *temp = new char[strlen(buff) + strlen(content) + number_more + 1];
	int i = 0;
	for (; i < strlen(buff); i++)
	{
		temp[i] = buff[i];
	}
	delete[]buff;
	buff = temp;
	end_buff = i;
}

int Formatting::cntTabs()
{
	int cnt = 0;
	int i = 0;
	while (buff[i] != '\n'&&buff[i] != '\0')i++;
	if (buff[i] == '\n') {
		cnt++;
		while (buff[i] == ' '&&buff[i] != '\0')
		{
			cnt++;
			i++;
		}
	}
	return cnt;
}

void Formatting::setContent(char * content)
{
	int end_buff = strlen(buff);
	int cnt_tabs = cntTabs();
	resizeBuffer(content, end_buff, cnt_tabs + 2);
	int i = 0;
	int cnt_name = 0;
	int cnt_close_tag = 0;
	int this_end = 0;
	this->buff[end_buff] = ' '; end_buff++;
	while (content[i] == ' ')i++;
	for (; i<strlen(content); i++)
	{
		char name_tag[50] = { 0 };
		if (content[i] == '<'&&content[i + 1] != '/') {
			this->buff[end_buff] = '@';
			end_buff++;
			cnt_name = 0; i++;
			while (content[i] != '>') {
				name_tag[cnt_name] = content[i];
				cnt_name++; i++;
			}
			name_tag[cnt_name] = '\0';
			i++;
			if (isTag(name_tag)) {
				resizeTags();
				tags[cnt_tags] = createTag(name_tag);
				cnt_tags++;
				cnt_close_tag = 0;
				int cnt_how_same_tags = sameTags(content, name_tag, i, strlen(content));
				int cnt_times_to_close = 0;
				int first_close = 0;
				char close_tag[14] = { 0 };
				int how_tags = 0;
				int cnt_row = 0;
				for (int j = i; j <strlen(content); j++)
				{
					if (content[j] == '<'&&content[j + 1] == '/') {
						cnt_close_tag = 0; j += 2;
						while (content[j] != '>') {
							close_tag[cnt_close_tag] = content[j];
							cnt_close_tag++; j++;
						}
						close_tag[cnt_close_tag] = '\0';
						if (!strcmp(TagNoId(name_tag), close_tag) && cnt_how_same_tags == 0) {
							first_close = j + 1;
							break;
						}
						else if (!strcmp(TagNoId(name_tag), close_tag))
						{
							if (cnt_how_same_tags == cnt_times_to_close) {
								first_close = j + 1;
								break;
							}
							cnt_times_to_close++;
						}
					}
				}
				this_end = first_close - strlen(close_tag) - 3;
				tags[cnt_tags - 1]->setData(content, name_tag, i, this_end);
				i = this_end + strlen(close_tag) + 2;
			}
		}
		else if (content[i] == '<'&&content[i + 1] == '/')
		{
			break;
		}
		else
		{
			buff[end_buff] = content[i];
			end_buff++;
		}
	}
	int j = 0;
	if (cnt_tabs != 0) {
		buff[end_buff] = '\n';
		end_buff++;
	}
	while (j <= cnt_tabs - 1) {
		buff[end_buff] = ' ';
		end_buff++; j++;
	}
	buff[end_buff] = '\0';
	std::cout << "Successfully added a new element!\n";
}

void Formatting::createContent(char * path, int cnt_tags_path, int beg, int alltags)
{
	cnt_tags_path++;
	int cnt_real = this->cnt_tags;
	char *tag = getTagFromPath(path, cnt_tags_path, beg);
	for (int i = 0; i <this->cnt_tags;)
	{
		if (cnt_tags_path == alltags) {
			if (!strcmp(tag, tags[i]->getName()))
			{
				char *content = getCommandBuff(path);
				if (content == NULL)
				{
					std::cout << "Bad content!\n";
					return;
				}
				tags[i]->create(content);
				delete[]content;
				std::cout << "The element was created!\n";
			}
		}
		else if (isTag(tag) && cnt_tags_path != alltags)
		{
			if (!strcmp(tag, tags[i]->getName()))
			{
				tags[i]->createContent(path, cnt_tags_path, strlen(tag) + 1 + beg, alltags);
			}
		}
		i++;
	}
}

void Formatting::create(char * content)
{
	int end_buff = strlen(buff);
	int cnt_tabs = cntTabs();
	resizeBuffer(content, end_buff, cnt_tabs + 2);
	int i = 0;
	int cnt_name = 0;
	int cnt_close_tag = 0;
	int this_end = 0;
	this->buff[end_buff] = ' '; end_buff++;
	while (content[i] == ' ')i++;
	for (; i<strlen(content); i++)
	{
		char name_tag[50] = { 0 };
		if (content[i] == '<'&&content[i + 1] != '/') {
			this->buff[end_buff] = '@';
			end_buff++;
			cnt_name = 0; i++;
			while (content[i] != '>') {
				name_tag[cnt_name] = content[i];
				cnt_name++; i++;
			}
			name_tag[cnt_name] = '\0';
			i++;
			if (isTag(name_tag)) {
				resizeTags();
				tags[cnt_tags] = createTag(name_tag);
				cnt_tags++;
				cnt_close_tag = 0;
				int cnt_how_same_tags = sameTags(content, name_tag, i, strlen(content));
				int cnt_times_to_close = 0;
				int first_close = 0;
				char close_tag[14] = { 0 };
				int how_tags = 0;
				int cnt_row = 0;
				for (int j = i; j <strlen(content); j++)
				{
					if (content[j] == '<'&&content[j + 1] == '/') {
						cnt_close_tag = 0; j += 2;
						while (content[j] != '>') {
							close_tag[cnt_close_tag] = content[j];
							cnt_close_tag++; j++;
						}
						close_tag[cnt_close_tag] = '\0';
						if (!strcmp(TagNoId(name_tag), close_tag) && cnt_how_same_tags == 0) {
							first_close = j + 1;
							break;
						}
						else if (!strcmp(TagNoId(name_tag), close_tag))
						{
							if (cnt_how_same_tags == cnt_times_to_close) {
								first_close = j + 1;
								break;
							}
							cnt_times_to_close++;
						}
					}
				}
				this_end = first_close - strlen(close_tag) - 3;
				tags[cnt_tags - 1]->setData(content, name_tag, i, this_end);
				i = this_end + strlen(close_tag) + 2;
			}
		}
		else if (content[i] == '<'&&buff[i + 1] == '/')
		{
			break;
		}
		else
		{
			buff[end_buff] = content[i];
			end_buff++;
		}
	}
	int j = 0;
	if (cnt_tabs != 0) {
		buff[end_buff] = '\n';
		end_buff++;
	}
	while (j <= cnt_tabs - 1) {
		buff[end_buff] = ' ';
		end_buff++; j++;
	}
	buff[end_buff] = '\0';
	std::cout << "Successfully added a new element!\n";
}

void Formatting::within(char * path, int cnt_tags, int beg, int alltags)
{
	cnt_tags++;
	int cnt_real = this->cnt_tags;
	char *tag = getTagFromPath(path, cnt_tags, beg);
	for (int i = 0; i <this->cnt_tags;)
	{
		if (cnt_tags == alltags) {
			if (!strcmp(tag, tags[i]->getName()))
			{
				std::cout << "<" << tags[i]->getName();
				if (tags[i]->getId() != NULL) {
					std::cout << " id=\"" << tags[i]->getId() << "\"";
				}
				std::cout << ">";
				tags[i]->readData();
				std::cout << "</" << tags[i]->getName() << ">\n";
			}
		}
		else if (isTag(tag) && cnt_tags != alltags)
		{
			if (!strcmp(tag, tags[i]->getName()))
			{
				tags[i]->within(path, cnt_tags, strlen(tag) + 1 + beg, alltags);
			}
		}
		i++;
	}
	delete[]tag;
}
