#include "Woman.h"
#include "Image.h"

HRESULT Woman::Init()
{
	img = new Image();
	img->Init("Image/woman.bmp", 69, 76, true, RGB(255, 255, 255));

	return S_OK;
}

void Woman::Release()
{
}

void Woman::Update()
{
}

void Woman::Render(HDC hdc)
{
	img->Render(hdc);
}
