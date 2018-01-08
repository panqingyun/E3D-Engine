using System;
using System.Runtime.CompilerServices;

namespace E3DEngine
{
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
