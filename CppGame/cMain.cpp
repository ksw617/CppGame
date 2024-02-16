#include <stdio.h>
#include <Windows.h>

#define BulletCount 10
#define EnemyCount 10

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
struct Info
{
	int x;
	int y;
	COLOR color;

};

struct Bullet
{
	bool act;
	Info info;
	const char* shape;
};

struct Enemy
{
	bool act;
	int x;
	int y;
	COLOR color;
	const char* shape[3];
};

struct Obj
{
	int x;
	int y;
	COLOR color;	  //Info
	int aniIndex;
	const char* shape[10][3];

};
#pragma endregion


#pragma region Game
Obj* player = nullptr;	  
Bullet* bullets[BulletCount] = {}; 
Enemy* enemies[EnemyCount] = {};


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
		Sleep(20);	   //20ms

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
	player->color = WHITE;
	player->aniIndex = 0;
	player->shape[0][0] = "   -----|-----";
	player->shape[0][1] = "*>=====[_]L)";
	player->shape[0][2] = "      -'-`-";

	player->shape[1][0] = "    ----|---- ";
	player->shape[1][1] = "*>=====[_]L)";
	player->shape[1][2] = "      -'-`-";

	player->shape[2][0] = "     ---|---  ";
	player->shape[2][1] = "*>=====[_]L)";
	player->shape[2][2] = "      -'-`-";

	player->shape[3][0] = "      --|--   ";
	player->shape[3][1] = "*>=====[_]L)";
	player->shape[3][2] = "      -'-`-";

	player->shape[4][0] = "       -|-    ";
	player->shape[4][1] = "*>=====[_]L)";
	player->shape[4][2] = "      -'-`-";

	player->shape[5][0] = "        +     ";
	player->shape[5][1] = "*>=====[_]L)";
	player->shape[5][2] = "      -'-`-";

	player->shape[6][0] = "       -|-    ";
	player->shape[6][1] = "*>=====[_]L)";
	player->shape[6][2] = "      -'-`-";

	player->shape[7][0] = "      --|--   ";
	player->shape[7][1] = "*>=====[_]L)";
	player->shape[7][2] = "      -'-`-";

	player->shape[8][0] = "     ---|---  ";
	player->shape[8][1] = "*>=====[_]L)";
	player->shape[8][2] = "      -'-`-";

	player->shape[9][0] = "    ----|---- ";
	player->shape[9][1] = "*>=====[_]L)";
	player->shape[9][2] = "      -'-`-";

	for (int i = 0; i < BulletCount; i++)
	{
		bullets[i] = (Bullet*)malloc(sizeof(Bullet));
		bullets[i]->act = false;
		bullets[i]->info.x = i;
		bullets[i]->info.y = 0;
		bullets[i]->info.color = LIGHTBLUE;
		bullets[i]->shape = "��";
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		enemies[i] = (Enemy*)malloc(sizeof(Enemy));
		enemies[i]->act = true;
		enemies[i]->x = rand() % 20 + 20;
		enemies[i]->y = rand() % 30;
		enemies[i]->color = (COLOR)(rand() % 14 + 1);
		enemies[i]->shape[0] = "������";
		enemies[i]->shape[1] = "������";
		enemies[i]->shape[2] = "������";
	}

}

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

	if (GetAsyncKeyState(VK_SPACE))
	{
		for (int i = 0; i < BulletCount; i++)
		{
			if (bullets[i]->act == false)
			{

				bullets[i]->info.x = player->x + 6;
				bullets[i]->info.y = player->y + 1; 
				bullets[i]->act = true;
				break;
			}
		}
	}

	for (int i = 0; i < BulletCount; i++)
	{
		//if (bullets[i]->act)
		if (bullets[i]->act == true)
		{
			bullets[i]->info.x++;
			if (bullets[i]->info.x >= 40)
			{
				bullets[i]->info.x = i;
				bullets[i]->info.y = 0;
				bullets[i]->act = false;
			}
		}
	}
}

int stageCount = 0;

void StageRender()
{
	stageCount++;
	if (stageCount == 3)
	{
		player->aniIndex++;

		player->aniIndex %= 10;
		stageCount = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		MovePos(player->x, player->y + i);
		Paint(player->color);
		printf(player->shape[player->aniIndex][i]);
	}


	for (int i = 0; i < BulletCount; i++)
	{
		MovePos(bullets[i]->info.x, bullets[i]->info.y);
		Paint(bullets[i]->info.color);
		printf(bullets[i]->shape);
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			MovePos(enemies[i]->x, enemies[i]->y + j);
			Paint(enemies[i]->color);
			printf(enemies[i]->shape[j]);
		}

	}
}

void StageRelease()
{
	if (player != nullptr)
	{
		free(player);
		player = nullptr;
	}

	for (int i = 0; i < BulletCount; i++)
	{
		if (bullets[i] != nullptr)
		{
			free(bullets[i]);
			bullets[i] = nullptr;
		}
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		if (enemies[i] != nullptr)
		{
			free(enemies[i]);
			enemies[i] = nullptr;
		}
	}
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

