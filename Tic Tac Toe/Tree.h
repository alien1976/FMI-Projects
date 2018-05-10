#pragma once
#include <iostream>
#include "DynamicArray.h"
class TicTacToeTree {
private:
	struct Node {
		char *board;
		int aplha;
		int beta;
		int value;
		bool max;
		int depth;
		DynamicArray <Node*> childrens;
		Node(char *&data, int alpha, int beta, bool max, int depth) :
			aplha(alpha), beta(beta), max(max), depth(depth) {
			board = data;
			if (max)value = -1000;
			else value = +1000;
		};
	};
	Node *root;
public:
	TicTacToeTree();
	TicTacToeTree(const TicTacToeTree& rhs);
	TicTacToeTree& operator= (const TicTacToeTree& rhs);
	~TicTacToeTree();
public:
	//void printBoards();
	bool PCmove(char *board);
private:
	void genTree(char* board);
	void minmax();
	void copy(const TicTacToeTree&rhs);
	void copyFromRoot(Node *&root, Node *cpyRoot);
	void destroy(Node *root);
	void genTreeFromRoot(Node *&root, bool player, bool max);
	//void printBoardsFromRoot(Node *&root);
	bool winner(Node *&root, char player);
	void hn(Node *& root);//evristi4nata funkciq
	int haveNoSymbol(char *board, char symbol, int num);
	int minmaxFromRoot(Node *&root);
	int max(int a, int b) { if (a >= b)return a; else return b; }
	int min(int a, int b) { if (a <= b)return a; else return b; }
	bool isBoardFull(Node *&root)const;
};


inline TicTacToeTree::TicTacToeTree()
{
	root = NULL;

}

inline TicTacToeTree::TicTacToeTree(const TicTacToeTree & rhs)
{
	copy(rhs);
}


inline TicTacToeTree& TicTacToeTree::operator=(const TicTacToeTree & rhs)
{
	if (this == &rhs)
		return *this;
	destroy(root);
	root = NULL;
	copy(rhs);
	return *this;
}

inline TicTacToeTree::~TicTacToeTree()
{
	destroy(root);
	root = NULL;
}

inline void TicTacToeTree::genTree(char* board)
{
	if (root != NULL)destroy(root);
	char *tempBoard = new char[10];
	for (int i = 0; i < 9; i++)
	{
		tempBoard[i] = board[i];
	}
	tempBoard[9] = '\0';
	root = new Node(tempBoard, -1000, 1000, true, 0);
	genTreeFromRoot(root, false, true);
}

inline void TicTacToeTree::minmax()
{
	for (int i = 0; i < root->childrens.getSize(); i++)
	{
		root->value = max(root->value, minmaxFromRoot(root->childrens[i]));
		root->aplha = max(root->aplha, root->value);
		if (root->beta < root->aplha)break;
	}
}


inline void TicTacToeTree::copy(const TicTacToeTree & rhs)
{
	copyFromRoot(root, rhs.root);
}

inline void TicTacToeTree::copyFromRoot(Node *&root, Node *cpyRoot)
{
	if (cpyRoot == NULL)
	{
		root = NULL;
		return;
	}
	char *tempBoard = new char[10];
	for (int i = 0; i < 9; i++)
	{
		tempBoard[i] = cpyRoot->board[i];
	}
	tempBoard[9] = '\0';
	root = new Node(tempBoard, cpyRoot->aplha, cpyRoot->beta, cpyRoot->max, cpyRoot->depth);
	int size = cpyRoot->childrens.getSize();
	for (int i = 0; i < size; i++)
	{
		root->childrens.AddItem(NULL);
		copyFromRoot(root->childrens[i], cpyRoot->childrens[i]);
	}
}

inline void TicTacToeTree::destroy(Node * root)
{
	if (root != NULL)
	{
		int size = root->childrens.getSize();
		for (int i = 0; i < size; i++)
		{
			destroy(root->childrens[i]);
		}
		delete[]root->board;
		delete root;
	}
}

