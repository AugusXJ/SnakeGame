#pragma once
#include <string>
#include <random>
#include "point.h"


using namespace std;
class Food : Point
{
	friend class Snake;
public:
	Food()  { color = 'y'; shape = "ก็"; }
	void Draw(Snake&);
private:

};