#pragma once
#include "Header.h"
class Obj
{
protected:
	bool act;
	int x;
	int y;
	COLOR color;
	const char* shape;
public:
	bool GetAct() { return act; }
	int GetX() { return x; }
	int GetY() { return y; }
public:
	void SetActive(bool _act, int _x, int _y)
	{
		act = _act;
		x = _x;
		y = _y;
	}
public:
	virtual void Initialize() abstract;
	virtual void Progress() abstract;
	virtual void Render() abstract;
	virtual void Release() abstract;
};

