#pragma once

#include "Singleton.h"
#define MAX_KEY_COUNT 256
using namespace std;

class KeyManager : public Singleton<KeyManager>
{
private:
	//static KeyManager* instance; ��ӹ޾Ƽ� �̷��� ������ �ִ� ��ó�� �ȴ�?

	bitset<MAX_KEY_COUNT> KeyUp;	//���� Ű�� ���� �ö�� �ִ���
	bitset<MAX_KEY_COUNT> KeyDown;	//���� Ű�� ���� �ִ���


public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyDown(int key);	//�ش� Ű�� ó�� ���ȴ��� �Ǵ�
	bool IsOnceKeyUp(int key);		//�ش� Ű�� ó�� ���ȴٰ� ���������� �Ǵ�
	bool IsStayKeyDown(int key);	//Ű�� ��� ���� �ִ��� �Ǵ�

	void SetKeyDown(int key, bool state) { this->KeyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { this->KeyUp.set(key, state); }



};

