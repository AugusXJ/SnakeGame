#pragma once
#include <deque>
#include "point.h"

using namespace std;

class Snake
{
public:
	Snake() = default;
	void Eat(Point &);
	void Move();
	void show();
	Point& head() { return snake[snake.size() - 1]; }	//·µ»ØÍ·ÔªËØ
	void SetDirect(const string &d);
	string& GetDirect() { return direct; }
	void push_back(const Point &);
	void pop_front();
	bool ifExistPoint(const Point &);
	bool ifDead();
	size_t size();
private:
	deque<Point> snake;
	string direct;
	const string shape = "¡ñ";
	const char color = 'g';
};