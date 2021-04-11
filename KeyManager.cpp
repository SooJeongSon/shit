#include "config.h"
#include "KeyManager.h"

HRESULT KeyManager::Init()
{
    KeyUp.set();        //���� 1���� ����
    KeyDown.reset();    //���� 0���� ����
    
   /* for (int i = 0; i < MAX_KEY_COUNT; i++)
    {
        KeyUp[i] = true;
        KeyDown[i] = false;
    }*/
    return S_OK;
}

void KeyManager::Release()
{
    ReleaseSingleton();
}

bool KeyManager::IsOnceKeyDown(int key)
{
    /*
        GetAsyncKeyState(VK_...)    
        ���� Ű�� � �������� �˷��ִ� ������ ���� �Լ�
        �׷��� �ӵ��� ����??? ����� ó���� �ȵȴ�.

        �Լ� ȣ�� ������ ����Ű(VK= virtual key)�� � �������� Ȯ��
        1. 0x0000 -> ���� �����ӿ� ���� ���� ���� ȣ��������� �������� ����
        2. 0x0001 -> ���� �����ӿ� ���� ���� �ְ� ȣ��������� �������� ����
        3. 0x8000 -> ���� �����ӿ� ���� ���� ���� ȣ��������� �����ִ� ����
        4. 0x8001 -> ���� �����ӿ� ���� ���� �ְ� ȣ��������� �����ִ� ����
        
        8�� 2������ 1000�̱⶧����, �� ������ 1�̸� ��������� ����,
        �� �������� 1�̸� ���� ������ ���� ���¸� ǥ���ϴ� ��Ʈ��.
        
     */

    
    //& ��Ʈ ����. �� ��ȯ������ ���� 2������ ��ȯ�ϰ� �ڸ������� ������ �Ѵ�.
    //�Ʒ� ������ �����Ϸ��� ���ڸ��� 8�� ��쿡�� �����ϴ�.
    if (GetAsyncKeyState(key) & 0x8000) //���� �����ִٴ� ��
    {
        if (KeyDown[key] == false)
        {
            KeyDown[key] = true;
            return true;
        }
    }
    else
    {
        KeyDown[key] = false;
    }
    return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
   //�ǽ�. ���� ������.
    if (GetAsyncKeyState(key) & 0x8000)
    {
        KeyUp[key] = false;
    }
    else
    {
        if (KeyUp[key] == false)
        {
            KeyUp[key] = true;
            return true;
        }        
    }
    return false;

    
}

bool KeyManager::IsStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {

        return true;
    }

    return false;
}
