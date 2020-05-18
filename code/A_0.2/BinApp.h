#pragma once
#include<Windows.h>
#include<iostream>
#include<exception>
#include<string>
#include<thread>
#include<CommCtrl.h>
#include<sstream>
#include<vector>
#include<d2d1.h>
#include<dwrite.h>


#include<fstream>

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "Comctl32.lib")

#pragma warning(disable : 4996)

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include<bitset>

#include"resource.h"


class Converter {
private:
	
	std::vector<int> a;
	
	int iriginal;
public:
	
	Converter(std::string str, int original) {
		this->iriginal = original;
		//«аносит числа исходного числа в вектор
		for (int i = 0; i < str.length(); i++) {
			this->a.push_back(charToInt(str[i]));
		}
	}

	int charToInt(char c) {
		if (c >= '0' && c <= '9' && (c - '0') < this->iriginal) {
			return c - '0';
		}
		else {
			if (c >= 'A' && c <= 'Z' && (c - 'A') < this->iriginal) {
				return c - 'A' + 10;
			}
			else {
				return -1;
			}
		}
	}

	char intToChar(int c) {
		if (c >= 0 && c <= 9) {
			return c + '0';
		}
		else {
			return c + 'A' - 10;
		}
	}

	int nextNumber(int final) {
		int temp = 0;
		for (int i = 0; i < this->a.size(); i++) {
			temp = temp * this->iriginal + this->a[i];
			a[i] = temp / final;
			temp = temp % final;
		}
		return temp;
	}

	bool zero() {
		for (int i = 0; i < this->a.size(); i++) {
			if (a[i] != 0) {
				return false;
			}
		}
		return true;
	}

	std::string convertTo(int final) {
		std::vector<int> b;
		int size = 0;
		do {
			b.push_back(this->nextNumber(final));
			size++;
		} while (!this->zero());

		std::string sTemp = "";
		for (int i = b.size() - 1; i >= 0; i--) {
			sTemp += intToChar(b[i]);
		}
		return sTemp;
	}
};

class BinApp{
	//--------------------------
	int nCTheme = 0;
	//--------DirectX------------

	ID2D1SolidColorBrush* pBrush;
	ID2D1SolidColorBrush* pSBrush;
	
	D2D1_ELLIPSE  ellipse;

	ID2D1Factory* pFactory;
	IDWriteFactory* m_pDWriteFactory{};
	IDWriteTextFormat* TextFormt{};
	IDWriteTextFormat* TextButtonFormt{};
	IDWriteTextFormat* m_pTextFormat{};
	ID2D1DCRenderTarget* m_pDCRT;

	HDC AppHDC;
	RECT m_rWindowRect{};

	//-------Functions------------

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
		ID_EDIT,
		ID_COMBOBOX,
		ID_COMBOBOX2,
		ID_TEXT_TO
	};
	//---------------------------


	HWND MainHwnd{}, CloseButtonHwnd{}, TranslateButtonHwnd{}, MiniMizeButtonHwnd{}, EditHWND{}, hWndComboBox{}, hWndComboBox2{}, HtextTO{};

	HDC m_hWindowDC{};

	const HRGN m_hSrcRgn{ CreateRectRgn(0,0,350,180) };
	const HRGN m_hSrcRgn1{ CreateRectRgn(2,2,348,375) };

	const int Width{ 350 }, Hieght{ 280 };

	const std::wstring AppName{ L"Bin-VV" };

	static LRESULT CALLBACK ApplicationProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK WindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void initObjMainWindow();

	void CreateNativeControls();

	void LoadSettingFromFile();

	static LRESULT CALLBACK StaticProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam);

	WNDPROC StaticWndProc{};

public:

	BinApp();

	int run();

	~BinApp();

private:

	void onCloseButton();

	void onTransfButton(LPARAM lParam);

	void onMinimizeButton();

	void Paint(HWND hwnd);

	void onCreate();
	
	void onClose();

	void Command(const int& nId, WPARAM wParam, LPARAM lParam);

	void onMove();

	std::wstring Convert(std::wstring number, int NumberSystem, int NumberSystem2);
};

