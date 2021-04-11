#include "config.h"
#include "KeyManager.h"

HRESULT KeyManager::Init()
{
    KeyUp.set();        //전부 1으로 세팅
    KeyDown.reset();    //전부 0으로 세팅
    
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
        현재 키가 어떤 상태인지 알려주는 윈도우 제공 함수
        그런데 속도가 빨라서??? 제대로 처리가 안된다.

        함수 호출 시점에 가상키(VK= virtual key)가 어떤 상태인지 확인
        1. 0x0000 -> 이전 프레임에 누른 적이 없고 호출시점에도 눌려있지 않음
        2. 0x0001 -> 이전 프레임에 누른 적이 있고 호출시점에는 눌려있지 않음
        3. 0x8000 -> 이전 프레임에 누른 적이 없고 호출시점에는 눌려있는 상태
        4. 0x8001 -> 이전 프레임에 누른 적이 있고 호출시점에도 눌려있는 상태
        
        8은 2진수로 1000이기때문에, 맨 왼쪽이 1이면 현재시점에 눌림,
        맨 오른쪽이 1이면 이전 시점에 눌림 상태를 표현하는 비트다.
        
     */

    
    //& 비트 연산. 저 반환값들을 전부 2진수로 변환하고 자리수별로 연산을 한다.
    //아래 조건을 만족하려면 앞자리가 8인 경우에만 가능하다.
    if (GetAsyncKeyState(key) & 0x8000) //현재 눌려있다는 뜻
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
   //실습. 직접 만들어보자.
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
