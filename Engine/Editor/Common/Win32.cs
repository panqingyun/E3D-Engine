using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEditor.Common
{
    public class Win32
    {
        public const int SW_FORCEMINIMIZE   = 11; // 最小化窗口
        public const int SW_HIDE            = 0;  // 隐藏窗口并激活其他窗口
        public const int SW_MAXIMIZE        = 3;  // 最大化指定的窗口
        public const int SW_MINIMIZE        = 6;  // 最小化指定的窗口并且激活在Z序中的下一个顶层窗口
        public const int SW_RESTORE         = 9;  // 激活并显示窗口
        public const int SW_SHOW            = 5;  // 在窗口原来的位置以原来的尺寸激活和显示窗口
        public const int SW_SHOWDEFAULT     = 10; // 
        public const int SW_SHOWMAXIMIZED   = 3;  // 激活窗口并将其最大化。
        public const int SW_SHOWMINIMIZED   = 2;  // 激活窗口并将其最小化
        public const int SW_SHOWMINNOACTIVE = 7;  // 窗口最小化，激活窗口仍然维持激活状态。
        public const int SW_SHOWNA          = 8;  // 以窗口原来的状态显示窗口
        public const int SW_SHOWNOACTIVATE  = 4;  // 以窗口最近一次的大小和状态显示窗口
        public const int SW_SHOWNORMAL      = 1;  // 激活并显示一个窗口
        public const int WM_NULL            = 0x0000;
        public const int WM_CREATE          = 0x0001; // 创建一个窗口
        public const int WM_DESTROY         = 0x0002; // 当一个窗口被破坏时发送
        public const int WM_MOVE            = 0x0003; // 移动一个窗口
        public const int WM_SIZE            = 0x0005; // 改变一个窗口的大小
        public const int WM_ACTIVATE        = 0x0006; // 一个窗口被激活或失去激活状态
        public const int WA_INACTIVE        = 0;
        public const int WA_ACTIVE          = 1;
        public const int WA_CLICKACTIVE     = 2;
        public const int WM_SETFOCUS        = 0x0007; // 一个窗口获得焦点
        public const int WM_KILLFOCUS       = 0x0008; // 一个窗口失去焦点
        public const int WM_ENABLE          = 0x000A; // 一个窗口改变成Enable状态
        public const int WM_SETREDRAW       = 0x000B; // 设置窗口是否能重画
        public const int WM_SETTEXT         = 0x000C; // 应用程序发送此消息来设置一个窗口的文本
        public const int WM_GETTEXT         = 0x000D; // 应用程序发送此消息来复制对应窗口的文本到缓冲区
        public const int WM_GETTEXTLENGTH   = 0x000E; // 得到与一个窗口有关的文本的长度（不包含空字符）
        public const int WM_PAINT           = 0x000F; // 要求一个窗口重画自己
        public const int WM_CLOSE           = 0x0010; // 当一个窗口或应用程序要关闭时发送一个信号
        public const int WM_QUERYENDSESSION = 0x0011; // 当用户选择结束对话框或程序自己调用ExitWindows函数
        public const int WM_QUERYOPEN       = 0x0013; // 当用户窗口恢复以前的大小位置时，把此消息发送给某个图标
        public const int WM_ENDSESSION      = 0x0016; // 当系统进程发出WM_QUERYENDSESSION消息后，此消息发送给应用程序，通知它对话是否结束
        public const int WM_QUIT            = 0x0012; // 用来结束程序运行
        public const int WM_ERASEBKGND      = 0x0014; // 当窗口背景必须被擦除时（例在窗口改变大小时）
        public const int WM_SYSCOLORCHANGE  = 0x0015; // 当系统颜色改变时，发送此消息给所有顶级窗口
        public const int WM_SHOWWINDOW      = 0x0018; // 当隐藏或显示窗口是发送此消息给这个窗口        
        public const int WM_WININICHANGE    = 0x001A;
        public const int WM_DEVMODECHANGE   = 0x001B;
        public const int WM_ACTIVATEAPP     = 0x001C; // 发此消息给应用程序哪个窗口是激活的，哪个是非激活的
        public const int WM_FONTCHANGE      = 0x001D; // 当系统的字体资源库变化时发送此消息给所有顶级窗口
        public const int WM_TIMECHANGE      = 0x001E; // 当系统的时间变化时发送此消息给所有顶级窗口
        public const int WM_CANCELMODE      = 0x001F; // 发送此消息来取消某种正在进行的摸态（操作）
        public const int WM_SETCURSOR       = 0x0020; // 如果鼠标引起光标在某个窗口中移动且鼠标输入没有被捕获时，就发消息给某个窗口
        public const int WM_MOUSEACTIVATE   = 0x0021; // 当光标在某个非激活的窗口中而用户正按着鼠标的某个键发送此消息给当前窗口
        public const int WM_CHILDACTIVATE   = 0x0022; // 发送此消息给MDI子窗口当用户点击此窗口的标题栏，或当窗口被激活，移动，改变大小
        public const int WM_QUEUESYNC       = 0x0023; // 此消息由基于计算机的训练程序发送，通过WH_JOURNALPALYBACK的hook程序分离出用户输入消息
        public const int WM_GETMINMAXINFO   = 0x0024; // 此消息发送给窗口当它将要改变大小或位置
        public const int WM_PAINTICON       = 0x0026; // 发送给最小化窗口当它图标将要被重画
        public const int WM_ICONERASEBKGND  = 0x0027; // 此消息发送给某个最小化窗口，仅当它在画图标前它的背景必须被重画
        public const int WM_NEXTDLGCTL      = 0x0028; // 发送此消息给一个对话框程序去更改焦点位置
        public const int WM_SPOOLERSTATUS   = 0x002A; // 每当打印管理列队增加或减少一条作业时发出此消息
        public const int WM_DRAWITEM        = 0x002B; // 当button，combobox，listbox，menu的可视外观改变时发送
        public const int WM_MEASUREITEM     = 0x002C; // 当button, combo box, list box, list view control, or menu item 被创建时
        public const int WM_DELETEITEM      = 0x002D;    
        public const int WM_VKEYTOITEM      = 0x002E; // 此消息有一个LBS_WANTKEYBOARDINPUT风格的发出给它的所有者来响应WM_KEYDOWN消息
        public const int WM_CHARTOITEM      = 0x002F; // 此消息由一个LBS_WANTKEYBOARDINPUT风格的列表框发送给他的所有者来响应WM_CHAR消息
        public const int WM_SETFONT         = 0x0030; // 当绘制文本时程序发送此消息得到控件要用的颜色
        public const int WM_GETFONT         = 0x0031; // 应用程序发送此消息得到当前控件绘制文本的字体
        public const int WM_SETHOTKEY       = 0x0032; // 应用程序发送此消息让一个窗口与一个热键相关连
        public const int WM_GETHOTKEY       = 0x0033; // 应用程序发送此消息来判断热键与某个窗口是否有关联
        public const int WM_QUERYDRAGICON   = 0x0037; // 此消息发送给最小化窗口，当此窗口将要被拖放而它的类中没有定义图标，应用程序能返回一个图标或光标的句柄，当用户拖放图标时系统显示这个图标或光标
        public const int WM_COMPAREITEM     = 0x0039; // 发送此消息来判定combobox或listbox新增加的项的相对位置
        public const int WM_COMPACTING      = 0x0041; // 显示内存已经很少了
        public const int WM_COMMNOTIFY      = 0x0044; /* no longer suported */

        public const int WM_WINDOWPOSCHANGING   = 0x0046; //发送此消息给那个窗口的大小和位置将要被改变时，来调用setwindowpos函数或其它窗口管理函数
        public const int WM_WINDOWPOSCHANGED    = 0x0047; //发送此消息给那个窗口的大小和位置已经被改变时，来调用setwindowpos函数或其它窗口管理函数
        public const int WM_POWER               = 0x0048; //当系统将要进入暂停状态时发送此消息                                                         
        public const uint ERROR_ALREADY_EXISTS  = 183;
        /// <summary>
        /// 内存复制
        /// </summary>
        /// <param name="dest">目标</param>
        /// <param name="src">源</param>
        /// <param name="count">数目</param>
        /// <returns></returns>
        [DllImport("msvcrt.dll", EntryPoint = "memcpy", CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        public static extern IntPtr memcopy(byte[] dest, byte[] src, int count);

        /// <summary>
        /// 内存复制
        /// </summary>
        /// <param name="dest">目标</param>
        /// <param name="src">源</param>
        /// <param name="count">数目</param>
        /// <returns></returns>
        [DllImport("msvcrt.dll", EntryPoint = "memcpy", CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        public static extern IntPtr memcopy(byte[] dest, string src, int count);

        /// <summary>
        /// 内存赋值
        /// </summary>
        /// <param name="dest">目标</param>
        /// <param name="value">值</param>
        /// <param name="count">数目</param>
        /// <returns></returns>
        [DllImport("msvcrt.dll", EntryPoint = "memset", CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        public static extern IntPtr memset(byte[] dest, int value, int count);

        /// <summary>
        /// 查找窗体
        /// </summary>
        /// <param name="lpClassName"></param>
        /// <param name="lpWindowName"></param>
        /// <returns></returns>
        [DllImport("User32.dll", EntryPoint = "FindWindow")]
        public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        /// <summary>
        /// 找子窗体  
        /// </summary>
        /// <param name="hwndParent"></param>
        /// <param name="hwndChildAfter"></param>
        /// <param name="lpszClass"></param>
        /// <param name="lpszWindow"></param>
        /// <returns></returns>
        [DllImport("user32.dll", EntryPoint = "FindWindowEx")]
        public static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);

        /// <summary>
        /// 用于发送信息给窗体
        /// </summary>
        /// <param name="hWnd"></param>
        /// <param name="Msg"></param>
        /// <param name="wParam"></param>
        /// <param name="lParam"></param>
        /// <returns></returns>
        [DllImport("User32.dll", EntryPoint = "SendMessage")]      
        public static extern int SendMessage(IntPtr hWnd, int Msg, IntPtr wParam, string lParam);

        /// <summary>
        /// 显示窗体
        /// </summary>
        /// <param name="hWnd">指窗口句柄</param>
        /// <param name="type">指定窗口如何显示</param>
        /// <returns>如果窗口之前可见，则返回值为true。如果窗口之前被隐藏，则返回值为false</returns>
        [DllImport("User32.dll", EntryPoint = "ShowWindow")]   //
        public static extern bool ShowWindow(IntPtr hWnd, int type);

        /// <summary>
        /// 置由不同线程产生的窗口的显示状态
        /// </summary>
        /// <param name="hWnd">窗口句柄</param>
        /// <param name="cmdShow">指定窗口如何显示</param>
        /// <returns>如果函数原来可见，返回值为true；如果函数原来被隐藏，返回值为false</returns>
        [DllImport("User32.dll")]
        public static extern bool ShowWindowAsync(System.IntPtr hWnd, int cmdShow);

        /// <summary>
        /// 设置为顶层窗体
        /// </summary>
        /// <param name="hWnd"></param>
        /// <returns></returns>
        [DllImport("User32.dll")]
        public static extern bool SetForegroundWindow(System.IntPtr hWnd);

        /// <summary>
        /// 互斥窗口
        /// </summary>
        /// <param name="lpMutexAttributes"></param>
        /// <param name="bInitialOwner"></param>
        /// <param name="lpName"></param>
        /// <returns></returns>
        [DllImport("Kernel32.dll" ,EntryPoint = "CreateMutex")]
        public static extern IntPtr CreateMutex(IntPtr lpMutexAttributes, bool bInitialOwner, string lpName);

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        [DllImport("Kernel32.dll", EntryPoint = "GetLastError")]
        public static extern uint GetLastError();
    }
}
