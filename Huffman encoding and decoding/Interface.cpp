#include "Interface.h"

void Interface::run(char * operation, char *  pathArc, char*pathforZipOrStr)
{
	if (!strcmp(operation, "-Pack"))
	{
		arcFile.open(pathArc, std::ios::binary);
		if (!arcFile)return;
		Pack(pathforZipOrStr);
		arcFile.close();
	}
	else if (!strcmp(operation, "-Unpack"))
	{
		Unpack(pathArc, pathforZipOrStr);
	}
	else if (!strcmp(operation, "-List"))
	{
		List(pathArc);
	}
	else if (!strcmp(operation, "-Search"))
	{
		Search(pathArc, pathforZipOrStr);
	}

}
void Interface::readDir(DIR *&pdir, struct dirent *&pent, char *dirPath)
{
	while (pent = readdir(pdir))
	{
		if (pent == NULL)
		{
			return;
		}
		if (strcmp(pent->d_name, ".") && strcmp(pent->d_name, ".."))
		{
			char *newPathDir = makePath(dirPath, pent->d_name);
			if (!newPathDir)return;
			DIR *temp = opendir(newPathDir);
			if (temp) {
				Tree.writeByte(1, arcFile);
				int sizeNameDir = strlen(pent->d_name);
				Tree.writeByte((Byte)sizeNameDir, arcFile);
				for (int i = 0; i < sizeNameDir; i++)
					Tree.writeByte((Byte)pent->d_name[i], arcFile);
				readDir(temp, pent, newPathDir);
				closedir(temp);
			}
			else {
				Tree.clearTree();
				Tree.writeByte(0, arcFile);
				Tree.writeByte((Byte)strlen(pent->d_name), arcFile);
				for (int i = 0; i < strlen(pent->d_name); i++)
					Tree.writeByte((Byte)pent->d_name[i], arcFile);
				char *newPathFile = makePath(dirPath, pent->d_name);
				if (!newPathFile)return;
				clock_t tStart = clock();
				CodeFile(newPathFile);
				for (int i = 0; i < 256; i++)
					frequency[i] = 0;
				std::cout << "Time for Compress " << pent->d_name << ": " << (double)(clock() - tStart) / CLOCKS_PER_SEC << " secs.\n";
				delete[]newPathFile;
			}
			delete[]newPathDir;
		}
	}
	Tree.writeByte('k', arcFile);
}
void Interface::Pack(char * path)
{
	DIR *pdir = NULL;
	pdir = opendir(path);
	struct dirent *pent = NULL;
	if (!pdir)
	{
		std::cout << "Bad DIR path!\n";
		return;
	}
	isDir = true;
	char *nameHead = getHeadPath(path);
	if (!nameHead)return;
	int sizeNameDir = strlen(nameHead);
	Tree.writeByte((Byte)sizeNameDir, arcFile);
	for (int i = 0; i < sizeNameDir; i++)
		Tree.writeByte((Byte)nameHead[i], arcFile);
	readDir(pdir, pent, path);
	closedir(pdir);
	if (Tree.getMask() == 8)Tree.writeByte('k', arcFile);//zashtoto maskata ostana na 8 i ne zapisva poslednoto k
	//segashnoto k nqma da se zapishe prosto trqbva funckiqta da se pusne 4e da zapishe predishnoto k
	delete[]nameHead;
}

void Interface::Unpack(char * pathDecode, char*pathWrite)
{
	clock_t tStart = clock();
	std::ifstream file(pathDecode, std::ios::binary);
	if (!file)return;
	sizeDir = (int)Tree.readByte(file);
	char*nameDir = new(std::nothrow) char[sizeDir + 1];
	if (!nameDir)return;
	for (int i = 0; i < sizeDir; i++)
		nameDir[i] = Tree.readByte(file);
	nameDir[sizeDir] = '\0';
	char *newPathDir = makePath(pathWrite, nameDir);
	if (!newPathDir)return;
	DIR *pdir = opendir(newPathDir);
	if (pdir)
	{
		std::cout << nameDir << " exists and will be not decomressed!\n";
		return;
	}
	else {
		mkdir(newPathDir);
		DecodeFile(newPathDir, file);
	}
	delete[]nameDir;
	delete[]newPathDir;
	file.close();
	std::cout << "Time for Decompress: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << " secs.\n";

}

void Interface::MakeTree(std::ifstream & file)
{
	Byte c;
	if (file.peek() == EOF)return;
	while (!file.eof())
	{
		file.read((char*)&c, sizeof(c));
		frequency[c]++;
	}
	for (int i = 0; i < SizeFrequency; i++)
	{
		if (frequency[i] != 0)
		{
			Leafs *temp = new Leafs(frequency[i], i);
			sub_trees.enqueue(temp);
		}
	}
	if (sub_trees.getSize() > 0) {
		Tree.setLetters(sub_trees.getSize());
		Tree.MakeTree(file, sub_trees);
		Tree.MakeTable();
	}
}

