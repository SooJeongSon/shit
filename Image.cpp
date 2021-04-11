#include "Image.h"

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);    //�������� ���� HDC ������

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc); 
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;
    ReleaseDC(g_hWnd, hdc);     //�������� ���� HDC ��ȯ�ϱ�

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);    //�������� ���� HDC ������

    imageInfo = new IMAGE_INFO();
    imageInfo->resID = 0;
    imageInfo->hMemDC = CreateCompatibleDC(hdc);
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); 
    imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

    ReleaseDC(g_hWnd, hdc);     //�������� ���� HDC ��ȯ�ϱ�

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
    HDC hdc = GetDC(g_hWnd);    //�������� ���� HDC ������

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

    ReleaseDC(g_hWnd, hdc);     //�������� ���� HDC ��ȯ�ϱ�

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
        //Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,                    //���� ������ DC
            destX, destY,           //���� ���� ��ġ
            imageInfo->width,
            imageInfo->height,
            imageInfo->hMemDC,      //���� DC
            srcX, srcY,                  //���� ���� ���� ��ġ
            imageInfo->width,
            imageInfo->height,
            transColor              //������� ���� ����

            );
    }
    else
    {
        //bitmap�� �ִ� �̹��� ������ �ٸ� ��Ʈ�ʿ� ����
        BitBlt(
            hdc,                    //���� ������ DC
            destX, destY,                   //���� ���� ��ġ
            imageInfo->width,       //�������� ����� ����ũ��
            imageInfo->height,      //�������� ����� ����ũ��
            imageInfo->hMemDC,      //���� DC
            srcX, srcY,                   //�������� ���� ���� ��ġ
            SRCCOPY                 //���� �ɼ�
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

    //    //Ư�� ������ ���� �����ϴ� �Լ�
    //    GdiTransparentBlt(
    //        hdc,                    //���� ������ DC
    //        destX, destY,           //������ ���� ���� ��ġ
    //        imageInfo->frameWidth, 
    //        imageInfo->frameHeight, //������ ���� ũ��

    //        hdc,      //���� DC                    
    //        imageInfo->frameWidth * imageInfo->currFrameX, //�������� ���� x��ġ
    //        imageInfo->frameHeight * imageInfo->currFrameY, //�������� ���� y��ġ
    //        imageInfo->frameWidth, imageInfo->frameHeight, //�������� ���� ũ��
    //        transColor              //������� ���� ����
    //     );
    //                
    //}
    //���� ��ȣ
    if (isTransparent)
    {
        //Ư�� ������ ���� �����ϴ� �Լ�
        GdiTransparentBlt(
            hdc,                    //���� ������ DC
            destX, destY,           //������ ���� ���� ��ġ
            imageInfo->frameWidth,
            imageInfo->frameHeight, //������ ���� ũ��

            imageInfo->hMemDC,      //���� DC                    
            imageInfo->frameWidth * imageInfo->currFrameX, //�������� ���� x��ġ
            imageInfo->frameHeight * imageInfo->currFrameY, //�������� ���� y��ġ
            imageInfo->frameWidth, imageInfo->frameHeight, //�������� ���� ũ��
            transColor              //������� ���� ����
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