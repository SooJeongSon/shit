#include "CharacterSelect.h"
#include "Image.h"
#include "SceneManager.h"
#include "Character.h"
#include "InGame.h"

HRESULT CharacterSelect::Init()
{
    img = new Image();
    img->Init("Image/gamebackground.bmp", WINSIZE_X, WINSIZE_Y);

    for (int i = 0; i < (int)Character::Characters::NONE; i++)
    {
        charImg.push_back(new Image());
    }
    charImg[0]->Init("Image/woman.bmp", 69, 76, true, RGB(255, 255, 255));
    charImg[1]->Init("Image/ironman.bmp", 58, 78, true, RGB(255, 255, 255));
    charImg[2]->Init("Image/man.bmp", 58, 78, true, RGB(255, 255, 255));
    
    


    changeScene = false;
    charSelected = false;
    isManOn = false;
    isIronmanOn = false;
    isWomanOn = false;
    
    selectboxPosX = 100;
    selectboxPosY = 100;
    selectNum = 0;
    

    return S_OK;
}

void CharacterSelect::Release()
{
    delete img;
    img = nullptr;

    //벡터는 삭제를 어떻게하지?
}

void CharacterSelect::Update()
{
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
    {

         changeScene = true;
         CheckSelect();
         SetPlayer();
         SceneManager::GetSingleton()->ChangeScene((int)SceneManager::SCENE_STATE::INGAME);
         SceneManager::GetSingleton()->SetPlayer(selectNum);
    
    }
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
    {
        if (!charSelected)
        {
            selectboxPosY -= 300;
            if (selectboxPosY <= 100)
                selectboxPosY = 100;

        }
    }
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
    {
        if (!charSelected)
        {
            selectboxPosY += 300;
            if (selectboxPosY >= 700)
                selectboxPosY = 700;

        }
    }


}

void CharacterSelect::Render(HDC hdc)
{
    img->Render(hdc);
    charImg[0]->Render(hdc, 100, 100);
    charImg[1]->Render(hdc, 100, 400);
    charImg[2]->Render(hdc, 100, 700);

    Rectangle(hdc, selectboxPosX, selectboxPosY, selectboxPosX + 600, selectboxPosY + 200);

}

void CharacterSelect::CheckSelect()
{
    if (selectboxPosY == 700)
        isManOn = true;
    else if (selectboxPosY == 400)
        isIronmanOn = true;
    else if (selectboxPosY == 100)
        isWomanOn = true;
}

void CharacterSelect::SetPlayer()
{
    if (isManOn)
    {
        //ingame->SetPlayer((int)Character::Characters::MAN);
       selectNum = ((int)Character::Characters::MAN);
        
    }
        
    else if (isIronmanOn)
    {
       // ingame->SetPlayer((int)Character::Characters::IRONMAN);
        selectNum = ((int)Character::Characters::IRONMAN);
    }
    
    else if (isWomanOn)
    {
       // ingame->SetPlayer((int)Character::Characters::WOMAN);
        selectNum = ((int)Character::Characters::WOMAN);
    }
        
}
