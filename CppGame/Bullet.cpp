#include "Bullet.h"
#include "DoubleBuffer.h"

void Bullet::Initialize()
{
	act = false;
	x = 0;
	y = 0;
	color = RED;
	shape = "£À";
}

void Bullet::Progress()
{
	if (act)
	{
		x++;

		if (x >= 40)
		{
			act = false;
			x = 0;
		}
	}
}

void Bullet::Render()
{
	if (act)
	{
		DoubleBuffer::Get().WriteBuffer(x, y, shape, color);
	}
}

void Bullet::Release()
{
}
