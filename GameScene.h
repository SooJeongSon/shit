#pragma once
#include "config.h"

class GameScene
{
public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void SetPlayer(int num) = 0;
	virtual int GetSelectNum() = 0;
};

