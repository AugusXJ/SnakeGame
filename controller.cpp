#include <conio.h>
#include "controller.h"
#include "window.h"
#include "point.h"
#include "snake.h"

using namespace std;

void Controller::Play()
{
	SelectInterface sif;
	sif.Play();				//ѡ����
	GameInterface gif;
	gif.DrawGame();

}



void SelectInterface::Play()
{
	Window<41, 32> win;
	color = 'y';
	SetColor(color);
	SetCursorPosition(6, 21);
	std::cout << "��ѡ����Ϸ�Ѷȣ�";
	SetCursorPosition(6, 22);
	std::cout << "(���¼�ѡ��,�س�ȷ��)";

	/*��������Ѷ�ѡ��
	key = 1 -> ���Ѷ�
	key = 2 -> ��ͨ�Ѷ�
	key = 3 -> �����Ѷ�
	key = 4 -> �����Ѷ�
	*/
	for(int key=2; key<5; key++)
		Select_Print(key, false);
	Select_Print(1, true);

	//�����¼����п���
	int ch;
	int key = 1;

	//ѡ������Ϸ��ƶ�����
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
			if (ch == 13)		//����س�������
				break;
			Select_Move(key, ch);
		}
	}

	//�������յ�keyȷ���ߵ��ٶ�
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

	SetCursorPosition(0, 31);//������������½ǣ�����ر���˸Ӱ����Ϸ����
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
		cout << "���Ѷ�";
		break;
	case 2:
		cout << "��ͨ�Ѷ�";	
		break;
	case 3:
		cout << "�����Ѷ�";
		break;
	case 4:
		cout << "�����Ѷ�";
		break;
	default:
		break;
	}

}

void GameInterface::DrawGame()//������Ϸ����
{
	system("cls");//����

	/*���Ƶ�ͼ*/
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
		

	/*���Ʋ����*/
	SetColor('r');
	SetCursorPosition(33, 1);
	std::cout << "Greedy Snake";
	SetCursorPosition(34, 2);
	std::cout << "̰����";
	SetCursorPosition(31, 4);
	std::cout << "�Ѷȣ�";
	SetCursorPosition(36, 5);
	switch (key)
	{
	case 1:
		std::cout << "��ģʽ";
		break;
	case 2:
		std::cout << "��ͨģʽ";
		break;
	case 3:
		std::cout << "����ģʽ";
		break;
	case 4:
		std::cout << "����ģʽ";
		break;
	default:
		break;
	}
	SetCursorPosition(31, 7);
	std::cout << "�÷֣�";
	SetCursorPosition(37, 8);
	std::cout << "     0";
	SetCursorPosition(33, 13);
	std::cout << " ������ƶ�";
	SetCursorPosition(33, 15);
	std::cout << " ESC����ͣ";
}

int GameInterface::PlayGame()
{
	/*��ʼ���ߺ�ʳ��*/
	Snake snake;
	snake.push_back(Point(4,1));
	snake.SetDirect("down");
	Food food; food.Draw(snake);

	/*��Ϸѭ��*/
	while (!snake.ifDead()) //�ж��Ƿ�ײǽ��ײ���������Ƿ�������
	{
		/*����ѡ��˵�*/
		if (!csnake->ChangeDirection()) //��Esc��ʱ
		{
			int tmp = Menu();//���Ʋ˵������õ�����ֵ
			switch (tmp)
			{
			case 1://������Ϸ
				break;

			case 2://���¿�ʼ
				delete csnake;
				delete cfood;
				return 1;//��1��ΪPlayGame�����ķ���ֵ���ص�Game�����У���ʾ���¿�ʼ

			case 3://�˳���Ϸ
				delete csnake;
				delete cfood;
				return 2;//��2��ΪPlayGame�����ķ���ֵ���ص�Game�����У���ʾ�˳���Ϸ

			default:
				break;
			}
		}

		if (csnake->GetFood(*cfood)) //�Ե�ʳ��
		{
			csnake->Move();//������
			UpdateScore(1);//���·�����1Ϊ����Ȩ��
			RewriteScore();//���»��Ʒ���
			cfood->DrawFood(*csnake);//������ʳ��
		}
		else
		{
			csnake->NormalMove();//�������ƶ�
		}

		if (csnake->GetBigFood(*cfood)) //�Ե���ʱʳ��
		{
			csnake->Move();
			UpdateScore(cfood->GetProgressBar() / 5);//����������ʱʳ�������ȷ��
			RewriteScore();
		}

		if (cfood->GetBigFlag()) //�����ʱ����ʱʳ���˸��
		{
			cfood->FlashBigFood();
		}

		Sleep(speed);//�����ߵ��ƶ�Ч��
	}

	/*������*/
	delete csnake;//�ͷŷ�����ڴ�ռ�
	delete cfood;
	int tmp = GameOver();//������Ϸ�������棬��������ѡ��
	switch (tmp)
	{
	case 1:
		return 1;//���¿�ʼ
	case 2:
		return 2;//�˳���Ϸ
	default:
		return 2;
	}
}