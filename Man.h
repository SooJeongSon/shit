#pragma once
#include "Character.h"
class Man : public Character
{
private:
	Image* img;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

