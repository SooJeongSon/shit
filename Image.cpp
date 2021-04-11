#include "Image.h"

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);    //윈도우의 메인 HDC 얻어오기

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc); 
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;
    ReleaseDC(g_hWnd, hdc);     //윈도우의 메인 HDC 반환하기

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);    //윈도우의 메인 HDC 얻어오기

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); 
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    ReleaseDC(g_hWnd, hdc);     //윈도우의 메인 HDC 반환하기

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }
    this->isTransparent = isTransparent;
    this->transColor = transColor; 

    return S_OK;
 
}

HRESULT Image::Init2(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);    //윈도우의 메인 HDC 얻어오기

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    //imageInfo->hTempDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;
    imageInfo->currFrameX = 0;
    imageInfo->currFrameY = 0;

    ReleaseDC(g_hWnd, hdc);     //윈도우의 메인 HDC 반환하기

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    this->isTransparent = isTransparent;
    this->transColor = transColor;

    return S_OK;
}

void Image::Render(HDC hdc, int destX, int destY, int srcX, int srcY)
{
    if (isTransparent)
    {
        //특정 색상을 빼고 복사하는 함수
        GdiTransparentBlt(
            hdc,                    //복사 목적지 DC
            destX, destY,           //복사 시작 위치
            imageInfo->width,
            imageInfo->height,
            imageInfo->hMemDC,      //원본 DC
            srcX, srcY,                  //원본 복사 시작 위치
            imageInfo->width,
            imageInfo->height,
            transColor              //빼고싶은 색깔 정보

            );
    }
    else
    {
        //bitmap에 있는 이미지 정보를 다른 비트맵에 복사
        BitBlt(
            hdc,                    //복사 목적지 DC
            destX, destY,                   //복사 시작 위치
            imageInfo->width,       //원본에서 복사될 가로크기
            imageInfo->height,      //원본에서 복사될 세로크기
            imageInfo->hMemDC,      //원본 DC
            srcX, srcY,                   //원본에서 복사 시작 위치
            SRCCOPY                 //복사 옵션
        );
    }
       
}

void Image::Render3(HDC hdc, int destX, int destY, int frameIndex, int frameCount)
{
   imageInfo->currFrameX = frameIndex;
   

    //if (isTransparent)
    //{
    //  /*  StretchBlt(
    //        hdc, destX, destY,
    //        imageInfo->frameWidth, imageInfo->frameHeight,
    //        imageInfo->hMemDC, 
    //        imageInfo->frameWidth * imageInfo->currFrameX,
    //        imageInfo->frameHeight * imageInfo->currFrameY,
    //        -1 * (imageInfo->frameWidth), imageInfo->frameHeight,
    //        SRCCOPY);*/

    //    //특정 색상을 빼고 복사하는 함수
    //    GdiTransparentBlt(
    //        hdc,                    //복사 목적지 DC
    //        destX, destY,           //목적지 복사 시작 위치
    //        imageInfo->frameWidth, 
    //        imageInfo->frameHeight, //목적지 복사 크기

    //        hdc,      //원본 DC                    
    //        imageInfo->frameWidth * imageInfo->currFrameX, //원본에서 복사 x위치
    //        imageInfo->frameHeight * imageInfo->currFrameY, //원본에서 복사 y위치
    //        imageInfo->frameWidth, imageInfo->frameHeight, //원본에서 복사 크기
    //        transColor              //빼고싶은 색깔 정보
    //     );
    //                
    //}
    //원본 보호
    if (isTransparent)
    {
        //특정 색상을 빼고 복사하는 함수
        GdiTransparentBlt(
            hdc,                    //복사 목적지 DC
            destX, destY,           //목적지 복사 시작 위치
            imageInfo->frameWidth,
            imageInfo->frameHeight, //목적지 복사 크기

            imageInfo->hMemDC,      //원본 DC                    
            imageInfo->frameWidth * imageInfo->currFrameX, //원본에서 복사 x위치
            imageInfo->frameHeight * imageInfo->currFrameY, //원본에서 복사 y위치
            imageInfo->frameWidth, imageInfo->frameHeight, //원본에서 복사 크기
            transColor              //빼고싶은 색깔 정보
        );

    }
    else
    {
        BitBlt(
            hdc,
            destX, destY,
            (imageInfo->width / frameCount),
            imageInfo->height,
            imageInfo->hMemDC,
            (imageInfo->width / frameCount) * (frameIndex), 0,
            SRCCOPY
        );
    }
   
}

void Image::Release()
{
    if (imageInfo)
    {
        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDC);
        SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hTempDC);

        delete imageInfo;
        imageInfo = nullptr;
    }

}