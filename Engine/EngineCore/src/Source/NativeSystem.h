#pragma once

#include "Interface.h"
#include "E3DDelegate.h"

enum MouseButton
{
	eLeftButton = 0,
	eRightButton,
	eMiddleButton,
	eUnKnown
};

enum KeyCode
{
	KeyA,KeyB,KeyC,KeyD,KeyE,KeyF,KeyG,KeyH,KeyI,KeyJ,KeyK,KeyL,KeyM,
	KeyN,KeyO,KeyP,KeyQ,KeyR,KeyS,KeyT,KeyU,KeyV,KeyW,KeyX,KeyY,KeyZ,
	Key1,Key2,Key3,Key4,Key5,Key6,Key7,Key8,Key9,Key0,
	KeySheift,KeyAlt,KeyWin,KeyBack,KeySpace,KeyEnter,KeyDelete,
	KeyF1,KeyF2,KeyF3,KeyF4,KeyF5,KeyF6,KeyF7,KeyF8,KeyF9,KeyF10,KeyF11,KeyF12,
};

namespace E3DEngine
{
	using MouseEventsDelegates = event Delegates<MouseButton, vec2f>;
	using KeyEventDelegates = event Delegates<KeyCode>;
	using KeyCharEventDelegates = event Delegates<char>;

	class NativeSystem extends IObject
	{
	public: 
		static void OnMouseButtonDown(MouseButton btn, vec2f pos);
		static void OnClick(MouseButton btn, vec2f pos);
		static void OnMouseButtonUp(MouseButton btn, vec2f pos);
		static void OnMouseMove(vec2f pos);
		static void OnkeyDown(char key);
		static void OnKeyUp(char key);
	private: 
		static NativeSystem &Instance()
		{
			static NativeSystem _ins;
			return _ins;
		}
	public:
		MouseEventsDelegates MouseButtonDown;
		MouseEventsDelegates MouseButtonUp;
		MouseEventsDelegates Click;
		MouseEventsDelegates MouseMove;
		KeyEventDelegates KeyDown;
		KeyEventDelegates KeyUp;
		KeyCharEventDelegates KeyChar;
	};
}
