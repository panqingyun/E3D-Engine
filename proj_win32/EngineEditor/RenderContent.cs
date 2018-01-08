using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EngineEditor
{
    class RenderContent
    {
        [DllImport("kernel32.dll")]
        public static extern int WinExec(string exeName, int operType);
        [DllImport("user32.dll")]
        static extern IntPtr SetParent(IntPtr hWndChild,
          IntPtr hWndNewParent
        );

        [DllImport("Kernel32.dll")]
        static extern Int32 GetLastError();

        [DllImport("user32.dll")]
        static extern Int32 GetWindowLong(IntPtr hWnd, Int32 nIndex );

        [DllImport("user32.dll")]
        static extern Int32 SetWindowLong(IntPtr hWnd, Int32 nIndex, Int32 dwNewLong);

        [DllImport("user32.dll")]
        static extern Int32 SetWindowPos(IntPtr hWnd,
          IntPtr hWndInsertAfter,
          Int32 X,
          Int32 Y,
          Int32 cx,
          Int32 cy,
          UInt32 uFlags
        );
        [DllImport("user32.dll", EntryPoint = "SendMessageA")]
        public static extern int SendMessage(IntPtr hwnd, int wMsg, int wParam, int lParam);
        [DllImport("User32.dll", EntryPoint = "FindWindow")]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

   
        /* 
         * 定义 Win32 常数 
         */
        const Int32 WM_CLOSE = 0x10;
        const Int32 GWL_STYLE = -16;
        const Int32 WS_BORDER = (Int32)0x00800000L;
        const Int32 WS_THICKFRAME = (Int32)0x00040000L;
        const Int32 SWP_NOMOVE = 0x0002;
        const Int32 SWP_NOSIZE = 0x0001;
        const Int32 SWP_NOZORDER = 0x0004;
        const Int32 SWP_FRAMECHANGED = 0x0020;
        const Int32 SW_MAXIMIZE = 3;
        IntPtr HWND_NOTOPMOST = new IntPtr(-2);

        public static void OpenEngine(IntPtr handle,int width, int height)
        {
            
        }

        private static void LoadEvent(ProcessStartInfo info, IntPtr handle)
        {
            
        }

        static void m_innerProcess_Exited(object sender, EventArgs e)
        {
            System.Environment.Exit(0);
        }

        public static void Close()
        {
           
        }
    }

}
