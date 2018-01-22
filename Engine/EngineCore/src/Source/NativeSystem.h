#pragma once

#include "Interface.h"
#include "E3DDelegate.h"
#include "../Mono/MonoScriptManager.h"

enum KeyCode
{
	KeyUnKnown,
	KeyA,KeyB,KeyC,KeyD,KeyE,KeyF,KeyG,KeyH,KeyI,KeyJ,KeyK,KeyL,KeyM,
	KeyN,KeyO,KeyP,KeyQ,KeyR,KeyS,KeyT,KeyU,KeyV,KeyW,KeyX,KeyY,KeyZ,
	Key1,Key2,Key3,Key4,Key5,Key6,Key7,Key8,Key9,Key0,
	KeySheift,KeyAlt,KeyWin,KeyBack,KeySpace,KeyEnter,KeyDelete,
	KeyF1,KeyF2,KeyF3,KeyF4,KeyF5,KeyF6,KeyF7,KeyF8,KeyF9,KeyF10,KeyF11,KeyF12,
};

namespace E3DEngine
{

#define MOUSE_MOVE "MouseMove"
#define MOUSE_BUTTON_DOWN "MouseButtonDown"
#define MOUSE_BUTTON_UP "MouseButtonUp"
#define KEY_DOWN "KeyDown"
#define KEY_UP "KeyUp"

	/*using MouseEventsDelegates = event Delegates<MouseButton, vec2f>;
	using KeyEventDelegates = event Delegates<KeyCode>;
	using KeyCharEventDelegates = event Delegates<char>;
	*/
	static class NativeSystem : public IObject
	{
	public:
		NativeSystem();
		static KeyCode GetKeyCode(char key);
	private: 
		static NativeSystem &Instance()
		{
			static NativeSystem _ins;
			return _ins;
		}
		std::map<char, KeyCode> m_keyCodeMap;
	};
}
