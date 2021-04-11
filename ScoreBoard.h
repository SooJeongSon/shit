#pragma once
#include "GameScene.h"

class ScoreBoard : public GameScene
{
public:

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void SetPlayer(int num) {}
	int GetSelectNum() { return 0; }
};

