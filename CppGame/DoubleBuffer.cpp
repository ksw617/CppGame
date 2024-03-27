#include "DoubleBuffer.h"

void DoubleBuffer::InitBuffer()
{		   
	screeIndex = 0;

	COORD size = { BufferWidth, BufferHeight };
	SMALL_RECT rect = { 0, 0, BufferWidth - 1, BufferHeight - 1 };

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[0], size);
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[1], size);
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	CONSOLE_CURSOR_INFO info;	
	info.dwSize = 1;			
	info.bVisible = FALSE;		

	SetConsoleCursorInfo(hBuffer[0], &info);
	SetConsoleCursorInfo(hBuffer[1], &info);

}

void DoubleBuffer::FlipBuffer()
{				
	SetConsoleActiveScreenBuffer(hBuffer[screeIndex]);
	screeIndex = !screeIndex;
}

void DoubleBuffer::ClearBuffer()
{	   

	COORD pos = { 0,0 };
	DWORD dw;

	FillConsoleOutputCharacter(hBuffer[screeIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}

void DoubleBuffer::WriteBuffer(int x, int y, const char* shape, int color)
{
	COORD pos = { x * 2, y };

	SetConsoleCursorPosition(hBuffer[screeIndex], pos);
	SetConsoleTextAttribute(hBuffer[screeIndex], color);

	DWORD dw;

	WriteFile(hBuffer[screeIndex], shape, strlen(shape), &dw, NULL);
}

void DoubleBuffer::ReleaseBuffer()
{
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}
