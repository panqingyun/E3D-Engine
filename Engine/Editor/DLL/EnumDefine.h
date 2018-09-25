#pragma once

#pragma managed

namespace E3DEngine
{

	[Serializable]
	[FlagsAttribute]
	public enum class MouseButton
	{
		eLeftButton = 0,
		eRightButton,
		eMiddleButton,
		eUnKnown
	};
}
#pragma unmanaged