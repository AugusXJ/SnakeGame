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
	Point& head() { return snake[snake.size() - 1]; }	//����ͷԪ��
	void SetDirect(const string &d);					//�ı䷽��
	string& GetDirect() { return direct; }
	void push_back(const Point &);
	void pop_front();
	bool ifExistPoint(const Point &);
	bool ifDead();
	size_t size();
	bool ifGetFood(const Food &f) { return head() == f; };	//�Ƿ�õ�ʳ��
private:
	deque<Point> snake;
	string direct;
	const string shape = "��";
	const char color = 'g';
};