#include <stdio.h>
#include <Windows.h>
#include <time.h>



#pragma region DoubleBuffer

#define BufferWidth 80	  //가로 버퍼 크기
#define BufferHeight 40	  //세로 버퍼 크기

HANDLE hBuffer[2];	// 창 두개를 제어하는 핸들
int screeIndex;		//hBuffer[screeIndex], screenIndex == 0 or 1
void InitBuffer();
void FlipBuffer();
void ClearBuffer();
void WriteBuffer(int x, int y, const char* shape, int color);
void ReleaseBuffer();
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

enum DIR
{
	IDLE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

#pragma endregion
#pragma region Map

#define MAP_WIDTH 40
#define MAP_HEIGHT 40
int map[MAP_HEIGHT][MAP_WIDTH] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

#pragma endregion

#pragma region Struct
struct Obj
{
	int step;
	int maxMove;
	DIR dir;
	int x;
	int y;
	COLOR color;
	const char* shape[3];

};

#pragma endregion



#pragma region PlayGame
SCENE_ID id;

void LogoInitialize();
void LogoProgress();
void LogoRender();
void LogoRelease();

void MenuInitialize();
void MenuProgress();
void MenuRender();
void MenuRelease();

Obj* player = nullptr;
Obj* enemy = nullptr;

void StageInitialize();
void StageProgress();
void StageRender();
void StageRelease();

void PlayGame();

#pragma endregion

int main()
{
	srand((unsigned)time(NULL));
	id = STAGE;
	StageInitialize();
	InitBuffer();

	while (true)
	{
		PlayGame();

		FlipBuffer();
		ClearBuffer();

		Sleep(50);
	}

	ReleaseBuffer();
}


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
	if (GetAsyncKeyState(VK_SPACE))
	{
		LogoRelease();
		id = MENU;
		MenuInitialize();
	}
}
void LogoRender()
{
	WriteBuffer(10,10,"LOGO", YELLOW);
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
	if (GetAsyncKeyState(VK_RETURN))
	{
		MenuRelease();
		id = STAGE;
		StageInitialize();
	}
}
void MenuRender()
{
	WriteBuffer(10, 10, "MENU", RED);
}
void MenuRelease()
{
}
#pragma endregion

bool CheckMap(Obj* obj)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (map[obj->y + y][obj->x + x] == 1)
			{
				return true;
			}
		}
	}

	return false;
}
#pragma region Stage

int enemyCount = 0;
void StageInitialize()
{
	player = (Obj*)malloc(sizeof(Obj));
	player->x = 10;
	player->y = 11;
	player->color = WHITE;
	player->shape[0] = "■■■";
	player->shape[1] = "■■■";
	player->shape[2] = "■■■";

	enemy = (Obj*)malloc(sizeof(Obj));


	do
	{
		enemy->x = rand() % 40;
		enemy->y = rand() % 40;
		enemyCount++;

	} while (CheckMap(enemy));

	enemy->dir = (DIR)(rand() % 5);
	enemy->step = 0;
	enemy->maxMove = rand() % 5 + 5;

	enemy->color = RED;
	enemy->shape[0] = "■■■";
	enemy->shape[1] = "■■■";
	enemy->shape[2] = "■■■";
}

bool IsCollisionMap(int x, int y, DIR dir)
{
	switch (dir)
	{
	case LEFT:
		for (int i = 0; i < 3; i++)
		{
			if (map[y + i][x] == 1)
			{
				return true;
			}
		}
		break;
	case RIGHT:
		for (int i = 0; i < 3; i++)
		{
			if (map[y + i][x + 2] == 1)
			{
				return true;
			}
		}
		break;
	case UP:
		for (int i = 0; i < 3; i++)
		{
			if (map[y][x + i] == 1)
			{
				return true;
			}
		}
		break;
	case DOWN:
		for (int i = 0; i < 3; i++)
		{
			if (map[y + 2][x + i] == 1)
			{
				return true;
			}
		}
		break;
	default:
		break;
	}

	return false;
}

