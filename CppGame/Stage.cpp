#include "Stage.h"
#include "DoubleBuffer.h"

void Stage::Initialize()
{
}

void Stage::Progress()
{
}

void Stage::Render()
{
	DoubleBuffer::Get().WriteBuffer(10, 10, "STAGE", 14);
}

void Stage::Release()
{
}
