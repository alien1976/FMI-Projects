#pragma once
#include "Tag.h"
class Lists :public Tag
{
public:
	Lists();
	Lists& operator=(const Lists &rhs);
	virtual ~Lists();
	virtual Tag* createTag(char*);
	virtual void resizeTags();
	void deleteResize(int index);
	virtual void setData(char*buff, char *name, int beg, int end);
	virtual void readData();
	virtual char *getName() { return name; }
	virtual char *getId() { return id; }
	virtual int getCntTags() { return cnt_tags; }
	virtual void find(char *tag);
	virtual void saveData(std::ofstream&file);
	virtual void erase(char *path, int cnt_tags, int beg, int alltags);
	virtual void findIdAdd(char *id,char *content);
	void deleteBuffer(int index);
	void resizeBuffer(char *content, int &end_buff, int number_more);
	virtual void setContent(char *content);
	virtual void createContent(char *path, int cnt_tags_path, int beg, int alltags);
	virtual void create(char *content);
	virtual void within(char *path, int cnt_tags, int beg, int alltags);
	int cntTabs();
private:
	int cnt_tags;
	Tag **tags;
	char *name;
	char *buff;
	char *id;
};

