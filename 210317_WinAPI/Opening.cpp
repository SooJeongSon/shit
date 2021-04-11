#include "Opening.h"
#include "Image.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "GameScene.h"

HRESULT Opening::Init()
{
	img = new Image();
	img->Init("Image/title.bmp", WINSIZE_X, WINSIZE_Y);

	changeScene = 0;

	return S_OK;
}

void Opening::Release()
{
	delete img;
	img = nullptr;
}

void Opening::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		changeScene = true;
		SceneManager::GetSingleton()->ChangeScene(1);
	}
}

void Opening::Render(HDC hdc)
{
	img->Render(hdc);
}
