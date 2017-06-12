#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include "Queue.h"
#include "DynamicArray.h"
#include "HashTable.h"
#define MaxMask 8
#define MaxSizeMask 7
typedef unsigned char Byte;
class Leafs {
public:
	Byte c;
	int frequency;
	bool code;
	Leafs *left;
	Leafs *right;
public:
	Leafs(int frequency=0,Byte c=0,Leafs*left = NULL, Leafs*right = NULL,bool code=false)
		:c(c),frequency(frequency), left(left), right(right),code(code) {};
};
class HuffTree
{
private:
	Leafs *root;
	Byte byte;
	int mask;
	bool isLeadroot;
	bool isWritten;
	bool bit;
	int allLetters;
	unsigned int cntAllbits;
	unsigned int cntAllbitsDecode;
	int i;
	HashTable<DynamicArray<bool>>charTable;
	DynamicArray<bool>charCode;
public:
	HuffTree();
	HuffTree(const HuffTree& rhs);
	HuffTree& operator=(const HuffTree& rhs);
	~HuffTree();
private:
	void Copy(const HuffTree& rhs);
	void Destroy(Leafs* root);
	void CopyFromRoot(Leafs*& root, Leafs* rootForCopy);
	void MakeTableFromRoot(Leafs*& root,bool code);
	void CodeTreeInFileFromRoot(Leafs*&root, std::ofstream &write);
	Leafs* DecodeInTreeFromRoot(std::ifstream &read);
	void DecodeInFileFromRoot(Leafs*&root,std::ofstream &write, std::ifstream &read);
	void ListFileFromRoot(Leafs*&root, std::ifstream &read);
	bool SearchInFileFromRoot(Leafs*&root, std::ifstream&read, char c);
	void getCode(std::ofstream&file,DynamicArray<bool>&charCode);
public:
	void clearTree();
	void writeBit(int num, std::ofstream &file);
	void writeByte(Byte c, std::ofstream &file);
	bool readBit(std::ifstream&read);
	char readByte(std::ifstream&read);
	void MakeTree(std::ifstream&file,Queue<Leafs*>& sub_trees);
	void MakeTable();
	void CodeTreeInFile(std::ofstream &write);
	void CodeInFile(std::ofstream &write,std::ifstream &read);
	void DecodeInTree(std::ifstream&read);
	void DecodeInFile(std::ofstream &write, std::ifstream &read);
	void ListInFile(std::ifstream&read);
	bool SearchInFile(std::ifstream&read, char*str);
	void setLetters(int num) { allLetters = num; }
	void setcntBits(unsigned int num) { cntAllbits = num; }
	int getMask() { return mask; }
	void setMask(int num) { mask = num; }
	unsigned int getBitsOfFile() { return cntAllbits; }
};
