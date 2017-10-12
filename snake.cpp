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
	//ÅÐ¶ÏÊÇ·ñ×²µ½×Ô¼º
	for (auto it = snake.begin(); it != snake.end() - 1; it++)
		if (*it == head())
			return true;
	//ÅÐ¶ÏÊÇ·ñ×²Ç½
	if (head().Getx() >= 30 || head().Getx() <= 1
		|| head().Gety() >= 30 || head().Gety() <= 1)
		return true;
	return false;
}

size_t Snake::size()
{
	return snake.size();
}

void Snake::Eat(Point &p)
{
	push_back(p);
	p.SetShape(shape);
	p.SetColor(color);
	p.Print();
	for (auto it : snake)
	{
		it.SetShape(shape);
		it.SetColor(color);
		it.Print();
	}
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

	push_back(p);					//point add deque
	p.SetShape(shape);
	p.SetColor(color);
	p.Print();						//show this point

	snake[0].Clear();
	pop_front();
}

void Snake::show()
{
	for (auto p : snake)
	{
		p.SetShape(shape);
		p.SetColor(color);
		p.Print();
	}

}

void Snake::SetDirect(const string & d)
{
	direct = d;
}


