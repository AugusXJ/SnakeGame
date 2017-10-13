#include "food.h"
#include "snake.h"

void Food::Draw(Snake &s)
{
	random_device e;
	uniform_int_distribution<> u(2, 29);
	while (true)
	{
		x = u(e); y = u(e);
		if (!s.ifExistPoint(*this))
			break;
	}
	Print();
}
