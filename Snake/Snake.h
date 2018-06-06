#pragma once
#include "Part.h"

class Snake
{
public:
	Snake();
	~Snake();
	void resizeParts();
	void updateTable(Part &food);
	void clearTable();
	void checkEaten(Part &food);
	bool checkGameOver();
	void changeDirectionRight(int &i, int &j, Part &food);
	void changeDirectionLeft(int &i, int &j, Part &food);
	void changeDirectionUp(int &i, int &j, Part &food);
	void changeDirectionDown(int &i, int &j, Part &food);
	void(*direction)(int&, int&, Part &food);
	void play();
	void printTable();
	void getHightPoints();
	void setHightPoints();
private:
	Part *parts;
	int cnt_parts;
	char move;
	int points;
	int high_points;
	bool gameover;
};

