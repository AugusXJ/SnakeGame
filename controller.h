#pragma once
#include <Windows.h>
#include "food.h"
class Controller
{
public:
	Controller() : speed(200), key(1), score(0) {}
	void Play();
	void UpdateScore(const int&);
	void RewriteScore();
	int Menu();
	void Game();
	int GameOver();
protected:
	int speed;
	int score;
	char color;
	int key;
};

class SelectInterface : Controller
{
public:
	SelectInterface() = default;
	void Play();
private: 
	void Select_Move(int &key, char ch);
	void Select_Print(int key, bool ifTouched);
};

class GameInterface : Controller
{
public:
	void DrawGame();
	int PlayGame();
private:
};