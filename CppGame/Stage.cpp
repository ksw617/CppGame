#include "Stage.h"
#include "DoubleBuffer.h"
#include "Player.h"
#include "Bullet.h"

void Stage::Initialize()
{
	player = new Player;
	player->Initialize();

	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullets[i] = new Bullet;
		bullets[i]->Initialize();
	}
}

void Stage::Progress()
{
	player->Progress();

	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullets[i]->Progress();
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		for (int i = 0; i < BULLET_COUNT; i++)
		{
			if (!bullets[i]->GetAct())
			{
				bullets[i]->SetActive(true, player->GetX() + 1, player->GetY());
				break;
			}
			
		}

	}
}

void Stage::Render()
{
	player->Render();

	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullets[i]->Render();
	}
}

void Stage::Release()
{
	player->Release();
	delete player;
	player = nullptr;

	for (int i = 0; i < BULLET_COUNT; i++)
	{
		bullets[i]->Release();
		delete bullets[i];
		bullets[i] = nullptr;
	}
}