inline void TicTacToeTree::genTreeFromRoot(Node *&root, bool player, bool max)
{
	for (int i = 0; i < 9; i++)
	{
		if (root->board[i] == ' ')
		{

			if (player)
			{
				root->board[i] = 'X';
			}
			else
			{
				root->board[i] = 'O';
			}
			char *temp = new char[10];
			for (int j = 0; j < 9; j++)
			{
				temp[j] = root->board[j];
			}
			temp[9] = '\0';
			if (winner(root, 'O')) {
				Node *condition = new Node(temp, -1000, 1000, !max, root->depth + 1);
				hn(condition);
				root->childrens.AddItem(condition);
				root->board[i] = ' ';
			}
			else if (winner(root, 'X'))
			{
				Node *condition = new Node(temp, -1000, 1000, !max, root->depth + 1);
				condition->value = -1000;//poneje iskame O da pobedi trqbva da e mnogo malka 
				//stoinost za da ne iszpluva tova sustoqnie nagore
				root->childrens.AddItem(condition);
				root->board[i] = ' ';
			}
			else if (isBoardFull(root))
			{
				Node *condition = new Node(temp, -1000, 1000, !max, root->depth + 1);
				condition->value = 0;
				root->childrens.AddItem(condition);
				root->board[i] = ' ';
			}
			else {
				Node *condition = new Node(temp, -1000, 1000, !max, root->depth + 1);
				root->childrens.AddItem(condition);
				genTreeFromRoot(root->childrens[root->childrens.getSize() - 1], !player, !max);
				root->board[i] = ' ';
			}
		}
	}
}

/*
inline void TicTacToeTree::printBoards()
{
	//polzvah tazi funkciq da si testvam!!
	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 3 || i == 6)std::cout << std::endl;
		std::cout << root->board[i] << " ";
	}
	std::cout << std::endl;
	std::cout << root->value << " " << root->depth;
	if (root->max)std::cout << "MAX";
	else std::cout << "MIN";
	std::cout << std::endl;
	printBoardsFromRoot(root);
}
*/

inline bool TicTacToeTree::PCmove(char * board)
{
	genTree(board);
	minmax();
	if (winner(root, 'X')) {
		std::cout << "Winner is Player: X!";
		return true;
	}
	if (root->childrens.getSize() != 0) {
		for (int i = 0; i < root->childrens.getSize(); i++)
		{
			if (root->childrens[i]->value == root->value)
			{
				for (int j = 0; j < 9; j++)
					board[j] = root->childrens[i]->board[j];
				if (winner(root->childrens[i], 'O')) {
					std::cout << "Winner is PC: O!";
					return true;
				}
				break;
			}
		}
	}
	
}

/*
inline void TicTacToeTree::printBoardsFromRoot(Node *& root)
{
	//otnovo za test
	if (root->depth > 1)return;
	if (root->value > -1000 && root->value < 1000) {
		for (int i = 0; i < 9; i++)
		{
			if (i == 0 || i == 3 || i == 6)std::cout << std::endl;
			std::cout << root->board[i] << " ";
		}
		std::cout << std::endl;
		std::cout << root->value << " " << root->depth;
		if (root->max)std::cout << "MAX";
		else std::cout << "MIN";
		std::cout << std::endl;
	}
	for (int i = 0; i < root->childrens.getSize(); i++)
	{
		printBoardsFromRoot(root->childrens[i]);
	}
}
*/

inline bool TicTacToeTree::winner(Node *&root, char player)
{
	//tuk kopirah koda tui kato ne mi se gubeshe vreme :)
	for (int i = 0; i < 9; i += 3)
	{
		if ((root->board[i] == root->board[i + 1]) && (root->board[i + 1] == root->board[i + 2]) && (root->board[i] == player))
			return true;
	}
	for (int i = 0; i < 3; i++)
	{
		if ((root->board[i] == root->board[i + 3]) && (root->board[i + 3] == root->board[i + 6]) && (root->board[i] == player))
			return true;
	}
	if ((root->board[0] == root->board[4]) && (root->board[4] == root->board[8]) && (root->board[0] == player))
	{
		return true;
	}
	if ((root->board[2] == root->board[4]) && (root->board[4] == root->board[6]) && (root->board[2] == player))
	{
		return true;
	}
	return false;
}

