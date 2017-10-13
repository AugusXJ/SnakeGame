#pragma once
#include <windows.h>
#include <iostream>

using namespace std;
class Point
{
public:
	Point() = default;
	Point(int x, int y, char color = 'w', string shape = "��"):x(x), y(y), color(color), shape(shape){}
	void SetColor(char);	//���õ����ɫ
	void SetShape(string);	//������״
	void ChangePos(int x, int y);		//�ı���λ��
	bool Crash(const Point &p);
	void Clear();		//ɾ���õ�
	void Print();		//�����
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

