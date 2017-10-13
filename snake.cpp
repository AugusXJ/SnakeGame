#include "snake.h"
#include "window.h"

using namespace std;

void Snake::push_back(const Point &p)
{
	snake.push_back(p);
}

void Snake::pop_front()
{
	snake.pop_front();
}

bool Snake::ifExistPoint(const Point &p)
{
	for (auto i : snake)
		if (i == p)
			return true;
	return false;
}

bool Snake::ifDead()
{
	//判断是否撞到自己
	for (auto it = snake.begin(); it != snake.end() - 1; it++)
		if (*it == head())
			return true;
	//判断是否撞墙
	if (head().Getx() >= 30 || head().Getx() <= 1
		|| head().Gety() >= 30 || head().Gety() <= 1)
		return true;
	return false;
}

size_t Snake::size()
{
	return snake.size();
}

void Snake::Eat()
{
	//蛇的末尾增加一格子
	int end_x = 2 * snake[0].Getx() - snake[1].Getx();
	int end_y = 2 * snake[0].Gety() - snake[1].Gety();
	Point temp(end_x, end_y,color,shape);
	snake.push_front(temp);
	temp.Print();
}

void Snake::Move()
{
	Point p;
	deque<Point>::iterator pit = snake.end() - 1;
	if (direct == "up")
		p.ChangePos(pit->Getx(), pit->Gety() - 1);
	else if (direct == "down")
		p.ChangePos(pit->Getx(), pit->Gety() + 1);
	else if (direct == "left")
		p.ChangePos(pit->Getx() - 1, pit->Gety());
	else if (direct == "right")
		p.ChangePos(pit->Getx() + 1, pit->Gety());
	else
		throw runtime_error("direct is wrong");

	//更改首元素的颜色
	head().Clear();
	head().SetColor(color);
	head().Print();


	p.SetShape(shape);
	p.SetColor('y');
	p.Print();						//show this point
	push_back(p);					//point add deque

	snake[0].Clear();
	pop_front();
}

void Snake::show()
{
	for (auto it = snake.begin(); it != snake.end() - 1; it++)
	{
		it->SetShape(shape);
		it->SetColor(color);
		it->Print();
	}
	head().SetColor('y');
	head().SetShape(shape);
	head().Print();
}

void Snake::SetDirect(const string & d)
{
	direct = d;
}


