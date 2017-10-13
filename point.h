#pragma once
#include <windows.h>
#include <iostream>

using namespace std;
class Point
{
public:
	Point() = default;
	Point(int x, int y, char color = 'w', string shape = "■"):x(x), y(y), color(color), shape(shape){}
	void SetColor(char);	//设置点的颜色
	void SetShape(string);	//设置形状
	void ChangePos(int x, int y);		//改变点的位置
	bool Crash(const Point &p);
	void Clear();		//删除该点
	void Print();		//输出点
	int Getx() const{ return this->x; } 
	int Gety() const{ return this->y; }
protected:
	int x, y;
	char color;
	string shape;
};

inline bool operator==(const Point &p1, const Point &p2)
{
	if (p1.Getx() == p2.Getx() && p1.Gety() == p2.Gety())
		return true;
	else
		return false;
}

