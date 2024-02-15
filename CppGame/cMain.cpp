#include <stdio.h>
#include <Windows.h>

enum Color
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


//Ŀ���̵� �����ִ� ��
void MovePos(int x, int y);
//���� ���� �ٲ���
void Paint(int color);
//Ŀ�� �����
void HideCursor();


int main()
{
	HideCursor();


	while (true)
	{
		system("cls");

		MovePos(10, 10);
		Paint(LIGHTGREEN);
		printf("Hello world");

		Sleep(1000);

	}
	return 0;
}


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
