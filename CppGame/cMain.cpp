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

#define BufferWidth 80	  //���� ���� ũ��
#define BufferHeight 40	  //���� ���� ũ��

HANDLE hBuffer[2];	// â �ΰ��� �����ϴ� �ڵ�
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

//���� �ʱ�ȭ
void InitBuffer()
{
	//���� ��ũ�� index���� 0
	screeIndex = 0;

	//size.x = 80, size.y = 40 : ȭ��ũ��
	COORD size = { BufferWidth, BufferHeight };

	//â ũ�� ���� : 0, ���� : 0, ������ : 80 - 1, �Ʒ��� : 40 - 1 
	SMALL_RECT rect = { 0, 0, BufferWidth - 1, BufferHeight - 1 };

	//0�� ���� �����
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//0�� ȭ�� ���� ������ ����(���� ���� �ּ�, ũ��)
	SetConsoleScreenBufferSize(hBuffer[0], size);
	//0�� â ������ ����
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	//1�� ���� �����
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//1�� ȭ�� ���� ������ ����(���� ���� �ּ�, ũ��)
	SetConsoleScreenBufferSize(hBuffer[1], size);
	//1�� â ������ ����
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	//Ŀ�� ���� ��� : �����̴� Ŀ�� �Ⱥ��̰�
	CONSOLE_CURSOR_INFO info;	//�ܼ� Ŀ�� ���� ����ü
	info.dwSize = 1;			//Ŀ�� ũ��
	info.bVisible = FALSE;		//Ŀ�� �Ⱥ��̰�

	//0 && 1 ������ ���ۿ� Ŀ�� ���� ���
	SetConsoleCursorInfo(hBuffer[0], &info);
	SetConsoleCursorInfo(hBuffer[1], &info);
}

//���� ������
void FlipBuffer()
{
	//�ش� ���� Ȱ��ȭ
	SetConsoleActiveScreenBuffer(hBuffer[screeIndex]);

	//[0]->[1] / [1]->[0]
	screeIndex = !screeIndex;
}

//���� â ������
void ClearBuffer()
{
	//���� ��ġ
	//pos.x = 0, pos.Y = 0
	COORD pos = { 0,0 };
	//�Ű����� ä�����
	DWORD dw;

	//ȭ���� ' '�� ä��
	FillConsoleOutputCharacter(hBuffer[screeIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}

//���ۿ� ����
void WriteBuffer(int x, int y, const char* shape, int color)
{
	//��ġ����
	//pos.X = x * 2, pos.Y = y
	COORD pos = { x * 2, y };

	//Ŀ�� ��ġ �̵�
	SetConsoleCursorPosition(hBuffer[screeIndex], pos);

	//���� �ٲ��ְ�
	SetConsoleTextAttribute(hBuffer[screeIndex], color);

	//�Ű����� ä��� ����
	DWORD dw;

	//�ش� ���ۿ� ����
	WriteFile(hBuffer[screeIndex], shape, strlen(shape), &dw, NULL);
}

//���� ����
void ReleaseBuffer()
{
	//���� �ݱ�
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

#pragma endregion

