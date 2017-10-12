#pragma once
#include <string>
#include <random>
#include "point.h"
#include "snake.h"

using namespace std;
class Food : Point
{
	friend class Snake;
public:
	void Draw(Snake&);
private:
	const string shape = "ก็";
	const char color = 'y';
};