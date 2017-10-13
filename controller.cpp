#include <conio.h>
#include "controller.h"
#include "window.h"
#include "point.h"
#include "snake.h"

using namespace std;

void Controller::Play()
{
	while (true)
	{
		SelectInterface sif;
		sif.Play();				//选择画面
		GameInterface gif;
		gif.key = sif.key;
		gif.speed = sif.speed;
		gif.DrawGame();
		int temp = gif.PlayGame();
		if (temp == 2)
			break;
	}


}

void Controller::OutLevel(int key)
{
	switch (key)
	{
	case 1:
		std::cout << "简单模式";
		break;
	case 2:
		std::cout << "普通模式";
		break;
	case 3:
		std::cout << "困难模式";
		break;
	case 4:
		std::cout << "炼狱模式";
		break;
	default:
		break;
	}
}

void SelectInterface::Play()
{
	Window<41, 32> win;
	color = 'y';
	SetColor(color);
	SetCursorPosition(6, 21);
	std::cout << "请选择游戏难度：";
	SetCursorPosition(6, 22);
	std::cout << "(上下键选择,回车确认)";

	/*输出几种难度选择
	key = 1 -> 简单难度
	key = 2 -> 普通难度
	key = 3 -> 困难难度
	key = 4 -> 炼狱难度
	*/
	for(int key=2; key<5; key++)
		Select_Print(key, false);
	Select_Print(1, true);

	//以上下键进行控制
	int ch;
	key = 1;

	//选择界面上方移动的蛇
	Snake snake;
	snake.push_back(Point(10, 5));
	snake.push_back(Point(11, 5));
	snake.push_back(Point(12, 5));
	snake.push_back(Point(13, 5));
	snake.push_back(Point(14, 5));
	snake.push_back(Point(15, 5));
	snake.push_back(Point(16, 5));
	snake.push_back(Point(17, 5));
	snake.push_back(Point(18, 5));
	snake.SetDirect("right");
	snake.show();
	while (true)
	{
		snake.Move();
		if (snake.GetDirect() == "right" && snake.head() == Point(30, 5))
			snake.SetDirect("down");
		if(snake.GetDirect() == "down" && snake.head() == Point(30, 15))
			snake.SetDirect("left");
		if (snake.GetDirect() == "left" && snake.head() == Point(10, 15))
			snake.SetDirect("up");
		if (snake.GetDirect() == "up" && snake.head() == Point(10, 5))
			snake.SetDirect("right");
		Sleep(30);
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 13)		//输出回车键跳出
				break;
			Select_Move(key, ch);
		}
	}

	//根据最终的key确定蛇的速度
	switch (key)
	{
	case 1:
		speed = 135;
		break;
	case 2:
		speed = 100;
		break;
	case 3:
		speed = 60;
		break;
	case 4:
		speed = 30;
		break;
	default:
		break;
	}

	SetCursorPosition(0, 31);//将光标置于左下角，避免关标闪烁影响游戏体验
}

void SelectInterface::Select_Move(int &key, char ch)
{
	switch (ch)
	{
	case 72:
		if (key > 1)
		{
			Select_Print(key, false);
			key = key - 1;
			Select_Print(key, true);
		}
		break;
	case 80:
		if (key < 4)
		{
			Select_Print(key, false);
			key = key + 1;
			Select_Print(key, true);
		}
		break;
	default:
		break;
	}
}

void SelectInterface::Select_Print(int key, bool ifTouched)
{
	int col = 30;
	int row = key * 2 + 20;
	SetCursorPosition(col, row);
	if (ifTouched == false)
		SetColor(color);
	else
		SetBackColor();
	OutLevel(key);

}

void GameInterface::DrawGame()//绘制游戏界面
{
	Window<41, 32> win;
	system("cls");//清屏

	/*绘制地图*/
	SetColor('r');
	for (int i = 1; i < 31; i++)
	{
		Point(i, 1).Print();
		Point(i, 30).Print();
		Sleep(10);
	}
	for (int i = 2; i < 30; i++)
	{
		Point(1, i).Print();
		Point(30, i).Print();
		Sleep(10);
	}
		

	/*绘制侧边栏*/
	SetColor('r');
	SetCursorPosition(33, 1);
	std::cout << "Greedy Snake";
	SetCursorPosition(34, 2);
	std::cout << "贪吃蛇";
	SetCursorPosition(31, 4);
	std::cout << "难度：";
	SetCursorPosition(36, 5);
	OutLevel(key);			//绘制难度线
	SetCursorPosition(31, 7);
	std::cout << "得分：";
	SetCursorPosition(37, 8);
	std::cout << "     0";
	SetCursorPosition(33, 13);
	std::cout << " 方向键移动";
	SetCursorPosition(33, 15);
	std::cout << " ESC键暂停";
}

