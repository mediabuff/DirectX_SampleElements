﻿#pragma once

#include "pch.h"
#include "Common\DeviceResources.h"
#include "SampleElementsMain.h"

namespace SampleElements
{
	// Main entry point for our app. Connects the app with the Windows shell and handles application lifecycle events.
	ref class App sealed : public Windows::ApplicationModel::Core::IFrameworkView
	{
	public:
		App();

		// IFrameworkView Methods.
		virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
		virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
		virtual void Load(Platform::String^ entryPoint);
		virtual void Run();
		virtual void Uninitialize();

protected:
		// Application lifecycle event handlers.
		void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args);
		void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
		void OnResuming(Platform::Object^ sender, Platform::Object^ args);

		// Window event handlers.
#if !(WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
		void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
#endif
		void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
		void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);

		// DisplayInformation event handlers.
#if !(WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
		void OnDpiChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
		void OnOrientationChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
#endif
		void OnDisplayContentsInvalidated(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);

	private:
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		std::unique_ptr<SampleElementsMain> m_main;
		Platform::Agile<Windows::UI::Input::GestureRecognizer> m_gestureRecognizer;
		bool m_windowClosed;
		bool m_windowVisible;
		void OnPointerPressed(Windows::UI::Core::CoreWindow ^sender, Windows::UI::Core::PointerEventArgs ^args);
		void OnPointerReleased(Windows::UI::Core::CoreWindow ^sender, Windows::UI::Core::PointerEventArgs ^args);
		void OnPointerMoved(Windows::UI::Core::CoreWindow ^sender, Windows::UI::Core::PointerEventArgs ^args);
		void OnTapped(Windows::UI::Input::GestureRecognizer ^sender, Windows::UI::Input::TappedEventArgs ^args);
		void OnDragging(Windows::UI::Input::GestureRecognizer ^sender, Windows::UI::Input::DraggingEventArgs ^args);
		void OnHolding(Windows::UI::Input::GestureRecognizer ^sender, Windows::UI::Input::HoldingEventArgs ^args);
	};
}

ref class Direct3DApplicationSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
{
public:
	virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();
};
