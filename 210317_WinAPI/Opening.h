#pragma once
#include "GameScene.h"

class Image;

class Opening : public GameScene
{
private:
	Image* img;
	bool changeScene;


public:

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void SetPlayer(int num) {}
	int GetSelectNum() { return 0; }
};

 