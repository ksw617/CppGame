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

enum SCENE_ID
{
	 LOGO,
	 MENU,
	 STAGE,
};


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

void StageInitialize();
void StageProgress();
void StageRender();
void StageRelease();

void PlayGame();

#pragma endregion

int main()
{
	id = LOGO;
	LogoInitialize();
	InitBuffer();

	while (true)
	{
		PlayGame();

		FlipBuffer();
		ClearBuffer();

		Sleep(30);
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

#pragma region Stage
void StageInitialize()
{
}
void StageProgress()
{
}
void StageRender()
{
	WriteBuffer(10, 10, "STAGE", BLUE);
}
void StageRelease()
{
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

