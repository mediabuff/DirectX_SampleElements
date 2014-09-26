#pragma once
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"

namespace SampleElements
{
	// Render 2D elements
	class Sample2DSceneRenderer
	{
	public:
		Sample2DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
		HRESULT LoadResourceBitmap(
			ID2D1RenderTarget *pRenderTarget, IWICImagingFactory *pIWICFactory, PCTSTR resourceName,
			PCTSTR resourceType, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **ppBitmap);
	private:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_pBlueBrush;
		Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush> m_pLinearGradientBrush;

		Microsoft::WRL::ComPtr<ID2D1BitmapBrush> m_pBitmapBrush;
	};
}

