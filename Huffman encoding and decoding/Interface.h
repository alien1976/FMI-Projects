#pragma once
#include<iostream>
#include<fstream>
#include <direct.h>
#include <time.h>
#include "HuffmanTree.h"
#include "dirent.h"
//vzeto ot https://github.com/tronkko/dirent
//tozi hedur beshe nujen za otvarqne na direktoriite
//za algoritima za hufmanovo durvo 4etoh ot nqkolko saita no nai mi dopadna tazi statiq
//http://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree
//zashtoto ot neq razbrah kak deisva samiqt algoritum
//ostanalite idei za sortiraneto v opashkata, 4eteneto po izmislenata hash tablica za kod na nqkoi simvol
//podredbata vuv binarniq arc fail, obhojdaneto na faila i t.n. sa moi
#define SizeFrequency 256
class Interface
{
public:
	Interface():isDir(false),cnt_spaces(0),isFind(false){};
	~Interface() {};
	void run(char *operation, char * pathArc, char* pathforZip);
private:
	void readDir(DIR *&pdir, struct dirent *&pent,char *dirPath);
	void Pack(char *path);
	void Unpack(char *pathDecode, char *pathWrite);
	void MakeTree(std::ifstream &file);
	void MakePath(char*&path, char*systemPath, std::ifstream&file);
	void CodeFile(char *path);
	void DecodeFile(char *path,std::ifstream&file);
	void List(char*path);
	void ListFile(char*path,std::ifstream &file);
	void Search(char *path, char*str);
	void SearchFile(char *path,std::ifstream&file,char*str);
	char* makePath(char*dirPath, char*dirOrFile);
	char *getHeadPath(char*path);
	//promenlivi za kompresiq
	int frequency[SizeFrequency] = { 0 };
	Queue<Leafs*> sub_trees;
	HuffTree Tree;
	std::ofstream arcFile;
	bool isDir;
	//promenlivi za dekompresiq
	Byte sizeDir;
	int curPosFile;
	int curMask;
	char*namefile;
	//promenlivi za list
	int cnt_spaces;
	//promenlivi za Search
	bool isFind;
};
