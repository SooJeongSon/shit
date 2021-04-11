#pragma once
#include "GameNode.h"

class Image;
class Character : public GameNode
{
private:
	Image* img;
	FPOINT pos;
	int elapsedTime;
	int frame;
	int frameCount;
	int stateCount = 0;
	int state;

public:


	enum class Character_STATE { MOVE, SKILL, DIE };
	enum class Characters { WOMAN, IRONMAN, MAN, NONE };

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	

};

