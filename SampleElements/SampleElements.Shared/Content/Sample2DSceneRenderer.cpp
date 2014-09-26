
#include "pch.h"
#include "Sample2DSceneRenderer.h"

#include "Common/DirectXHelper.h"

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

using namespace SampleElements;

template<class Interface>
inline void SafeRelease(
	Interface **ppInterfaceToRelease
	)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


Sample2DSceneRenderer::Sample2DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) : m_deviceResources(deviceResources)
{
	CreateDeviceDependentResources();
}

void Sample2DSceneRenderer::Update(DX::StepTimer const& timer)
{

}

void Sample2DSceneRenderer::Render()
{
	ID2D1DeviceContext* context = m_deviceResources->GetD2DDeviceContext();

	// Dash array for dashStyle D2D1_DASH_STYLE_CUSTOM
	float dashes[] = { 1.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f };
	ID2D1StrokeStyle* m_stroke;
	m_deviceResources->GetD2DFactory()->CreateStrokeStyle(
		D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_ROUND,
		D2D1_LINE_JOIN_MITER,
		10.0f,
		D2D1_DASH_STYLE_CUSTOM,
		0.0f),
		dashes,
		ARRAYSIZE(dashes),
		&m_stroke
		);

	context->BeginDraw();
	context->Clear(D2D1::ColorF(D2D1::ColorF::CornflowerBlue));

	/*context->DrawRectangle(
		D2D1::RectF(100.0f, 100.0f, 500.0f, 500.0f),
		m_pBlueBrush.Get(),
		4.0f,
		m_stroke
		);

		context->FillRectangle(
		D2D1::RectF(600.0f, 400.0f, 900.0f, 700.0f),
		m_pLinearGradientBrush.Get()
		);

		context->DrawLine(
		D2D1::Point2F(200, 300),
		D2D1::Point2F(800, 500),
		m_pBlueBrush.Get(),
		10.0f,
		m_stroke
		);*/

	DX::ThrowIfFailed(
		context->EndDraw()
		);
}

void Sample2DSceneRenderer::CreateDeviceDependentResources()
{
	ID2D1DeviceContext* context = m_deviceResources->GetD2DDeviceContext();

	DX::ThrowIfFailed(
		context->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &m_pBlueBrush)
		);
	// Create an array of gradient stops to put in the gradient stop
	// collection that will be used in the gradient brush.
	ID2D1GradientStopCollection *pGradientStops = NULL;

	D2D1_GRADIENT_STOP gradientStops[2];
	gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Yellow, 1);
	gradientStops[0].position = 0.0f;
	gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::ForestGreen, 1);
	gradientStops[1].position = 1.0f;
	// Create the ID2D1GradientStopCollection from a previously
	// declared array of D2D1_GRADIENT_STOP structs.
	context->CreateGradientStopCollection(
		gradientStops,
		2,
		D2D1_GAMMA_2_2,
		D2D1_EXTEND_MODE_CLAMP,
		&pGradientStops
		);

	DX::ThrowIfFailed(
		context->CreateLinearGradientBrush(
		D2D1::LinearGradientBrushProperties(D2D1::Point2F(600, 400), D2D1::Point2F(900, 700)),
		pGradientStops,
		&m_pLinearGradientBrush
		)
		);
}

void Sample2DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_pBlueBrush.Reset();
}


HRESULT Sample2DSceneRenderer::LoadResourceBitmap(
	ID2D1RenderTarget *pRenderTarget, IWICImagingFactory *pIWICFactory, PCTSTR resourceName,
	PCTSTR resourceType, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **ppBitmap)
{
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void *pImageFile = NULL;
	DWORD imageFileSize = 0;

	// Locate the resource.
	imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);
	HRESULT hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}



	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;

	}


	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = pIWICFactory->CreateStream(&pStream);
	}
	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
			);
	}


	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = pIWICFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
			);
	}


	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}


	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}



	if (SUCCEEDED(hr))
	{



		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
			);



	}


	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
			);

	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}
