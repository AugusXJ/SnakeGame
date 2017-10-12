#include "food.h"

void Food::Draw(Snake &s)
{
	default_random_engine e;
	uniform_int_distribution<> u(1, 29);
	while (true)
	{
		x = u(e); y = u(e);
		if (!s.ifExistPoint(*this))
			break;
	}
	Print();
}
