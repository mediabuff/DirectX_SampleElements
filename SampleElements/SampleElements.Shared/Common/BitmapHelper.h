#pragma once

#include "pch.h"
#include "DeviceResources.h"
#include "DirectXHelper.h"

using namespace DX;
using namespace D2D1;
using namespace Microsoft::WRL;

namespace BitmapHelper
{
	inline HRESULT LoadBitmapFromFile(DeviceResources *pDeviceResources, PCWSTR uri, ID2D1Bitmap **ppBitmap)
	{
		HRESULT hr;
		ID2D1DeviceContext1 *context = pDeviceResources->GetD2DDeviceContext();
		IWICImagingFactory2 *m_wicFactory = pDeviceResources->GetWicImagingFactory();

		ComPtr<IWICBitmapDecoder> wicBitmapDecoder;
		hr = m_wicFactory->CreateDecoderFromFilename(
			uri,
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnDemand,
			&wicBitmapDecoder
			);

		ComPtr<IWICBitmapFrameDecode> wicBitmapFrame;
		if (SUCCEEDED(hr))
		{
			hr = wicBitmapDecoder->GetFrame(0, &wicBitmapFrame);
		}

		ComPtr<IWICFormatConverter> wicFormatConverter;
		if (SUCCEEDED(hr))
		{
			hr = m_wicFactory->CreateFormatConverter(&wicFormatConverter);
		}

		if (SUCCEEDED(hr))
		{
			hr = wicFormatConverter->Initialize(
				wicBitmapFrame.Get(),
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				nullptr,
				0.0,
				WICBitmapPaletteTypeCustom  // the BGRA format has no palette so this value is ignored
				);
		}

		double dpiX, dpiY;
		if (SUCCEEDED(hr))
		{
			hr = wicFormatConverter->GetResolution(&dpiX, &dpiY);
		}

		if (SUCCEEDED(hr))
		{
			hr = context->CreateBitmapFromWicBitmap(
				wicFormatConverter.Get(),
				BitmapProperties(
				PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
				static_cast<float>(dpiX),
				static_cast<float>(dpiY)
				),
				ppBitmap
				);
		}
		return hr;
	}

	inline HRESULT CreateBitmapBrush(DeviceResources *pDeviceResources, PCWSTR uri, ID2D1BitmapBrush **ppBitmapBrush)
	{
		Microsoft::WRL::ComPtr<ID2D1Bitmap> ppBitmap;

		auto hr = LoadBitmapFromFile(pDeviceResources, uri, &ppBitmap);
		auto context = pDeviceResources->GetD2DDeviceContext();
		hr = context->CreateBitmapBrush(ppBitmap.Get(), ppBitmapBrush);
		return hr;
	}
}