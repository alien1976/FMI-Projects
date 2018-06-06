#pragma once
class Part
{
public:
	Part();
	Part &operator=(const Part&rhs);
	~Part();
	bool operator==(const Part& rhs);
	void setXY(int x, int y);
	void setPoints();
	int getPoints() { return points; }
	char getC() { return c; }
	int getX() { return x; }
	int getY() { return y; }
	void move(int x, int y);
private:
	char c;
	int x;
	int y;
	int points;
};

