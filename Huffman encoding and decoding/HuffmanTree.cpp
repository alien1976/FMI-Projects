#include "HuffmanTree.h"
HuffTree::HuffTree()
{
	root = NULL;
	mask = 0;
	byte = 0;
	i = 0;
	cntAllbits = 0;
	isLeadroot = true;
}

HuffTree::HuffTree(const HuffTree & rhs)
{
	Copy(rhs);
}

HuffTree & HuffTree::operator=(const HuffTree & rhs)
{
	if (this == &rhs)
		return *this;
	Destroy(root);
	root = NULL;
	Copy(rhs);
	return *this;
}

HuffTree::~HuffTree()
{
	Destroy(root);
	root = NULL;
}

void HuffTree::Destroy(Leafs * root)
{
	if (root != NULL)
	{
		Destroy(root->left);
		Destroy(root->right);
		delete root;
	}
}

void HuffTree::Copy(const HuffTree & rhs)
{
	CopyFromRoot(this->root, rhs.root);
}

void HuffTree::CopyFromRoot(Leafs *& root, Leafs * rootForCopy)
{
	if (rootForCopy == NULL)
	{
		root = NULL;
		return;
	}
	root = new Leafs(rootForCopy->frequency, rootForCopy->c, NULL, NULL, rootForCopy->code);
	CopyFromRoot(root->left, rootForCopy->left);
	CopyFromRoot(root->right, rootForCopy->right);
}

void HuffTree::MakeTableFromRoot(Leafs *& root, bool code)
{
	if (root == NULL)
	{
		charCode.DeleteLast();
		return;
	}
	if (root->left == NULL&&root->right == NULL)
	{
		charCode.AddItem(root->code);
		charTable.hashFunc(charCode, root->c);
		charCode.DeleteLast();
		cntAllbits += (i + 1)*root->frequency;
		i--;
		return;
	}
	else {
		if (!isLeadroot)
			charCode.AddItem(root->code);
		else isLeadroot = false;
		i++;
		MakeTableFromRoot(root->left, false);
		i++;
		MakeTableFromRoot(root->right, true);
	}
	i--;
	if (charCode.getSize())charCode.DeleteLast();
}

void HuffTree::CodeTreeInFileFromRoot(Leafs *& root, std::ofstream & write)
{
	if (root == NULL)return;
	if (root->left == NULL&&root->right == NULL)
	{
		writeBit(1, write);
		writeByte(root->c, write);
	}
	else
	{
		writeBit(0, write);
		CodeTreeInFileFromRoot(root->left, write);
		CodeTreeInFileFromRoot(root->right, write);
	}
}

Leafs* HuffTree::DecodeInTreeFromRoot(std::ifstream & read)
{
	if (readBit(read))
	{
		return new Leafs(0, readByte(read), NULL, NULL, true);
	}
	else
	{
		Leafs*left = DecodeInTreeFromRoot(read);
		Leafs*right = DecodeInTreeFromRoot(read);
		return new Leafs(0, 0, left, right, false);
	}
}

void HuffTree::DecodeInFileFromRoot(Leafs *& root, std::ofstream&write, std::ifstream & read)
{
	if (root == NULL)return;
	if (root->left == NULL&&root->right == NULL)
	{
		isWritten = true;
		i++;
		cntAllbitsDecode += i;
		if (cntAllbitsDecode >= cntAllbits)return;
		write.write((char*)&root->c, sizeof(root->c));
		return;
	}
	else
	{
		bit = readBit(read);
		if (!bit)
		{
			i++;
			DecodeInFileFromRoot(root->left, write, read);
		}
		if (isWritten)return;
		if (bit)
		{
			i++;
			DecodeInFileFromRoot(root->right, write, read);
		}
		if (isWritten)return;
	}
}

void HuffTree::ListFileFromRoot(Leafs *& root, std::ifstream & read)
{
	if (root == NULL)return;
	if (root->left == NULL&&root->right == NULL)
	{
		isWritten = true;
		i++;
		cntAllbitsDecode += i;
		if (cntAllbitsDecode >= cntAllbits)return;
		return;
	}
	else
	{
		bit = readBit(read);
		if (!bit)
		{
			i++;
			ListFileFromRoot(root->left, read);
		}
		if (isWritten)return;
		if (bit)
		{
			i++;
			ListFileFromRoot(root->right, read);
		}
		if (isWritten)return;
	}
}

bool HuffTree::SearchInFileFromRoot(Leafs *& root, std::ifstream & read, char c)
{
	if (root == NULL)return false;
	if (root->left == NULL&&root->right == NULL)
	{
		i++;
		cntAllbitsDecode += i;
		if (cntAllbitsDecode >= cntAllbits)return false;
		if (c == root->c)return true;
		else return false;
	}
	else
	{
		bit = readBit(read);
		if (!bit)
		{
			i++;
			return SearchInFileFromRoot(root->left, read, c);
		}
		if (bit)
		{
			i++;
			return SearchInFileFromRoot(root->right, read, c);
		}
	}
}


void HuffTree::clearTree()
{
	Destroy(root);
	allLetters = 0;
	i = 0;
	root = NULL;
}

