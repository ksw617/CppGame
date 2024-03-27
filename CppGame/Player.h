#pragma once
#include "Obj.h"
class Player : public Obj
{
public:
	virtual void Initialize() override;
	virtual void Progress()	override;
	virtual void Render() override;
	virtual void Release() override;
};

