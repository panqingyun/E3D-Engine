using System;
using System.Runtime.CompilerServices;

namespace E3DEngine
{
    public enum MouseButton
    {
        LeftButton = 0,
        RightButton,
        MiddleButton,
        UnKnown
    };

    public class MouseButtonInfo
    {
        public MouseButton mButton;
        public int mPositionX;
        public int mPositionY;
    }
    public enum KeyCode
    {
        KeyUnKnown,
        KeyA, KeyB, KeyC, KeyD, KeyE, KeyF, KeyG, KeyH, KeyI, KeyJ, KeyK, KeyL, KeyM,
        KeyN, KeyO, KeyP, KeyQ, KeyR, KeyS, KeyT, KeyU, KeyV, KeyW, KeyX, KeyY, KeyZ,
        Key1, Key2, Key3, Key4, Key5, Key6, Key7, Key8, Key9, Key0,
        KeyShift, KeyAlt, KeyWin, KeyBack, KeySpace, KeyEnter, KeyDelete,
        KeyF1, KeyF2, KeyF3, KeyF4, KeyF5, KeyF6, KeyF7, KeyF8, KeyF9, KeyF10, KeyF11, KeyF12,
    };

    public class Application
	{
		public Application()
		{
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern string getAppDataPath();

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern string getResourcePath();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void exitApplication();

        public static string AppDataPath
		{
			get
			{
				return getAppDataPath();
			}
		}

		public static string ResourcePath
		{
			
			get
			{
				return getResourcePath();
			}
		}

        public static void Exit()
        {
            exitApplication();
        }
	}
}
