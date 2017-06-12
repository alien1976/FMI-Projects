#pragma once
#include <iostream>
#include "HelpClass.h"
class Tag
{
public:
	virtual Tag* createTag(char*) = 0;
	virtual void resizeTags() = 0;
	virtual void setData(char*buff,char *name, int beg, int end) = 0;
	virtual void readData() = 0;
	virtual char *getName() = 0;
	virtual char *getId() = 0;
	virtual int getCntTags() = 0;
	virtual void find(char *tag) = 0;
	virtual void saveData(std::ofstream&) = 0;
	virtual void erase(char *path, int cnt_tags, int beg,int alltags)=0;
	virtual void findIdAdd(char *id,char *content) = 0;
	virtual void setContent(char *content)=0;
	virtual void createContent(char *path, int cnt_tags_path, int beg, int alltags) = 0;
	virtual void create(char *content) = 0;
	virtual void within(char *path, int cnt_tags, int beg, int alltags) = 0;
private:
};

