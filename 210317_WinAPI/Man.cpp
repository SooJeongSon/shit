#include "Man.h"
#include "Image.h"

HRESULT Man::Init()
{
	img = new Image();
	img->Init("Image/man.bmp", 58, 78, true, RGB(255, 255, 255));
	return S_OK;
}

void Man::Release()
{
}

void Man::Update()
{
}

void Man::Render(HDC hdc)
{
	img->Render(hdc);
}
