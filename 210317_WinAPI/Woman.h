#pragma once
#include "Character.h"

class Image;

class Woman : public Character
{
private:
	Image* img;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

