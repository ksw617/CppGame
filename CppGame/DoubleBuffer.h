#pragma once
#include "Header.h"
#include "Singleton.h"
class DoubleBuffer : public  Singleton<DoubleBuffer>
{
public:
	DoubleBuffer() = default;
	~DoubleBuffer() = default;
	DoubleBuffer(const DoubleBuffer&) = delete;
private:
	HANDLE hBuffer[2];	// â �ΰ��� �����ϴ� �ڵ�
	int screeIndex;		//hBuffer[screeIndex], screenIndex == 0 or 1
public:
	void InitBuffer();
	void FlipBuffer();
	void ClearBuffer();
	void WriteBuffer(int x, int y, const char* shape, int color);
	void ReleaseBuffer();

};

