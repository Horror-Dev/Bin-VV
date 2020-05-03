#pragma once
#include<Windows.h>
#include<iostream>
#include<exception>
#include<string>
#include<thread>
#include<CommCtrl.h>
#include<UIAnimation.h>
#include<d2d1.h>
#include<dwrite.h>

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "Comctl32.lib")

#pragma warning(disable : 4996)

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include<bitset>

class BinApp{
	//--------DirectX------------

	ID2D1SolidColorBrush* pBrush;
	ID2D1SolidColorBrush* pSBrush;
	
	D2D1_ELLIPSE  ellipse;
	ID2D1RectangleGeometry* pRGM;

	ID2D1HwndRenderTarget* pRT;
	ID2D1Factory* pFactory;
	IDWriteFactory* m_pDWriteFactory{};
	IDWriteTextFormat* TextFormt{};
	IDWriteTextFormat* TextButtonFormt{};
	ID2D1DCRenderTarget* m_pDCRT;

	//-------Functions------------
	
	float dipX{}, dipY{};


	float pixelToDipX(float x) {
		return (x * 96.f) / dipX;
	}

	float pixelToDipY(float y) {
		return (y * 96.f) / dipY;
	}

	void CreateResources();

	void initFactory();

	void DrawBackGround();

	void ButtonDrawing(const int& nId, PDRAWITEMSTRUCT pDis);

	void FreeResources();

	void DrawTitle();

	//-----------------------------
	
	void DrawCloseButton(PDRAWITEMSTRUCT pDis);

	void DrawMinimizeButton(PDRAWITEMSTRUCT pDis);

	void DrawConvertButton(PDRAWITEMSTRUCT pDis);

	//----------------------------

	template<typename T>
	static void safeRelease(T** obj) {
		if ((*obj) != nullptr) {
			(*obj)->Release();
			(*obj) = nullptr;
		}
	}

	//---------------------------
	enum class CTL_ID {
		ID_BUTTON_CLOSE,
		ID_BUTTON_TRANSF,
		ID_BUTTON_MINIMIZE,
		ID_EDIT
	};
	//---------------------------


	HWND MainHwnd{}, CloseButtonHwnd{}, TranslateButtonHwnd{}, MiniMizeButtonHwnd{}, EditHWND{};

	HDC m_hWindowDC{};
	RECT m_rWindowRect{};

	const HRGN m_hSrcRgn{ CreateRectRgn(0,0,350,180) };
	const HRGN m_hSrcRgn1{ CreateRectRgn(2,2,348,375) };
	HRGN m_hAnimRegion{};

	const int Width{ 350 }, Hieght{ 280 };

	const std::wstring AppName{ L"Bin-VV" };

	static LRESULT CALLBACK ApplicationProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK WindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void initObjMainWindow();

	void CreateNativeControls();

public:

	BinApp();

	int run();

	~BinApp();

private:

	void onCloseButton();

	void onTransfButton();

	void onMinimizeButton();

	void Paint(HWND hwnd);

	void onCreate();
	
	void onClose();

	void Command(const int& nId);

};

