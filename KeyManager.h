#pragma once

#include "Singleton.h"
#define MAX_KEY_COUNT 256
using namespace std;

class KeyManager : public Singleton<KeyManager>
{
private:
	//static KeyManager* instance; 상속받아서 이렇게 가지고 있는 것처럼 된다?

	bitset<MAX_KEY_COUNT> KeyUp;	//현재 키가 위로 올라와 있는지
	bitset<MAX_KEY_COUNT> KeyDown;	//현재 키가 눌려 있는지


public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyDown(int key);	//해당 키가 처음 눌렸는지 판단
	bool IsOnceKeyUp(int key);		//해당 키가 처음 눌렸다가 떼어졌는지 판단
	bool IsStayKeyDown(int key);	//키가 계속 눌려 있는지 판단

	void SetKeyDown(int key, bool state) { this->KeyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { this->KeyUp.set(key, state); }



};

