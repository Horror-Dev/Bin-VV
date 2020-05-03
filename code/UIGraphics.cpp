#include "UIGraphics.h"

void UIGraphics::InitD2D1() {
	
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->pFactory);
	if (!SUCCEEDED(hr))
		throw std::runtime_error("Error, With Creating D2D1 factory");

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pDWriteFactory), reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	if (!SUCCEEDED(hr))
		throw std::runtime_error("Error, with Dwrite factory");
}

void UIGraphics::initResources(){
	HRESULT hr;

	D2D1_SIZE_U size = D2D1::SizeU(
		this->pApp->Width,
		this->pApp->Hieght
	);

	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0, D2D1_RENDER_TARGET_USAGE_NONE, D2D1_FEATURE_LEVEL_DEFAULT);

	if (hr = this->pFactory->CreateDCRenderTarget(&props, &this->m_pDCRT); !SUCCEEDED(hr))
		ExitProcess(EXIT_FAILURE);

	if (hr = this->m_pDCRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &this->pBrush); !SUCCEEDED(hr))
		ExitProcess(EXIT_FAILURE);

	if (hr = this->pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(this->pApp->MainHwnd, D2D1::SizeU(this->pApp->Width, this->pApp->Hieght)), &this->pHRT); !SUCCEEDED(hr))
		ExitProcess(EXIT_FAILURE);
}

void UIGraphics::StartDrawing() {
	this->m_pDCRT->BindDC(this->pApp->m_hWindowDC, &this->pApp->m_rWindowRect);
	this->m_pDCRT->BeginDraw();
	this->m_pDCRT->Clear(this->m_cWindowBackgroundColor);
}

void UIGraphics::stopDrawing(){
	this->m_pDCRT->EndDraw();
}

void UIGraphics::FreeResources() {
	safeRelease(&this->pBrush);
	safeRelease(&this->pFactory);
	safeRelease(&this->m_pDWriteFactory);
	safeRelease(&this->m_pTextFormat);
	safeRelease(&this->m_pDWriteFactory);
}

UIGraphics::UIGraphics(BinApp* pApp) : pApp(pApp){
	try{
		this->InitD2D1();
		this->initResources();
	}
	catch (const std::exception& ex){
		std::string exInfo = ex.what();

		MessageBox(NULL, std::wstring(begin(exInfo), end(exInfo)).c_str(), L"Îøèáêà", MB_ICONERROR | MB_OK);
		exit(1);
	}
}

void UIGraphics::DrawBackgound() {
	const D2D1_GRADIENT_STOP gradientStops[] =
	{
		{ 0.1f, D2D1::ColorF(D2D1::ColorF::Blue, 1.0f) },
		{ 0.1f, D2D1::ColorF(D2D1::ColorF::Blue, 1.0f) },
		{ 0.1f, D2D1::ColorF(D2D1::ColorF::Blue, 1.0f) },
		{ 0.1f, D2D1::ColorF(D2D1::ColorF::Blue, 1.0f) }
	};

	ID2D1GradientStopCollection* gSC;

	HRESULT hr = this->pHRT->CreateGradientStopCollection(gradientStops, _countof(gradientStops), &gSC);
	if (!SUCCEEDED(hr)) {
		exit(EXIT_FAILURE);
	}

	const D2D1_SIZE_F size = pHRT->GetSize();
	const D2D1_POINT_2F start = D2D1::Point2F(0.0f, 0.0f);
	const D2D1_POINT_2F end = D2D1::Point2F(size.width, size.height);

	ID2D1LinearGradientBrush* lgb = nullptr;

	const D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES properties = D2D1::LinearGradientBrushProperties(start, end);
	this->pHRT->CreateLinearGradientBrush(properties, gSC, &lgb);

	const D2D1_RECT_F rect = D2D1::RectF(0, 0, size.width, size.height);

	lgb->SetEndPoint(D2D1::Point2F(size.width, size.height));
	this->pHRT->FillRectangle(rect, lgb);
}