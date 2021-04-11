#pragma once
#include "config.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,		//������Ʈ ��ü�� ���� ��ų �̹���
		FILE,			//�ܺο��� �ε��� �̹���
		EMPTY,			//��ü ���� �̹���
		END		
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		//���ҽ��� ������ ID
		HDC hMemDC;			//�׸��⸦ �ְ��ϴ� �ڵ�
		HDC hTempDC;		//�¿� �����ϱ� ���� �־��� �ڵ�
		HBITMAP hBitmap;	//�̹��� ����
		HBITMAP hOldBit;	//���� �̹��� ����
		int width;			//�̹��� ���� ũ��
		int height;			//�̹��� ���� ũ��
		BYTE loadType;		//�ε� Ÿ�� - enum�� �ִ� ��

		//�ִϸ��̼� ���� (�����ӵ�����)
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;


		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hTempDC = NULL; 
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		};

	}IMAGE_INFO, *LPIMAGE_INFO;
	
private:
	//�����ͷ� ��� ���� ���� - �Ʒ� �� ���� ���� ��
	//LPIMAGE_INFO imageInfo;
	IMAGE_INFO* imageInfo;	//�̹��� ���� ����ü ������
	bool isTransparent;
	COLORREF transColor;

	
public:
	//�� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);
	void Release();

	//���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent=FALSE, COLORREF transColor=FALSE);

	//���Ϸκ��� �ִϸ��̼� �̹��� �ε� �Լ�?
	HRESULT Init2(const char* fileName, int width, int height, 
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);


	//ȭ�鿡 ���
	void Render(HDC hdc, int destX = 0, int destY = 0, int srcX = 0, int srcY = 0);
	//�ڿ� �Ű����� �ȳ־ �ڵ����� 0, 0 ����
		
	void Render3(HDC hdc, int destX, int destY, int frameIndex, int frameCount);


	//get, set
	HDC GetMemDc() 
	{ 
		if(this->imageInfo) 
			return this->imageInfo->hMemDC; 
		return NULL;
	}

};