void StageProgress()
{
	enemy->step++;
	if (enemy->step > enemy->maxMove)
	{
		enemy->step = 0;
		enemy->maxMove = rand() % 5 + 5;
		enemy->dir = (DIR)(rand() % 5);
	}
	
	switch (enemy->dir)
	{
	case LEFT:
		enemy->x--;
		if (IsCollisionMap(enemy->x, enemy->y, LEFT))
		{
			enemy->x++;
			enemy->dir = (DIR)(rand() % 5);
			enemy->step = 0;
		}
		break;
	case RIGHT:
		enemy->x++;
		if (IsCollisionMap(enemy->x, enemy->y, RIGHT))
		{
			enemy->x--;
			enemy->dir = (DIR)(rand() % 5);
			enemy->step = 0;
		}
		break;
	case UP:
		enemy->y--;
		if (IsCollisionMap(enemy->x, enemy->y, UP))
		{
			enemy->y++;
			enemy->dir = (DIR)(rand() % 5);
			enemy->step = 0;
		}
		break;
	case DOWN:
		enemy->y++;
		if (IsCollisionMap(enemy->x, enemy->y, DOWN))
		{
			enemy->y--;
			enemy->dir = (DIR)(rand() % 5);
			enemy->step = 0;
		}
		break;
	default:
		break;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (map[player->y + 0][player->x - 1] == 0 && map[player->y + 1][player->x - 1] == 0&& map[player->y + 2][player->x - 1] == 0)
		{
			player->x--;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		int enemyCount = 0;
		for (int i = 0; i < 3; i++)
		{
			if (map[player->y + i][player->x + 3] == 0)
			{
				enemyCount++;
			}
		}

		if (enemyCount == 3)
		{
			player->x++;
		}
		
	}
	if (GetAsyncKeyState(VK_UP))
	{
		player->y--;
		for (int i = 0; i < 3; i++)
		{
			if (map[player->y][player->x + i] == 1)
			{
				player->y++;
				break;
			}
		}

	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		player->y++;
		if (IsCollisionMap(player->x, player->y, DOWN))
		{
			player->y--;
		}
	}

	if (player->x <= enemy->x + 2 && enemy->x <= player->x + 2 &&
		player->y <= enemy->y + 2 && enemy->y <= player->y + 2)
	{
		exit(true);
	}
}
void StageRender()
{
	

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			switch (map[y][x])
			{
			case 1:
				WriteBuffer(x,y,"■", YELLOW);
				break;
			default:
				break;
			}

		}
	}

	for (int i = 0; i < 3; i++)
	{
		WriteBuffer(player->x, player->y + i, player->shape[i], player->color);
	}

	for (int i = 0; i < 3; i++)
	{
		WriteBuffer(enemy->x, enemy->y + i, enemy->shape[i], enemy->color);
	}

	char sNum[5];

	_itoa_s(enemyCount, sNum, 10);

	WriteBuffer(38, 0, sNum, RED);

}
void StageRelease()
{
	if (player != nullptr)
	{
		free(player);
		player = nullptr;
	}

	if (enemy != nullptr)
	{
		free(enemy);
		enemy = nullptr;
	}
}
#pragma endregion


#pragma region DoubleBuffer

//버퍼 초기화
void InitBuffer()
{
	//현재 스크린 index값은 0
	screeIndex = 0;

	//size.x = 80, size.y = 40 : 화면크기
	COORD size = { BufferWidth, BufferHeight };

	//창 크기 왼쪽 : 0, 위쪽 : 0, 오른쪽 : 80 - 1, 아래쪽 : 40 - 1 
	SMALL_RECT rect = { 0, 0, BufferWidth - 1, BufferHeight - 1 };

	//0번 버퍼 만들기
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//0번 화면 버퍼 사이즈 설정(만든 버퍼 주소, 크기)
	SetConsoleScreenBufferSize(hBuffer[0], size);
	//0번 창 사이즈 설정
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	//1번 버퍼 만들기
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//1번 화면 버퍼 사이즈 설정(만든 버퍼 주소, 크기)
	SetConsoleScreenBufferSize(hBuffer[1], size);
	//1번 창 사이즈 설정
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	//커서 정보 등록 : 깜박이는 커서 안보이게
	CONSOLE_CURSOR_INFO info;	//콘솔 커서 정보 구조체
	info.dwSize = 1;			//커서 크기
	info.bVisible = FALSE;		//커서 안보이게

	//0 && 1 각각의 버퍼에 커서 정보 등록
	SetConsoleCursorInfo(hBuffer[0], &info);
	SetConsoleCursorInfo(hBuffer[1], &info);
}

//버퍼 뒤집기
void FlipBuffer()
{
	//해당 버퍼 활성화
	SetConsoleActiveScreenBuffer(hBuffer[screeIndex]);

	//[0]->[1] / [1]->[0]
	screeIndex = !screeIndex;
}

//버퍼 창 깨끗이
void ClearBuffer()
{
	//시작 위치
	//pos.x = 0, pos.Y = 0
	COORD pos = { 0,0 };
	//매개변수 채울려고
	DWORD dw;

	//화면을 ' '로 채움
	FillConsoleOutputCharacter(hBuffer[screeIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}

//버퍼에 쓰기
void WriteBuffer(int x, int y, const char* shape, int color)
{
	//위치설정
	//pos.X = x * 2, pos.Y = y
	COORD pos = { x * 2, y };

	//커서 위치 이동
	SetConsoleCursorPosition(hBuffer[screeIndex], pos);

	//색깔 바꿔주고
	SetConsoleTextAttribute(hBuffer[screeIndex], color);

	//매개변수 채우기 위해
	DWORD dw;

	//해당 버퍼에 쓰기
	WriteFile(hBuffer[screeIndex], shape, strlen(shape), &dw, NULL);
}

//버퍼 해제
void ReleaseBuffer()
{
	//버퍼 닫기
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

#pragma endregion

