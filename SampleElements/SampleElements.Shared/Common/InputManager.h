#pragma once

#include "pch.h"

using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::Foundation;


namespace InputManager
{
	ref class InputManager
	{
	public:
		void Initialize(CoreWindow^ window);

	private:
		Platform::Agile<GestureRecognizer> m_gestureRecognizer;

		void OnPointerPressed(CoreWindow ^sender, PointerEventArgs ^args);
		void OnPointerReleased(CoreWindow ^sender, PointerEventArgs ^args);
		void OnPointerMoved(CoreWindow ^sender, PointerEventArgs ^args);
		void OnTapped(GestureRecognizer ^sender, TappedEventArgs ^args);
		void OnDragging(GestureRecognizer ^sender, DraggingEventArgs ^args);
		void OnHolding(GestureRecognizer ^sender, HoldingEventArgs ^args);
	};
	extern InputManager^ m_inputManager;

}