void HuffTree::writeBit(int num, std::ofstream& file)
{
	if (mask < MaxMask)
	{
		byte |= num << (MaxSizeMask - mask);
		mask++;
	}
	else {
		file.write((char*)&byte, sizeof(byte));
		byte = 0;
		mask = 0;
		writeBit(num, file);
	}
}

void HuffTree::writeByte(Byte c, std::ofstream &file)
{
	int i = 0;
	int num;
	if (mask < MaxMask)
	{
		while (mask < MaxMask && i < MaxMask)
		{
			num = (c >> MaxSizeMask - i) & 1;
			byte |= num << (MaxSizeMask - mask);
			i++; mask++;
		}
		if (i < 8) {
			file.write((char*)&byte, sizeof(byte));
			byte = 0;
			mask = 0;
			while (i < MaxMask)
			{
				num = (c >> MaxSizeMask - i) & 1;
				byte |= num << (MaxSizeMask - mask);
				i++; mask++;
			}
		}
	}
	else
	{
		file.write((char*)&byte, sizeof(byte));
		byte = 0;
		mask = 0;
		writeByte(c, file);
	}
}

bool HuffTree::readBit(std::ifstream & read)
{
	if (mask == MaxMask)
	{
		mask = 0;
		byte = 0;
		return readBit(read);
	}
	if (mask == 0)
		read.read((char*)&byte, sizeof(byte));
	return (byte >> MaxSizeMask - mask++) & 1;
}

char HuffTree::readByte(std::ifstream & read)
{
	if (mask == 0)
	{
		read.read((char*)&byte, sizeof(byte));
		return byte;
	}
	else
	{
		Byte c = 0;
		int i = 0;
		int num;
		while (mask < MaxMask && i < MaxMask)
		{
			num = ((byte >> MaxSizeMask - mask) & 1);
			c |= num << (MaxSizeMask - i);
			i++; mask++;
		}
		if (mask == MaxMask)
		{
			mask = 0; byte = 0;
			read.read((char*)&byte, sizeof(byte));
			while (i < MaxMask)
			{
				num = ((byte >> MaxSizeMask - mask) & 1);
				c |= num << (MaxSizeMask - i);
				i++; mask++;
			}
		}
		return c;
	}
}

void HuffTree::getCode(std::ofstream & file, DynamicArray<bool>&charCode)
{
	int size = charCode.getSize();
	for (int i = 0; i < size; i++)
	{
		writeBit(charCode[i], file);
	}
}

void HuffTree::MakeTree(std::ifstream & file, Queue<Leafs*>&sub_trees)
{
	while (sub_trees.getSize() > 1)
	{
		Leafs *right = sub_trees.Front();
		right->code = true;
		sub_trees.dequeue();
		Leafs *left = sub_trees.Front();
		left->code = false;
		sub_trees.dequeue();
		Leafs *newTree = new Leafs(right->frequency + left->frequency, 0, left, right);
		sub_trees.enqueue(newTree);
	}
	root = sub_trees.Front();
	sub_trees.dequeue();
}

void HuffTree::MakeTable()
{
	charTable.makeTable(256);
	MakeTableFromRoot(root, false);
}

void HuffTree::CodeTreeInFile(std::ofstream & write)
{
	CodeTreeInFileFromRoot(root, write);
}

void HuffTree::CodeInFile(std::ofstream & write, std::ifstream & read)
{
	Byte c;
	read.clear();
	read.seekg(0, std::ios::end);
	double end = read.tellg();
	read.seekg(0, std::ios::beg);
	while (!read.eof())
	{
		isWritten = false;
		read.read((char*)&c, sizeof(c));
		isLeadroot = true;
		getCode(write, charTable.getCode(c));
	}
}

void HuffTree::DecodeInTree(std::ifstream & read)
{
	byte = 0;
	root = DecodeInTreeFromRoot(read);
}

void HuffTree::DecodeInFile(std::ofstream&write, std::ifstream & read)
{
	Byte c;
	cntAllbitsDecode = 0;
	while (cntAllbitsDecode < cntAllbits)
	{
		i = 0;
		isWritten = false;
		isLeadroot = true;
		DecodeInFileFromRoot(root, write, read);
	}
}

void HuffTree::ListInFile(std::ifstream & read)
{
	Byte c;
	cntAllbitsDecode = 0;
	while (cntAllbitsDecode < cntAllbits)
	{
		i = 0;
		isWritten = false;
		isLeadroot = true;
		ListFileFromRoot(root, read);
	}
}

bool HuffTree::SearchInFile(std::ifstream & read, char * str)
{
	cntAllbitsDecode = 0;
	int indexStr = 0;
	while (cntAllbitsDecode < cntAllbits)
	{
		i = 0;
		isWritten = false;
		isLeadroot = true;
		if (SearchInFileFromRoot(root, read, str[indexStr])) {
			indexStr++;
		}
		else indexStr = 0;
		if (indexStr == strlen(str))
		{
			while (cntAllbitsDecode< cntAllbits)
			{
				i = 0;
				isWritten = false;
				isLeadroot = true;
				SearchInFileFromRoot(root, read, '0');//za da pro4ete baitovete
			}
			return true;
		}
	}
	return false;
}
