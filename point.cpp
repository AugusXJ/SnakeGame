#include "point.h"
#include "window.h"

using namespace std;



void Point::Clear()
{
	SetCursorPosition(x, y);
	SetColor(color);
	cout << " ";
}

void Point::Print()
{
	SetCursorPosition(x, y);
	::SetColor(color);
	cout << shape;
}

void Point::SetColor(char c)
{
	color = c;
}

void Point::SetShape(string s)
{
	shape = s;
}

void Point::ChangePos(int x0, int y0)
{
	x = x0;
	y = y0;
}

bool Point::Crash(const Point & p)
{
	if (p.x == x && p.y == y)
		return true;
	else
		return false;
}

