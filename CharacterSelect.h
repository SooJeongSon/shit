#pragma once
#include "GameScene.h"

class Image;
//class InGame;


class CharacterSelect : public GameScene
{
private:
	Image* img;
	vector<Image*> charImg; 

	bool changeScene;
	bool charSelected;
	int charIndex;

	bool isManOn;
	bool isIronmanOn;
	bool isWomanOn;
	int selectboxPosX;
	int selectboxPosY;

	int selectNum;

	//InGame* ingame;


public:

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void CheckSelect();
	void SetPlayer();
	void SetPlayer(int num) {};
	int GetSelectNum() { return selectNum; }
};

