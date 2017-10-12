#include <conio.h>
#include "controller.h"
#include "window.h"
#include "point.h"
#include "snake.h"

using namespace std;

void Controller::Play()
{
	SelectInterface sif;
	sif.Play();				//选择画面
	GameInterface gif;
	gif.DrawGame();

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
	int key = 1;

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
		if (ch = _getch())
		{
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
	switch (key)
	{
	case 1:
		cout << "简单难度";
		break;
	case 2:
		cout << "普通难度";	
		break;
	case 3:
		cout << "困难难度";
		break;
	case 4:
		cout << "炼狱难度";
		break;
	default:
		break;
	}

}

void GameInterface::DrawGame()//绘制游戏界面
{
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
	snake.push_back(Point(4,1));
	snake.SetDirect("down");
	Food food; food.Draw(snake);

	/*游戏循环*/
	while (!snake.ifDead()) //判断是否撞墙或撞到自身，即是否还有生命
	{
		/*调出选择菜单*/
		if (!csnake->ChangeDirection()) //按Esc键时
		{
			int tmp = Menu();//绘制菜单，并得到返回值
			switch (tmp)
			{
			case 1://继续游戏
				break;

			case 2://重新开始
				delete csnake;
				delete cfood;
				return 1;//将1作为PlayGame函数的返回值返回到Game函数中，表示重新开始

			case 3://退出游戏
				delete csnake;
				delete cfood;
				return 2;//将2作为PlayGame函数的返回值返回到Game函数中，表示退出游戏

			default:
				break;
			}
		}

		if (csnake->GetFood(*cfood)) //吃到食物
		{
			csnake->Move();//蛇增长
			UpdateScore(1);//更新分数，1为分数权重
			RewriteScore();//重新绘制分数
			cfood->DrawFood(*csnake);//绘制新食物
		}
		else
		{
			csnake->NormalMove();//蛇正常移动
		}

		if (csnake->GetBigFood(*cfood)) //吃到限时食物
		{
			csnake->Move();
			UpdateScore(cfood->GetProgressBar() / 5);//分数根据限时食物进度条确定
			RewriteScore();
		}

		if (cfood->GetBigFlag()) //如果此时有限时食物，闪烁它
		{
			cfood->FlashBigFood();
		}

		Sleep(speed);//制造蛇的移动效果
	}

	/*蛇死亡*/
	delete csnake;//释放分配的内存空间
	delete cfood;
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