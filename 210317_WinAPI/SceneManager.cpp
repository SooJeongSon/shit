#include "SceneManager.h"
#include "Image.h"
#include "Opening.h"
#include "ScoreBoard.h"
#include "InGame.h"
#include "CharacterSelect.h"
#include "GameScene.h"
#include "Character.h"


HRESULT SceneManager::Init()
{
	for (int i = 0; i < (int)SCENE_STATE::NONE; i++)
	{
		switch (i)
		{
		case (int)SCENE_STATE::OPENING:
			scenes[i] = new Opening();
			scenes[i]->Init();
			break;
		case (int)SCENE_STATE::SELECT:
			scenes[i] = new CharacterSelect();
			scenes[i]->Init();
			break;
		case (int)SCENE_STATE::INGAME:
			scenes[i] = new InGame();
			scenes[i]->Init();
			break;
		case (int)SCENE_STATE::SCOREBOARD:
			scenes[i] = new ScoreBoard();
			scenes[i]->Init();
			break;
		}
	}

	currentScene = SCENE_STATE::OPENING;

	return S_OK;
}

void SceneManager::Release()
{
	for (int i = 0; i < (int)SCENE_STATE::NONE; i++)
	{
		delete scenes[i];
	}

}

void SceneManager::Update()
{
	scenes[(int)currentScene]->Update();
	//scenes[(int)SCENE_STATE::INGAME]->SetPlayer(scenes[(int)SCENE_STATE::SELECT]->GetSelectNum());
	scenes[(int)SCENE_STATE::INGAME]->SetPlayer(scenes[(int)SCENE_STATE::SELECT]->GetSelectNum());
}

void SceneManager::Render(HDC hdc)
{
	scenes[(int)currentScene]->Render(hdc);
}

void SceneManager::ChangeScene(int num)
{
	switch (num)
	{
	case (int)SCENE_STATE::OPENING:
		currentScene = SCENE_STATE::OPENING;
		break;
	case (int)SCENE_STATE::SELECT:
		currentScene = SCENE_STATE::SELECT;
		break;
	case (int)SCENE_STATE::INGAME:
		currentScene = SCENE_STATE::INGAME;
		break;
	case (int)SCENE_STATE::SCOREBOARD:
		currentScene = SCENE_STATE::SCOREBOARD;
		break;


	}
}

void SceneManager::SetPlayer(int num)
{
	switch (num)
	{
	case (int)Character::Characters::WOMAN:
		scenes[(int)SCENE_STATE::INGAME]->SetPlayer(0);
		break;
	
	case (int)Character::Characters::IRONMAN:
		scenes[(int)SCENE_STATE::INGAME]->SetPlayer(1);
		break;
	
	case (int)Character::Characters::MAN:
		scenes[(int)SCENE_STATE::INGAME]->SetPlayer(2);
		break;
	
	}
	
}

