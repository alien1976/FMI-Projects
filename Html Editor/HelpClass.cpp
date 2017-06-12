#include <iostream>
#include "HelpClass.h"
char *TagNoId(char *name)
{
	char new_name[20];
	int i = 0;
	while (name[i] != '\0'&&name[i]!=' ')
	{
		new_name[i] = name[i];
		i++;
	}
	new_name[i] = '\0';
	return new_name;
}

char * getTagFromPath(char * path, int cnt_tags,int beg)
{
	char *tag=new char[10];
	int i = beg;
	int p = beg;
	int j = 0;
	while (path[i] != '\0'&&path[i] != ' ')
	{
		if (path[i] == '/'|| path[i] == '\0'|| path[i] == ' ')break;
		i++;
	}
	for (; p < i; j++)
	{
		tag[j] = path[p];
		p++;
	}
	tag[j] = '\0';
	return tag;
}

int getCntTagsPath(char *path)
{
	int i = 0;
	int cnt = 0;
	while (path[i] != '\0'&& path[i] != ' ')
	{
		if (path[i] == '/')cnt++;
		i++;
	}
	return cnt+1;
}

bool const isTag(char *name)
{
	for (int i = 0; basic[i] != "0"; i++)
	{
		if (!strcmp(basic[i], name))return true;
	}
	for (int i = 0; formatting[i] != "0"; i++)
	{
		if (!strcmp(formatting[i], name))return true;
	}
	for (int i = 0; lists[i] != "0"; i++)
	{
		if (!strcmp(lists[i], TagNoId(name)))return true;
	}
	for (int i = 0; style[i] != "0"; i++)
	{
		if (!strcmp(style[i], TagNoId(name)))return true;
	}
	return false;
}
char *setId(char*name)
{
	char id[50];
	int i = 0;
	for (; i < strlen(name); i++)
	{
		if (name[i] == ' ' || name[i] == '\0')break;
	}
	if (name[i] == '\0')return NULL;
	i += 5;
	int j = 0;
	for (; name[i]!='\"'; j++)
	{
		id[j] = name[i];
		i++;
	}
	id[j] = '\0';
	return id;
}
char *getCommandBuff(char *command)
{
	char *buff = new char[1000];
	int i = 0;
	while (command[i] != ' '&&command[i] != '\0')i++;
	if (command[i] == '\0')return buff = NULL;
	int j = 0;
	i++;
	while (command[i] != '\0')
	{
		buff[j] = command[i];
		i++; j++;
	}
	buff[j] = '\0';
	return buff;
}
char *TagNoIdDynamic(char *name)
{
	char *new_name=new char[strlen(name)+1];
	int i = 0;
	while (name[i] != '\0'&&name[i] != ' ')
	{
		new_name[i] = name[i];
		i++;
	}
	new_name[i] = '\0';
	return new_name;
}
void movePosition(char * buff, char *name_tag, int end,int &pos)
{
	int cnt = 1;
	int cnt_close = 0;
	char finded_tag_name[50];
	char *name_tag_no_id = TagNoIdDynamic(name_tag);
	for (int i = pos; i < end; i++)
	{
		if (buff[i] == '<'&&buff[i + 1] != '/')
		{
			i++;
			int j = 0;
			while (buff[i] != '>') { finded_tag_name[j] = buff[i]; i++; j++; }
			finded_tag_name[j] = '\0';
			if (!strcmp(TagNoId(finded_tag_name), name_tag_no_id))
			{
				cnt++;
			}
			else
			{
				movePosition(buff, finded_tag_name, end, i);
			}
		}
		else if (buff[i] == '<'&&buff[i + 1] == '/')
		{
			i += 2;
			int j = 0;
			while (buff[i] != '>') { finded_tag_name[j] = buff[i]; i++; j++; }
			finded_tag_name[j] = '\0';
			if (!strcmp(TagNoId(finded_tag_name), name_tag_no_id))
			{
				cnt_close++;
			}
		}
		if (cnt == cnt_close&&cnt != 0)break;
	}
	delete[]name_tag_no_id;
}
int sameTags(char * buff,char *name_tag, int beg, int end)
{
	int cnt = 1;
	int cnt_close=0;
	char finded_tag_name[50];
	char *name_tag_no_id = TagNoIdDynamic(name_tag);
	for(int i = beg; i < end; i++)
	{
		if (buff[i] == '<'&&buff[i + 1] != '/')
		{
			i++;
			int j = 0;
			while (buff[i] != '>') { finded_tag_name[j] = buff[i]; i++; j++; }
			finded_tag_name[j] = '\0';
			if (!strcmp(TagNoId(finded_tag_name), name_tag_no_id))
			{
				cnt++;
			}
			else
			{
				movePosition(buff,finded_tag_name,end,i);
			}
		}
		else if (buff[i] == '<'&&buff[i + 1] == '/')
		{
			i+=2;
			int j = 0;
			while (buff[i] != '>') { finded_tag_name[j] = buff[i]; i++; j++; }
			finded_tag_name[j] = '\0';
			if (!strcmp(TagNoId(finded_tag_name), name_tag_no_id))
			{
				cnt_close++;
			}
		}
		if (cnt == cnt_close&&cnt!=0)break;
	}
	delete[]name_tag_no_id;
	return cnt-1;
}
