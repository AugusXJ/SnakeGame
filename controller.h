#pragma once
#include <Windows.h>
#include "food.h"
class Controller
{
public:
	Controller() : speed(200), key(1), score(0) {}
	void Play();
protected:
	void OutLevel(int key);
	int speed;
	int score;
	char color;
	int key;
};

class SelectInterface : public Controller
{
public:
	SelectInterface() = default;
	void Play();
private: 
	void Select_Move(int &key, char ch);
	void Select_Print(int key, bool ifTouched);
};

class GameInterface : public Controller
{
public:
	void DrawGame();
	int PlayGame();
private:
	void UpdateScore() { score += key * 10; }
	void RewriteScore();
	void GamePause();
	int GameOver();
};