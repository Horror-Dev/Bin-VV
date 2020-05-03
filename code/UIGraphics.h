#pragma once
#include"BinApp.h"


#include<Windows.h>
#include<iostream>
#include<exception>
#include<string>


#include <string>
#include <thread>
#include <CommCtrl.h>
#include <UIAnimation.h>
#include<d2d1.h>
#include<dwrite.h>

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "Comctl32.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

template<typename T>
static void safeRelease(T** obj) {
	if ((*obj) != nullptr) {
		(*obj)->Release();
		(*obj) = nullptr;
	}
}


class BinApp;
class UIGraphics{
public:	
	void InitD2D1();

	void initResources();

	void StartDrawing();

	void stopDrawing();

	void FreeResources();

	void DrawBackgound();

private:

	ID2D1Factory* pFactory;
	IDWriteFactory* m_pDWriteFactory{};
	
	ID2D1HwndRenderTarget* pHRT{};
	ID2D1DCRenderTarget* m_pDCRT{};
	ID2D1SolidColorBrush* pBrush;

	IDWriteTextFormat* m_pTextFormat{};

	const D2D1_COLOR_F m_cWindowBackgroundColor{ 0.086f, 0.086f, 0.086f, 1.0f };

	BinApp* pApp{};

public:

	UIGraphics(BinApp *App);
};

