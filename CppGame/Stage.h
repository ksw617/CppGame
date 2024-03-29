#pragma once
#include "Scene.h"

#define BULLET_COUNT 10

class Stage : public Scene
{
private:
	class Obj* player = nullptr;
	class Obj* bullets[BULLET_COUNT] = {};
public:
	virtual void Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;
};

