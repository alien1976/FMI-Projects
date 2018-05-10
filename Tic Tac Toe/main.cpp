//Kaloyan Geshev N:45221 gr. 2
#include <iostream>
#include "Tree.h"
bool isBoardFull(char *board) {
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == ' ')return false;
	}
	return true;
}
void printBoard(char *board)
{
	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 3 || i == 6)std::cout << std::endl << "-------------\n";
		if (i == 0 || i == 3 || i == 6)std::cout << "| " << board[i] << " | ";
		else std::cout << board[i] << " | ";
	}
	std::cout << std::endl << "-------------\n";
	std::cout << std::endl;
}
int main()
{
	char board[10] = { ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };
	/*for (int i = 0; i < 9; i++)
	{
		board[i] = ' ';
	}
	board[9] = '\0';*/
	int x, y;
	TicTacToeTree *tree = new TicTacToeTree();
	bool invalidMove = false;
	while (!isBoardFull(board)) {
		system("CLS");
		printBoard(board);
		if (invalidMove)
		{
			std::cout << "Invalid Move!\n";
			invalidMove = false;
		}
		std::cout << "Your move(x,y): ";
		std::cin >> x >> y;
		if (x > 3 && y > 3 && y < 1 && x < 1)
		{
			invalidMove = true;
			continue;
		}
		if ((x == 1 && board[(y - 1)] != ' ') ||
			((x == 2) && board[(3 + (y - 1))] != ' ') ||
			((x == 3) && board[(6 + (y - 1))] != ' '))
		{
			invalidMove = true;
			continue;
		}
		else
		{
			if (x == 1)board[(y - 1)] = 'X';
			if (x == 2)board[(3 + (y - 1))] = 'X';
			if (x == 3)board[(6 + (y - 1))] = 'X';
		}

		//tree->printBoards();
		if (tree->PCmove(board)) {
			printBoard(board);
			break;
		}
	}
	if (isBoardFull(board))std::cout << "No one wins!\n";
	delete tree;
	return 0;
}