int GameInterface::PlayGame()
{
	/*初始化蛇和食物*/
	Snake snake;
	snake.push_back(Point(4,2));snake.push_back(Point(4,3));
	snake.show();
	snake.SetDirect("down");
	Food food; 
	food.Draw(snake);

	/*游戏循环*/
	while (!snake.ifDead()) //判断是否撞墙或撞到自身，即是否还有生命
	{
		if (_kbhit())
		{
			int ch = _getch();
			switch (ch)
			{
			case 72:
				if(snake.GetDirect()!="down")
					snake.SetDirect("up");
				break;
			case 80:
				if (snake.GetDirect() != "up")
					snake.SetDirect("down");
				break;
			case 75:
				if (snake.GetDirect() != "right")
					snake.SetDirect("left");
				break;
			case 77:
				if (snake.GetDirect() != "left")
					snake.SetDirect("right");
				break;
			case 27:
				GamePause();				//系统暂停
			default:
				break;
			}
		}
		if (snake.ifGetFood(food)) //吃到食物
		{
			snake.Eat();//蛇增长
			UpdateScore();//更新分数，1为分数权重
			RewriteScore();//重新绘制分数
			food.Draw(snake);//绘制新食物
		}
		snake.Move();
		Sleep(speed);//制造蛇的移动效果
	}

	//*蛇死亡*/
	int tmp = GameOver();//绘制游戏结束界面，并返回所选项
	switch (tmp)
	{
	case 1:
		return 1;//重新开始
	case 2:
		return 2;//退出游戏
	default:
		return 2;
	}
}

void GameInterface::RewriteScore()//重绘分数
{
	/*为保持分数尾部对齐，将最大分数设置为6位，计算当前分数位数，将剩余位数用空格补全，再输出分数*/
	SetCursorPosition(37, 8);
	SetColor('r');
	int bit = 0;
	int tmp = score;
	while (tmp != 0)
	{
		++bit;
		tmp /= 10;
	}
	for (int i = 0; i < (6 - bit); ++i)
	{
		std::cout << " ";
	}
	std::cout << score;
}

void GameInterface::GamePause()
{
	int key = 1;
	SetBackColor();
	SetCursorPosition(33, 20);
	cout << "继续游戏";
	SetColor('b');
	SetCursorPosition(33, 22);
	cout << "退出游戏";

	int ch;
	while (ch = _getch())
	{
		switch (ch)
		{
		case 72:
			key = 1;
			SetBackColor();
			SetCursorPosition(33, 20);
			cout << "继续游戏";
			SetColor('b');
			SetCursorPosition(33, 22);
			cout << "退出游戏";
			break;
		case 80:
			key = 2;
			SetColor('b');
			SetCursorPosition(33, 20);
			cout << "继续游戏";
			SetBackColor();
			SetCursorPosition(33, 22);
			cout << "退出游戏";
			break;
		case 13:
			if (key == 1)
			{
				SetColor('b');
				SetCursorPosition(33, 20);
				cout << "        ";
				SetCursorPosition(33, 22);
				cout << "        ";
				return;
			}
			else if (key == 2)
				exit(1);
		default:
			break;
		}
	}
	

}

int GameInterface::GameOver()
{
	//边框
	for (int i = 8; i <= 15; i++)
	{
		Point(i, 8, 'c', "■").Print();
		Point(30-i, 8, 'c', "■").Print();
		Sleep(20);
	}
	for (int i = 9; i <= 18; i++)
	{
		Point(8, i, 'c', "■").Print();
		Point(22, i, 'c', "■").Print();
		Sleep(20);
	}
	for (int i = 8; i <= 15; i++)
	{
		Point(i, 18, 'c', "■").Print();
		Point(30 - i, 18, 'c', "■").Print();
		Sleep(20);
	}
	SetColor('w');
	SetCursorPosition(13, 10);
	cout << "游戏结束";
	SetCursorPosition(10, 12);
	cout << "你的分数为：   " << score;
	SetCursorPosition(10, 14);
	cout << "重新来过？";
	SetCursorPosition(10, 16);
	SetBackColor();			//设置yes背景色
	cout << "Yes";
	SetColor('w');			//重新更改颜色
	SetCursorPosition(18, 16);
	cout << "No";

	int ch;
	int choice = 1;
	while (ch = _getch())
	{
		switch (ch)
		{
		case 75:
			choice = 1;
			SetColor('w');			//重新更改颜色
			SetCursorPosition(18, 16);
			cout << "No";
			SetCursorPosition(10, 16);
			SetBackColor();			//设置yes背景色
			cout << "Yes";
			break;
		case 77:
			choice = 2;
			SetColor('w');			//重新更改颜色
			SetCursorPosition(10, 16);
			cout << "Yes";
			SetCursorPosition(18, 16);
			SetBackColor();			//设置No背景色
			cout << "No";
			break;
		case 13:
			return choice;
		default:
			break;
		}
	}
	
	
		
	return 0;
}
