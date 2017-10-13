#pragma once
#include <deque>
#include "point.h"
#include "food.h"

using namespace std;

class Snake
{
public:
	Snake() = default;
	void Eat();
	void Move();
	void show();
	Point& head() { return snake[snake.size() - 1]; }	//返回头元素
	void SetDirect(const string &d);					//改变方向
	string& GetDirect() { return direct; }
	void push_back(const Point &);
	void pop_front();
	bool ifExistPoint(const Point &);
	bool ifDead();
	size_t size();
	bool ifGetFood(const Food &f) { return head() == f; };	//是否得到食物
private:
	deque<Point> snake;
	string direct;
	const string shape = "●";
	const char color = 'g';
};