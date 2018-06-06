#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "Snake.h"
const int MAX_SIZE = 20;
char table[MAX_SIZE+2][MAX_SIZE*2];

Snake::Snake()
{
	parts = NULL;
	cnt_parts = 0;
	move = 0;
	points = 0;
	gameover = false;
}

Snake::~Snake()
{
	delete[]parts;
}

void Snake::resizeParts()
{
	Part *temp = new Part[cnt_parts + 1];
	for (int i = 0; i < cnt_parts; i++) {
		temp[i] = parts[i];
	}
	delete[]parts;
	parts = temp;
}

void Snake::updateTable(Part &food)
{
	clearTable();	
	for (int k = 0; k < cnt_parts; k++)
	{
		table[parts[k].getY()][parts[k].getX()] = parts[k].getC();
	}
	table[food.getX()][food.getY()] = food.getC();
}

void Snake::clearTable()
{
	for (int i = 0; i < MAX_SIZE + 2; i++)
	{
		for (int j = 0; j < MAX_SIZE * 2; j++)
		{
			if (i == 0 || i == MAX_SIZE + 1) {
				table[i][j] = '#';
			}
			else if ((j == 0 || j == MAX_SIZE * 2 - 1) && i != 0 && i != MAX_SIZE + 1)
			{
				table[i][j] = '#';
			}
			else table[i][j] = ' ';
		}
	}
}

void Snake::checkEaten(Part & food)
{
	if (parts[0]==food) {
		resizeParts();
		cnt_parts++;
		this->points += food.getPoints();
		Part new_food;
		new_food.setXY(rand() % MAX_SIZE, rand() % ((MAX_SIZE * 2) - 2));
		new_food.setPoints();
		food = new_food;
	};
}

bool Snake::checkGameOver()
{
	for (int i = 1; i < cnt_parts; i++)
		if (parts[0].getX() == parts[i].getX() && parts[0].getY() == parts[i].getY())
			return true;
	return false;
}


