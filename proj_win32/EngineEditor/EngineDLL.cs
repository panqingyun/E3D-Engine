using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace EngineEditor
{
    public delegate void LogOutPutFunc([MarshalAs(UnmanagedType.LPArray, SizeConst = 1024)]byte[] log);
    public class EngineDLL
    {
        public enum MouseButton
        {
            eLeftButton = 0,
            eRightButton,
            eMiddleButton,
            eUnKnown
        };
#if DEBUG
        const string dllName = "EngineCore_d.dll";
#else
        const string dllName = "EngineCore.dll";
#endif
        /// <summary>
        /// 初始化
        /// </summary>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitilizeEngine();

        /// <summary>
        /// 设置目录
        /// </summary>
        /// <param name="path"></param>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetAppDataPath(string path);
        /// <summary>
        /// 初始化
        /// </summary>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetupRenderSystem(IntPtr hWnd, int width, int height);

        /// <summary>
        /// 开始
        /// </summary>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void StartAppliaction();

        /// <summary>
        /// 结束
        /// </summary>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void StopAppliaction();
        
        /// <summary>
        /// 更新
        /// </summary>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void EngineUpdate();
        
        /// <summary>
        /// 销毁
        /// </summary>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void DestoryEngine();

        /// <summary>
        /// 销毁
        /// </summary>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ChageFrameSize(int w, int h);

        /// <summary>
        /// 暂停
        /// </summary>
        /// <param name="bPause"></param>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void PauseEngine(bool bPause);

        /// <summary>
        /// 鼠标按下
        /// </summary>
        /// <param name="mouseButtonID">鼠标键ID 0 左键 1 右键 2 中键</param>
        /// <param name="xPos"></param>
        /// <param name="yPos"></param>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void MouseDown(int mouseButtonID, float xPos, float yPos);

        /// <summary>
        /// 鼠标按下
        /// </summary>
        /// <param name="mouseButtonID">鼠标键ID 0 左键 1 右键 2 中键</param>
        /// <param name="xPos"></param>
        /// <param name="yPos"></param>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void MouseUp(int mouseButtonID, float xPos, float yPos);

        /// <summary>
        /// 鼠标移动
        /// </summary>
        /// <param name="xPos"></param>
        /// <param name="yPos"></param>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void MouseMove(float xPos, float yPos);

        /// <summary>
        /// 键盘按下
        /// </summary>
        /// <param name="key"></param>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void KeyDown(char key);

        /// <summary>
        /// 键盘抬起
        /// </summary>
        /// <param name="key"></param>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void KeyUp(char key);

        /// <summary>
        /// 日志输出函数
        /// </summary>
        /// <param name="func"></param>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void setDebugLogOutFunc(LogOutPutFunc func);

        /// <summary>
        /// 编辑器的地格
        /// </summary>
        [DllImport(dllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void CreateEditorGrid();
    }
}
