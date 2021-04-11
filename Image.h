#pragma once
#include "config.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,		//프로젝트 자체에 포함 시킬 이미지
		FILE,			//외부에서 로드할 이미지
		EMPTY,			//자체 생산 이미지
		END		
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		//리소스의 고유한 ID
		HDC hMemDC;			//그리기를 주관하는 핸들
		HDC hTempDC;		//좌우 반전하기 위해 넣어준 핸들
		HBITMAP hBitmap;	//이미지 정보
		HBITMAP hOldBit;	//기존 이미지 정보
		int width;			//이미지 가로 크기
		int height;			//이미지 세로 크기
		BYTE loadType;		//로드 타입 - enum에 있는 것

		//애니메이션 관련 (프레임데이터)
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
	//포인터로 멤버 변수 선언 - 아래 두 개는 같은 뜻
	//LPIMAGE_INFO imageInfo;
	IMAGE_INFO* imageInfo;	//이미지 정보 구조체 포인터
	bool isTransparent;
	COLORREF transColor;

	
public:
	//빈 비트맵 이미지를 만드는 함수
	HRESULT Init(int width, int height);
	void Release();

	//파일로부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent=FALSE, COLORREF transColor=FALSE);

	//파일로부터 애니메이션 이미지 로드 함수?
	HRESULT Init2(const char* fileName, int width, int height, 
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);


	//화면에 출력
	void Render(HDC hdc, int destX = 0, int destY = 0, int srcX = 0, int srcY = 0);
	//뒤에 매개변수 안넣어도 자동으로 0, 0 세팅
		
	void Render3(HDC hdc, int destX, int destY, int frameIndex, int frameCount);


	//get, set
	HDC GetMemDc() 
	{ 
		if(this->imageInfo) 
			return this->imageInfo->hMemDC; 
		return NULL;
	}

};

