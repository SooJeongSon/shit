#include "MainGame.h"
#include "Image.h"
#include "SceneManager.h"

HRESULT MainGame::Init() 
{
	// 메인게임의 초기화 함수
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	
	KeyManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	//백퍼버 이미지
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->Release();


	backBuffer->Release();
	delete backBuffer;
	backBuffer = nullptr;


	KillTimer(g_hWnd, 0);
		
}

void MainGame::Update()
{

	SceneManager::GetSingleton()->Update();
	//CheckCollision(); 
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackDC = backBuffer->GetMemDc();

	SceneManager::GetSingleton()->Render(hBackDC);

	//// 인사
	//TextOut(backBuffer->GetMemDc(), 20, 20, "MainGame 렌더 중", strlen("MainGame 렌더 중"));
	//// 마우스 좌표
	//wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	//TextOut(hBackDC, 200, 20, szText, strlen(szText));

	backBuffer->Render(hdc, 0, 0);
}

void MainGame::CheckCollision()
{
	

}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;

	case WM_TIMER:

		if (isInited)
		{
			this->Update();
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		if (isInited)
		{
			this->Render(hdc);
		}

		EndPaint(g_hWnd, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(g_hWnd, 0);
		break;

	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}


