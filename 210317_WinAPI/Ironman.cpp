#include "Ironman.h"
#include "Image.h"

HRESULT Ironman::Init()
{
    img = new Image();
    img->Init("Image/ironman.bmp", 58, 78, true, RGB(255, 255, 255));

    return S_OK;
}

void Ironman::Release()
{
}

void Ironman::Update()
{
}

void Ironman::Render(HDC hdc)
{
    img->Render(hdc);
}