void Snake::changeDirectionRight(int &i, int &j,Part &food)
{
	if (j < MAX_SIZE * 2 - 2) {
		j++;
		for (int k=cnt_parts-1; k >0; k--)
		{
			parts[k] = parts[k-1];
		}
		parts[0].move(1, 0);
		if (checkGameOver())
		{
			gameover = true;
			return;
		}
		checkEaten(food);
		updateTable(food);
		Sleep(300);
		system("CLS");
		printTable();
	}
	else if (j == MAX_SIZE * 2 - 2)
	{
		j = 1;
		for (int k=cnt_parts-1; k >0; k--)
		{
			parts[k] = parts[k-1];
		}
		parts[0].move(1, 0);
		if (checkGameOver())
		{
			gameover = true;
			return;
		}
		checkEaten(food);
		updateTable(food);
		Sleep(300);
		system("CLS");
		printTable();
	}
}
void Snake::changeDirectionLeft(int &i, int &j,Part &food)
{
	if (j > 1) {
		j--;
		for (int k = cnt_parts - 1; k >0; k--)
		{
			parts[k] = parts[k - 1];
		}
		parts[0].move(-1, 0);
		if (checkGameOver())
		{
			gameover = true;
			return;
		}
		checkEaten(food);
		updateTable(food);
		Sleep(300);
		system("CLS");
		printTable();
	}
	else if (j == 1)
	{
		j = MAX_SIZE * 2 - 2;
		for (int k = cnt_parts - 1; k >0; k--)
		{
			parts[k] = parts[k - 1];
		}
		parts[0].move(-1, 0);
		if (checkGameOver())
		{
			gameover = true;
			return;
		}
		checkEaten(food);
		updateTable(food);
		Sleep(300);
		system("CLS");
		printTable();
	}
}
void Snake::changeDirectionDown(int & i, int & j, Part &food)
{
	if (i < MAX_SIZE) {
		i++;
		for (int k = cnt_parts - 1; k >0; k--)
		{
			parts[k] = parts[k - 1];
		}
		parts[0].move(0, 1);
		if (checkGameOver())
		{
			gameover = true;
			return;
		}
		checkEaten(food);
		updateTable(food);
		Sleep(300);
		system("CLS");
		printTable();
	}
	else if (i == MAX_SIZE)
	{
		i= 1;
		for (int k = cnt_parts - 1; k >0; k--)
		{
			parts[k] = parts[k - 1];
		}
		parts[0].move(0, 1);
		if (checkGameOver())
		{
			gameover = true;
			return;
		}
		checkEaten(food);
		updateTable(food);
		Sleep(300);
		system("CLS");
		printTable();
	}
}
void Snake::changeDirectionUp(int & i, int & j, Part &food)
{
	if (i > 1) {
		i--;
		for(int k = cnt_parts - 1; k >0; k--)
		{
			parts[k] = parts[k - 1];
		}
		parts[0].move(0, -1);
		if (checkGameOver())
		{
			gameover = true;
			return;
		}
		checkEaten(food);
		updateTable(food);
		Sleep(300);
		system("CLS");
		printTable();
	}
	else if (i == 1)
	{
		i = MAX_SIZE;
		for (int k = cnt_parts - 1; k >0; k--)
		{
			parts[k] = parts[k - 1];
		}
		parts[0].move(0, -1);
		if (checkGameOver())
		{
			gameover = true;
			return;
		}
		checkEaten(food);
		updateTable(food);
		Sleep(300);
		system("CLS");
		printTable();
	}
}
void Snake::play()
{
	resizeParts();
	cnt_parts++;
	resizeParts();
	cnt_parts++;
	int x = MAX_SIZE, y = MAX_SIZE/2;
	parts[0].setXY(x, y);
	for (int i = 1; i < cnt_parts;i++)
		parts[i].setXY(x - i, y);
	char cur_move;
	Part food;
	food.setXY(rand() % MAX_SIZE, rand() % ((MAX_SIZE * 2) - 2));
	food.setPoints();
	updateTable(food);
	printTable();
	void(Snake::*direction)(int&, int&, Part &food);
	direction=&Snake::changeDirectionRight;
	bool isSwap = false;
	getHightPoints();
	while (true)
	{	
		std::cout << "Score: " << points <<"             High score: "<<high_points<< "\n";
		if (_kbhit()) {
			cur_move = _getch();
			if (cur_move == 'd'|| cur_move == 'D') {
				direction = &Snake::changeDirectionRight;
			}
			else if (cur_move == 'w' || cur_move == 'W') {
				direction = &Snake::changeDirectionUp;
			}
			else if (cur_move == 's' || cur_move == 'S') {
				direction = &Snake::changeDirectionDown;
			}
			else if (cur_move == 'a' || cur_move == 'A') {
				direction = &Snake::changeDirectionLeft;
			}
		}
		if(gameover)
		{
			std::cout << "Game over!!!\n";
			if (points > high_points)
			{
				std::cout << "New record!!!\n";
				setHightPoints();
			}
			std::cout<<"Your score is : " << points << std::endl;
			break;
		}
		(this->*direction)(x,y,food);
	}
}

void Snake::printTable()
{
	for (int i = 0; i < MAX_SIZE+2; i++)
	{
		for (int j = 0; j < MAX_SIZE*2; j++)
		{
			if (i == 0 || i == MAX_SIZE + 1)
			{
				std::cout <<table[i][j];
			}
			else std::cout<< table[i][j];
		}
	std::cout << std::endl;
	}
}

void Snake::getHightPoints()
{
	std::ifstream file("hight_scores.txt", std::ios::in);
	if (!file)return ;
	file >> this->high_points;
	file.close();
}

void Snake::setHightPoints()
{
	std::ofstream file("hight_scores.txt", std::ios::out);
	if (!file)return ;
	file << points;
	file.close();
}
