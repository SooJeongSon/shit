#pragma once
#include "GameScene.h"

class Image;
class Character;
class CharacterSelect;

class InGame : public GameScene
{
private:
	Image* img;
	Character* player;
	int selectedNum;


public:

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void SetPlayer(int num);

	int GetSelectNum() { return 0; }
};

