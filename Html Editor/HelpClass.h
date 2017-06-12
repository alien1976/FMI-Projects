#pragma once
char *const basic[] = { "html","title","body","h1","h2","h3","h4","h5","h6","br","hr","0" };
char *const formatting[] = { "font","strong","u","em","0" };
char *const lists[] = { "ul","li","ol","0" };
char *const style[] = { "div","span","style","p","0" };

bool const isTag(char *name);
char *setId(char*name);
char *TagNoId(char *name);
char *getTagFromPath(char *path, int cnt_tags,int beg);
int getCntTagsPath(char *path);
char *getCommandBuff(char *command);
int sameTags(char *buff, char *name_tag, int beg, int end);