#pragma once
#include "GameNode.h"
#include "KeyManager.h"

//���漱��
class Image;
class SceneManager;

class MainGame : public GameNode
{
private:
	bool isInited;

	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	char szText[128] = "";
	Image* backBuffer;

	KeyManager keymgr;
	SceneManager* scMgr;

public:
	HRESULT Init();		// �������̵� : ������
	void Release();
	void Update();
	void Render(HDC hdc);
	void CheckCollision(); 
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	int GetSelectNum() {}
	MainGame();
	~MainGame();
};

