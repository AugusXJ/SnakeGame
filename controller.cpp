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
		sif.Play();				//ѡ����
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
	key = 1;

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
		if (_kbhit())
		{
			ch = _getch();
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
	OutLevel(key);

}

void GameInterface::DrawGame()//������Ϸ����
{
	Window<41, 32> win;
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
	OutLevel(key);			//�����Ѷ���
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
	snake.push_back(Point(4,2));snake.push_back(Point(4,3));
	snake.show();
	snake.SetDirect("down");
	Food food; 
	food.Draw(snake);

	/*��Ϸѭ��*/
	while (!snake.ifDead()) //�ж��Ƿ�ײǽ��ײ���������Ƿ�������
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
				GamePause();				//ϵͳ��ͣ
			default:
				break;
			}
		}
		if (snake.ifGetFood(food)) //�Ե�ʳ��
		{
			snake.Eat();//������
			UpdateScore();//���·�����1Ϊ����Ȩ��
			RewriteScore();//���»��Ʒ���
			food.Draw(snake);//������ʳ��
		}
		snake.Move();
		Sleep(speed);//�����ߵ��ƶ�Ч��
	}

	//*������*/
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

void GameInterface::RewriteScore()//�ػ����
{
	/*Ϊ���ַ���β�����룬������������Ϊ6λ�����㵱ǰ����λ������ʣ��λ���ÿո�ȫ�����������*/
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
	cout << "������Ϸ";
	SetColor('b');
	SetCursorPosition(33, 22);
	cout << "�˳���Ϸ";

	int ch;
	while (ch = _getch())
	{
		switch (ch)
		{
		case 72:
			key = 1;
			SetBackColor();
			SetCursorPosition(33, 20);
			cout << "������Ϸ";
			SetColor('b');
			SetCursorPosition(33, 22);
			cout << "�˳���Ϸ";
			break;
		case 80:
			key = 2;
			SetColor('b');
			SetCursorPosition(33, 20);
			cout << "������Ϸ";
			SetBackColor();
			SetCursorPosition(33, 22);
			cout << "�˳���Ϸ";
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
	//�߿�
	for (int i = 8; i <= 15; i++)
	{
		Point(i, 8, 'c', "��").Print();
		Point(30-i, 8, 'c', "��").Print();
		Sleep(20);
	}
	for (int i = 9; i <= 18; i++)
	{
		Point(8, i, 'c', "��").Print();
		Point(22, i, 'c', "��").Print();
		Sleep(20);
	}
	for (int i = 8; i <= 15; i++)
	{
		Point(i, 18, 'c', "��").Print();
		Point(30 - i, 18, 'c', "��").Print();
		Sleep(20);
	}
	SetColor('w');
	SetCursorPosition(13, 10);
	cout << "��Ϸ����";
	SetCursorPosition(10, 12);
	cout << "��ķ���Ϊ��   " << score;
	SetCursorPosition(10, 14);
	cout << "����������";
	SetCursorPosition(10, 16);
	SetBackColor();			//����yes����ɫ
	cout << "Yes";
	SetColor('w');			//���¸�����ɫ
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
			SetColor('w');			//���¸�����ɫ
			SetCursorPosition(18, 16);
			cout << "No";
			SetCursorPosition(10, 16);
			SetBackColor();			//����yes����ɫ
			cout << "Yes";
			break;
		case 77:
			choice = 2;
			SetColor('w');			//���¸�����ɫ
			SetCursorPosition(10, 16);
			cout << "Yes";
			SetCursorPosition(18, 16);
			SetBackColor();			//����No����ɫ
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