void Interface::MakePath(char *& path, char * systemPath, std::ifstream & file)
{
	clock_t tStart = clock();
	int size = (int)Tree.readByte(file);
	namefile = new(std::nothrow) char[size + 1];
	if (!namefile)return;
	for (int i = 0; i < size; i++)
		namefile[i] = Tree.readByte(file);
	namefile[size] = '\0';
	path = makePath(systemPath, namefile);
	curPosFile = file.tellg();
	curMask = Tree.getMask();
}

void Interface::CodeFile(char * path)
{
	std::ifstream file(path, std::ios::binary);
	if (!file)return;
	MakeTree(file);
	unsigned int bits = Tree.getBitsOfFile();
	int mask8 = 0;
	Byte temp;
	int num;
	for (int i = 0; i < 4; i++) {
		temp = (Byte)((bits >> (24 - i * 8)) & 255);
		Tree.writeByte(temp, arcFile);
	}
	Tree.setcntBits(0);
	if (bits != 0)
	{
		Tree.CodeTreeInFile(arcFile);
		Tree.CodeInFile(arcFile, file);
	}
	int tempMask = Tree.getMask();
	for (int i = 0; i < MaxMask - tempMask; i++)
		Tree.writeBit(0, arcFile);
	file.close();
}

void Interface::DecodeFile(char * path, std::ifstream&file)
{
	if (file.eof())return;
	if (file.peek() == 'k') {
		Tree.readByte(file);
		return;
	}
	if (Tree.readByte(file))
	{
		sizeDir = (int)Tree.readByte(file);
		char*nameDir = new(std::nothrow) char[sizeDir + 1];
		if (!nameDir)return;
		for (int i = 0; i < sizeDir; i++)
			nameDir[i] = Tree.readByte(file);
		nameDir[sizeDir] = '\0';
		char *newPathDir = makePath(path, nameDir);
		if (!newPathDir)return;
		DIR *pdir = opendir(newPathDir);
		if (pdir)
		{
			std::cout << nameDir << " exists and will be not decomressed!\n";
			return;
		}
		else {
			mkdir(newPathDir);
			DecodeFile(newPathDir, file);
			DecodeFile(path, file);
		}
		delete[]nameDir;
		delete[]newPathDir;
	}
	else
	{
		clock_t tStart = clock();
		Tree.clearTree();
		char *pathFile=NULL;
		MakePath(pathFile, path, file);
		if (!pathFile)return;
		std::ofstream write(pathFile, std::ios::binary);
		if (!write)return;
		file.seekg(curPosFile, std::ios::beg);
		Tree.setMask(curMask);
		Byte temp;
		unsigned int bits = 0;
		for (int i = 0; i < 4; i++) {
			temp = Tree.readByte(file);
			bits += temp << (24 - i * 8);
		}
		if (bits != 0)
		{
			Tree.setcntBits(bits);
			Tree.DecodeInTree(file);
			Tree.DecodeInFile(write, file);
			Tree.setMask(0);
		}
		delete[]pathFile;
		write.close();
		std::cout << "Time for Decompress " << namefile << " :" << (double)(clock() - tStart) / CLOCKS_PER_SEC << " secs.\n";
		delete[]namefile;
		DecodeFile(path, file);
	}
}

void Interface::List(char * path)
{
	clock_t tStart = clock();
	std::ifstream file(path, std::ios::binary);
	if (!file)return;
	sizeDir = (int)Tree.readByte(file);
	char*nameDir = new(std::nothrow) char[sizeDir + 1];
	if (!nameDir)return;
	for (int i = 0; i < sizeDir; i++)
		nameDir[i] = Tree.readByte(file);
	nameDir[sizeDir] = '\0';
	std::cout << "Content in "<<getHeadPath(path)<<"\n"<<"DIR: "<<nameDir<<"\n";
	char *newPathDir = makePath(path, nameDir);
	if (!newPathDir)return;
	ListFile(newPathDir, file);
	delete[]nameDir;
	delete[]newPathDir;
	file.close();
	std::cout << "Time for List: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << " secs.\n";
}

