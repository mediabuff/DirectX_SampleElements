#pragma once

#include "Common\DeviceResources.h"
#include "Common\StepTimer.h"
#include "Common\SceneBase.h"

using namespace Base;

namespace SampleElements
{
	// Render 2D elements
	class Sample2DSceneRenderer : SceneBase
	{
	public:
		Sample2DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		virtual void CreateDeviceDependentResources();
		virtual void ReleaseDeviceDependentResources();
		virtual void Update(DX::StepTimer const& timer);
		virtual void Render();
	private:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_pBlueBrush;
		Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush> m_pLinearGradientBrush;
		Microsoft::WRL::ComPtr<ID2D1BitmapBrush> m_pBitmapBrush;
		Microsoft::WRL::ComPtr<ID2D1Bitmap> m_pBitmap;

		float padding;
	};
}