inline void TicTacToeTree::hn(Node *& root)
{
	root->value = 0;
	root->value += 2 * haveNoSymbol(root->board, 'X', 2);
	root->value += haveNoSymbol(root->board, 'X', 1);
	root->value -= 2 * haveNoSymbol(root->board, 'O', 2);
	root->value -= haveNoSymbol(root->board, 'O', 1);
}

inline int TicTacToeTree::haveNoSymbol(char * board, char symbol, int num)
{
	//izpolzvam za evristi4nata funkciq
	int verticals = 0;
	int horisontals = 0;
	int diagonals = 0;
	int cntSymbol = 0;
	for (int i = 0; i < 9; i++)
	{
		if (i == 3 || i == 6)
		{
			if (cntSymbol == num)horisontals++;
			cntSymbol = 0;
		}
		if (board[i] == symbol)cntSymbol++;
		else if (board[i] != ' ') {
			if (i < 3)i = 3;
			else if (i < 6 & i>3)i = 6;
			continue;
		}
		if (i == 8) {
			if (cntSymbol == num)horisontals++;
			cntSymbol = 0;
		}
	}
	cntSymbol = 0;
	for (int i = 0; i < 3; i++)
	{
		if (board[i] == symbol)cntSymbol++;
		else if (board[i] != ' ') {
			cntSymbol = 0; continue;
		}
		if (board[i + 3] == symbol)cntSymbol++;
		else if (board[i] != ' ') {
			cntSymbol = 0; continue;
		}
		if (board[i + 6] == symbol)cntSymbol++;
		else if (board[i] != ' ') {
			cntSymbol = 0;  continue;
		}
		if (cntSymbol == num)verticals++;
		cntSymbol = 0;
	}
	cntSymbol = 0;
	for (int i = 0; i < 3; i += 2)
	{
		if (board[i] == symbol)cntSymbol++;
		else if (board[i] != ' ') {
			cntSymbol = 0; continue;
		}
		if (i == 2 && board[i + 2] == symbol)cntSymbol++;
		else if (board[i + 2] != ' ') {
			cntSymbol = 0; continue;
		}
		if ((i == 0 || i == 2) && board[i + 4] == symbol)cntSymbol++;
		else if (board[i + 4] != ' ') {
			cntSymbol = 0; continue;
		}
		if (i == 0 && board[i + 8] == symbol)cntSymbol++;
		else if (board[i + 8] != ' ') {
			cntSymbol = 0; continue;
		}
		if (cntSymbol == num)diagonals++;
		cntSymbol = 0;
	}
	return diagonals + verticals + horisontals;
}

inline int TicTacToeTree::minmaxFromRoot(Node *& root)
{
	if (winner(root, 'X')|| winner(root, 'O')|| isBoardFull(root))
		return root->value;
	if (root->max)
	{
		//int value = -1000;
		for (int i = 0; i < root->childrens.getSize(); i++)
		{
			root->value = max(root->value, minmaxFromRoot(root->childrens[i]));
			root->aplha = max(root->aplha, root->value);
			if (root->beta < root->aplha)break;
		}
		return root->value;
	}
	else {
		//int value = 1000;
		for (int i = 0; i < root->childrens.getSize(); i++)
		{
			root->value = min(root->value, minmaxFromRoot(root->childrens[i]));
			root->aplha = min(root->aplha, root->value);
			if (root->beta < root->aplha)break;
		}
		return root->value;
	}
}

inline bool TicTacToeTree::isBoardFull(Node *& root) const
{
	for (int i = 0; i < 9; i++)
	{
		if (root->board[i] == ' ')return false;
	}
	return true;
}

