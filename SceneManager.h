#pragma once
#include "Singleton2.h" 

class Image;
class GameScene; 
class SceneManager : public Singleton2<SceneManager> 
{
public:
	enum class SCENE_STATE
	{
		OPENING,
		SELECT,
		INGAME,
		SCOREBOARD,
		NONE
	};

private:

	GameScene* scenes[(int)SCENE_STATE::NONE];
	SCENE_STATE currentScene;
	//SCENE_STATE nextScene;




public:
	SceneManager() {};
	~SceneManager() {};

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void ChangeScene(int num);
	void SetPlayer(int num);



};

