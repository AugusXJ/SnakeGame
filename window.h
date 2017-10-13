#pragma once
#include <sstream>
#include <string>
#include <windows.h>
#include<iostream>

using namespace std;
template <int col, int row> class Window
{
public:
	Window() { Show(); }
	void Show();
private:
	char color;
};

void SetColor(char s);
void SetCursorPosition(const int x, const int y);//���ù��λ��
void SetBackColor();//�����ı�����ɫ


template <int col, int row>
void Window<col, row>::Show()
{
	system("title ̰����");//���ô��ڱ���
	stringstream ss;
	ss << "mode con cols=" << col * 2 << " lines=" << row;
	cout << ss.str() << endl;
	system(const_cast<char*>(ss.str().c_str()));//system(mode con cols=88 lines=88)���ô��ڿ�Ⱥ͸߶�
	SetColor('w');
	system("cls");
}


/*
r -> red
g -> green
b -> blue
k -> black
c -> blue-green
m -> purple-red
y -> yellow
w -> white
*/

inline void SetColor(char s)
{
	switch(s)
	{
		case 'r':
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
				FOREGROUND_RED| FOREGROUND_INTENSITY);
			break;
		case 'g':
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
				FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case 'b':
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
				FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		case 'k':
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
			break;
		case 'c':
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
				FOREGROUND_GREEN |FOREGROUND_BLUE |FOREGROUND_INTENSITY);
			break;
		case 'm':
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
				FOREGROUND_BLUE |FOREGROUND_RED |FOREGROUND_INTENSITY);
			break;
		case 'y':
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
				FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case 'w':
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
				FOREGROUND_RED |FOREGROUND_GREEN |FOREGROUND_BLUE |FOREGROUND_INTENSITY);
			break;
		default:
			throw runtime_error("wrong color");
			break;
	}
}

inline void SetBackColor()//�����ı�����ɫ
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE |
		BACKGROUND_BLUE |
		BACKGROUND_GREEN |
		BACKGROUND_RED);
}

inline void SetCursorPosition(const int x, const int y)//���ù��λ��
{
	COORD position;
	position.X = x * 2;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}