#include "NativeSystem.h"

namespace E3DEngine
{
	NativeSystem::NativeSystem()
	{
		m_keyCodeMap['a'] = KeyA;
		m_keyCodeMap['A'] = KeyA;
		m_keyCodeMap['b'] = KeyB;
		m_keyCodeMap['B'] = KeyB;
		m_keyCodeMap['c'] = KeyC;
		m_keyCodeMap['C'] = KeyC;
		m_keyCodeMap['d'] = KeyD;
		m_keyCodeMap['D'] = KeyD;
		m_keyCodeMap['e'] = KeyE;
		m_keyCodeMap['E'] = KeyE;
		m_keyCodeMap['f'] = KeyF;
		m_keyCodeMap['F'] = KeyF;
		m_keyCodeMap['g'] = KeyG;
		m_keyCodeMap['G'] = KeyG;
		m_keyCodeMap['h'] = KeyH;
		m_keyCodeMap['H'] = KeyH;
		m_keyCodeMap['i'] = KeyI;
		m_keyCodeMap['I'] = KeyI;
		m_keyCodeMap['j'] = KeyJ;
		m_keyCodeMap['J'] = KeyJ;
		m_keyCodeMap['k'] = KeyK;
		m_keyCodeMap['K'] = KeyK;
		m_keyCodeMap['l'] = KeyL;
		m_keyCodeMap['L'] = KeyL;
		m_keyCodeMap['m'] = KeyM;
		m_keyCodeMap['M'] = KeyM;
		m_keyCodeMap['n'] = KeyN;
		m_keyCodeMap['N'] = KeyN;
		m_keyCodeMap['o'] = KeyO;
		m_keyCodeMap['O'] = KeyO;
		m_keyCodeMap['p'] = KeyP;
		m_keyCodeMap['P'] = KeyP;
		m_keyCodeMap['Q'] = KeyQ;
		m_keyCodeMap['q'] = KeyQ;
		m_keyCodeMap['r'] = KeyR;
		m_keyCodeMap['R'] = KeyR;
		m_keyCodeMap['s'] = KeyS;
		m_keyCodeMap['S'] = KeyS;
		m_keyCodeMap['t'] = KeyT;
		m_keyCodeMap['T'] = KeyT;
		m_keyCodeMap['U'] = KeyU;
		m_keyCodeMap['u'] = KeyU;
		m_keyCodeMap['v'] = KeyV;
		m_keyCodeMap['V'] = KeyV;
		m_keyCodeMap['w'] = KeyW;
		m_keyCodeMap['W'] = KeyW;
		m_keyCodeMap['x'] = KeyX;
		m_keyCodeMap['X'] = KeyX;
		m_keyCodeMap['y'] = KeyY;
		m_keyCodeMap['Y'] = KeyY;
		m_keyCodeMap['z'] = KeyZ;
		m_keyCodeMap['Z'] = KeyZ;
	}


	KeyCode NativeSystem::GetKeyCode(char key)
	{
		if (Instance().m_keyCodeMap.find(key) == Instance().m_keyCodeMap.end())
		{
			return KeyUnKnown;
		}
		return Instance().m_keyCodeMap[key];
	}

}