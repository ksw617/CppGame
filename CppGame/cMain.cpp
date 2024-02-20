#include <stdio.h>
#include <Windows.h>

#pragma region Enum
enum COLOR
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE,

};

#pragma endregion

#pragma region Struct

struct Obj
{
	bool act;
	int x;
	int y;
	COLOR color;
	const char* shape;
};

#pragma endregion



#pragma region Game
#define BulletCount 4
#define EnemyCount 3
Obj* bullets[BulletCount] = {};
Obj* enemies[EnemyCount] = {};
Obj* player = nullptr;
void StageInitialize();
void StageProgress();
void StageRender();
void StageRelease();
#pragma endregion

#pragma region WIN_API
void MovePos(int x, int y);
void Paint(int color);
void HideCursor();

#pragma endregion

int main()
{
	HideCursor();
	StageInitialize();

	while (true)
	{
		system("cls");
		StageProgress();
		StageRender();
		Sleep(50);	  
	}

	StageRelease();

	return 0;
}

#pragma region Stage

void StageInitialize()
{
	player = (Obj*)malloc(sizeof(Obj));
	player->x = 10;
	player->y = 10;
	player->color = YELLOW;
	player->shape = "¿Ê";

	for (int i = 0; i < BulletCount; i++)
	{
		bullets[i] = (Obj*)malloc(sizeof(Obj));
		bullets[i]->act = false;
		bullets[i]->x = i;
		bullets[i]->y = 0;
		bullets[i]->color = RED;
		bullets[i]->shape = "¡Ü";
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		enemies[i] = (Obj*)malloc(sizeof(Obj));
		enemies[i]->act = false;
		enemies[i]->x = rand() % 30;
		enemies[i]->y = rand() % 30;
		enemies[i]->color = LIGHTBLUE;
		enemies[i]->shape = "º¿";
	}

}

int index = 0;

void StageProgress()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		player->x--;
	} 
	if (GetAsyncKeyState(VK_RIGHT))
	{
		player->x++;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		player->y--;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		player->y++;
	}

	if (GetAsyncKeyState(VK_RETURN))
	{

		for (int i = 0; i < BulletCount; i++)
		{
			if (bullets[i]->act == false)
			{
				bullets[i]->x = player->x;
				bullets[i]->y = player->y;
				bullets[i]->act = true;
				break;
			}

		}
	}

	for (int i = 0; i < BulletCount; i++)
	{
		if (bullets[i]->act == true)
		{
			bullets[i]->x++;
			if (bullets[i]->x >= 38)
			{
				bullets[i]->act = false;
			}

			//for (int j = 0; j < EnemyCount; j++)
			//{
			//	if (bullets[i]->x == enemies[j]->x && bullets[i]->y == enemies[j]->y)
			//	{
			//		enemies[j]->act = false;
			//	}
			//}
		}
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		if (!enemies[i]->act)
		{
			enemies[i]->x = rand() % 30;
			enemies[i]->y = rand() % 30;
			enemies[i]->act = true;
			break;
		}

	}

	for (int i = 0; i < EnemyCount; i++)
	{
		if (enemies[i]->act == true)
		{
			for (int j = 0; i < BulletCount; i++)
			{
				if (bullets[j]->x == enemies[i]->x && bullets[j]->y == enemies[i]->y)
				{
					enemies[i]->act = false;
				}
			}
		}
	}
	
}


void StageRender()
{
	MovePos(player->x, player->y);
	Paint(player->color);
	printf(player->shape);

	for (int i = 0; i < BulletCount; i++)
	{
		MovePos(bullets[i]->x, bullets[i]->y);
		Paint(bullets[i]->color);
		printf(bullets[i]->shape);
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		if (enemies[i]->act)
		{
			MovePos(enemies[i]->x, enemies[i]->y);
			Paint(enemies[i]->color);
			printf(enemies[i]->shape);
		}

	}

}

void StageRelease()
{
}
#pragma endregion

#pragma region WIN_API
void MovePos(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Paint(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void HideCursor()
{

	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;
	info.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

}


#pragma endregion

