#include <stdio.h>
#include <Windows.h>

#pragma region Define

#define PoopCount 20

#pragma endregion


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

enum SCENE_ID
{
	 LOGO, 
	 MENU,
	 STAGE,
};
#pragma endregion

#pragma region Struct
typedef struct Obj
{
	bool act;
	int x;
	int y;
	COLOR color;
	const char* shape;
}*PObj;	  //Obj*
#pragma endregion


#pragma region Game
SCENE_ID id;
void PlayGame();

void LogoInitialize();
void LogoProgress();
void LogoRender();
void LogoRelease();

void MenuInitialize();
void MenuProgress();
void MenuRender();
void MenuRelease();


PObj player;
PObj poops[PoopCount];

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
	id = LOGO;
	LogoInitialize();


	while (true)
	{
		system("cls");
		PlayGame();
		Sleep(50);

	}
	return 0;
}

#pragma region Game
void PlayGame()
{
	switch (id)
	{
	case LOGO:
		LogoProgress();
		LogoRender();
		break;
	case MENU:
		MenuProgress();
		MenuRender();
		break;
	case STAGE:
		StageProgress();
		StageRender();
		break;
	default:
		break;
	}
}

#pragma region Logo
void LogoInitialize()
{
}

void LogoProgress()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		LogoRelease();
		id = MENU;
		MenuInitialize();
	}
}

void LogoRender()
{
	printf("LOGO");
}
void LogoRelease()
{
}
#pragma endregion

#pragma region Menu
void MenuInitialize()
{
}

void MenuProgress()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		MenuRelease();
		id = STAGE;
		StageInitialize();
	}
}

void MenuRender()
{
	printf("MENU");
}

void MenuRelease()
{
}
#pragma endregion

#pragma region Stage
void StageInitialize()
{
	//PObj == Obj*
	player = (PObj)malloc(sizeof(Obj));
	player->x = 10;
	player->y = 25;
	player->color = YELLOW;
	player->shape = "옷";

	for (int i = 0; i < PoopCount; i++)
	{
		poops[i] = (PObj)malloc(sizeof(Obj));
		poops[i]->act = false;
		poops[i]->x = 0;  //임의의 난수에 % 10 == 0~9
		poops[i]->y = 0;
		poops[i]->color = BROWN;
		poops[i]->shape = "＠";
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

	for (int i = 0; i < PoopCount; i++)
	{
		if (poops[i]->act == false)
		{
			poops[i]->x = rand() % 40;
			poops[i]->act = true;
			break;

		}
	}


	for (int i = 0; i < PoopCount; i++)
	{
		if (poops[i]->act == true)
		{
			poops[i]->y++;
			if (poops[i]->y > player->y)
			{
				poops[i]->y = 0;
				poops[i]->act = false;
			}
			
			if (poops[i]->x == player->x && poops[i]->y == player->y)
			{
				player->color = RED;
			}
		}

		
	}
}

void StageRender()
{
	MovePos(player->x, player->y);
	Paint(player->color);
	printf(player->shape);

	for (int i = 0; i < PoopCount; i++)
	{
		MovePos(poops[i]->x, poops[i]->y);
		Paint(poops[i]->color);
		printf(poops[i]->shape);
	}
}

void StageRelease()
{
}
#pragma endregion

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