void Interface::ListFile(char * path, std::ifstream & file)
{
	cnt_spaces++;
	if (file.eof())
	{
		return;
	}
	if (file.peek() == 'k') {
		Tree.readByte(file);
		cnt_spaces--;
		return;
	}
	if (Tree.readByte(file))
	{
		sizeDir = (int)Tree.readByte(file);
		char*nameDir = new char[sizeDir + 1];
		for (int i = 0; i < sizeDir; i++)
			nameDir[i] = Tree.readByte(file);
		nameDir[sizeDir] = '\0';
		for (int i = 0; i < cnt_spaces; i++)
			std::cout << " ";
		std::cout <<"DIR: "<< nameDir << "\n";
		char *newPathDir = makePath(path, nameDir);
		ListFile(newPathDir, file);
		cnt_spaces--;
		ListFile(path, file);
		delete[]nameDir;
		delete[]newPathDir;
	}
	else
	{
		Tree.clearTree();
		char *pathFile=NULL;
		MakePath(pathFile, path, file);
		if (!pathFile)return;
		file.seekg(curPosFile, std::ios::beg);
		Tree.setMask(curMask);
		Byte temp;
		unsigned int bits = 0;
		for (int i = 0; i < 4; i++) {
			temp = Tree.readByte(file);
			bits += temp << (24 - i * 8);
		}
		if (bits != 0)
		{
			Tree.setcntBits(bits);
			Tree.DecodeInTree(file);
			Tree.ListInFile(file);
			Tree.setMask(0);
		}
		for (int i = 0; i < cnt_spaces; i++)
			std::cout << " ";
		std::cout << "FILE: " << namefile << " | Compressed Size: ";
		if (bits / 8 >= 1024)
		{
			if((bits/8)/1024<1024.0)
				std::cout<< (bits / 8)/1024.0 << " kb" << "\n";
			else if ((bits / 8) / 1024 >= 1024.0)
				std::cout << ((bits / 8) / 1024)/1024.0 << " mb" << "\n";
		}else std::cout << bits / 8 << " byte(s)" << "\n";
		delete[]pathFile;
		delete[]namefile;
		cnt_spaces--;
		int tempCnt = cnt_spaces;
		ListFile(path, file);
		if(tempCnt>cnt_spaces)
		cnt_spaces++;
	}
}

void Interface::Search(char * path, char * str)
{
	clock_t tStart = clock();
	std::ifstream file(path, std::ios::binary);
	if (!file)return;
	sizeDir = (int)Tree.readByte(file);
	char*nameDir = new(std::nothrow) char[sizeDir + 1];
	if (!nameDir)return;
	for (int i = 0; i < sizeDir; i++)
		nameDir[i] = Tree.readByte(file);
	nameDir[sizeDir] = '\0';
	char *newPathDir = makePath(path, nameDir);
	if (!newPathDir)return;
	std::cout <<"Results for "<< str << ":\n";
	SearchFile(newPathDir, file,str);
	if (!isFind)std::cout <<" "<< str << " could not be found in " << nameDir << std::endl;
	delete[]nameDir;
	delete[]newPathDir;
	file.close();
	std::cout << "Time for Search: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << " secs.\n";
}

void Interface::SearchFile(char * path, std::ifstream&file, char * str)
{
	if (file.eof())
	{
		return;
	}
	if (file.peek() == 'k') {
		Tree.readByte(file);
		return;
	}
	if (Tree.readByte(file))
	{
		sizeDir = (int)Tree.readByte(file);
		char*nameDir = new(std::nothrow) char[sizeDir + 1];
		if (!nameDir)return;
		for (int i = 0; i < sizeDir; i++)
			nameDir[i] = Tree.readByte(file);
		nameDir[sizeDir] = '\0';
		char *newPathDir = makePath(path, nameDir);
		if (!newPathDir)return;
		SearchFile(newPathDir, file,str);
		SearchFile(path, file,str);
		delete[]nameDir;
		delete[]newPathDir;
	}
	else
	{
		Tree.clearTree();
		char *pathFile=NULL;
		MakePath(pathFile, path, file);
		if (!pathFile)return;
		file.seekg(curPosFile, std::ios::beg);
		Tree.setMask(curMask);
		Byte temp;
		unsigned int bits = 0;
		for (int i = 0; i < 4; i++) {
			temp = Tree.readByte(file);
			bits += temp << (24 - i * 8);
		}
		if (bits != 0)
		{
			Tree.setcntBits(bits);
			Tree.DecodeInTree(file);
			if (Tree.SearchInFile(file, str))
			{
				isFind = true;
				std::cout <<"DIR: "<<getHeadPath(path)<<" FILE: "<< namefile << std::endl;
			}
			Tree.setMask(0);
		}
		delete[]pathFile;
		delete[]namefile;
		SearchFile(path, file,str);
	}
}

char * Interface::makePath(char * dirPath, char * dirOrFile)
{
	if (!dirPath)return NULL;
	if (!dirOrFile)return NULL;
	char *temp = new(std::nothrow) char[strlen(dirPath) + strlen(dirOrFile) + 2];
	if (!temp)return NULL;
	strcpy(temp, dirPath);
	strcat(temp, "\\");
	strcat(temp, dirOrFile);
	temp[strlen(dirPath) + strlen(dirOrFile) + 1] = '\0';
	return temp;
}

char * Interface::getHeadPath(char * path)
{
	int size = strlen(path);
	DynamicArray<char>temp;
	int i = size - 1;
	while (path[i] != '\\')
	{
		temp.AddItem(path[i]);
		i--;
	}
	char *temp1 = new(std::nothrow) char[temp.getSize() + 1];
	if (!temp1)return NULL;
	int j = temp.getSize() - 1;
	for (int i = 0; i < temp.getSize(); i++)
	{
		temp1[i] = temp[j];
		j--;
	}
	temp1[temp.getSize()] = '\0';
	return temp1;
}


