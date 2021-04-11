#include "InGame.h"
#include "Image.h"
#include "Character.h"
#include "CharacterSelect.h"
#include "Woman.h"
#include "Ironman.h"
#include "Man.h"

HRESULT InGame::Init()
{
	img = new Image();
	img->Init("Image/gamebackground.bmp", WINSIZE_X, WINSIZE_Y);

	selectedNum = 0;
	player = nullptr;

	return S_OK;
}

void InGame::Release()
{
}

void InGame::Update()
{
	if(player)
		player->Update();
}

void InGame::Render(HDC hdc)
{
	img->Render(hdc);
	if(player)
		player->Render(hdc);
}

void InGame::SetPlayer(int num)
{
	switch (num)
	{
	case (int)Character::Characters::WOMAN:
		player = new Woman();
		player->Init();
		break;

	case (int)Character::Characters::IRONMAN:
		player = new Ironman();
		player->Init();
		break;

	case (int)Character::Characters::MAN:
		player = new Man();
		player->Init();
		break;

	}

}
