using E3DEditor.Common;
using E3DEditor.Model;
using E3DEditor.View;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media;

public class LogEntiry
{
    public string LogStr { get; set; }
    public SolidColorBrush LogColor { get; set; }
}

public delegate void LogOutPutFunc(string log);

namespace E3DEditor.ViewModel
{
    public class VM_MainWindow : DependencyObject, INotifyPropertyChanged
    {
        private GameWindow game = new GameWindow();
        private LogOutPutFunc outFunc = null;
        public E3DEngine.EngineDelegateRef RenderDelegate = null;
        private IntPtr windowsPlayerHandle = IntPtr.Zero;
        private Process windowsPlayer = null;
        private Assembly externAsm = null;

        public VM_MainWindow()
        {
            try
            {
                RenderDelegate = new E3DEngine.EngineDelegateRef();
                RenderDelegate.InitilizeEngine();
                outFunc = ShowLog;
                IntPtr ptr = Marshal.GetFunctionPointerForDelegate(outFunc);
                RenderDelegate.SetDebugLogOutFunc(ptr);
            }
            catch
            {
                App.Instance.Setting();
            }
        }

        private bool engineLoaded = false;
        public bool EngineLoaded
        {
            get
            {
                return engineLoaded;
            }
        }

        private MainWindow mainWnd;
        public MainWindow _MainWindow
        {
            get
            {
                return mainWnd;
            }
            set
            {
                mainWnd = value;
            }
        }
        TabItemWithClose gameItem = null;
        TabItemWithClose renderItem = null;
        private void createRenderPanel()
        {
            if (renderItem != null)
            {
                renderItem.Close();
            }
            renderItem = new TabItemWithClose();
            renderItem.Width = 150;
            renderItem.Height = 20;
            renderItem.FontSize = 13;
            renderItem.Header = "编辑器";
            renderItem.HorizontalAlignment = HorizontalAlignment.Stretch;
            renderItem.VerticalAlignment = VerticalAlignment.Stretch;
            RenderPanel rp = new RenderPanel();
            rp.RenderLoaded += Rp_Loaded;
            rp._MouseButtonDown += Rp__MouseLeftButtonDown;
            rp._MouseButtonUp += Rp__MouseLeftButtonUp;
            rp._MouseMove += Rp__MouseMove;
            rp._KeyDown += Rp__KeyDown;
            rp._KeyUp += Rp__KeyUp;
            rp._SizeChange += Rp__SizeChange;
            renderItem.Content = rp;
            mainWnd.renderPanel.Items.Add(renderItem);
            mainWnd.renderPanel.SelectedItem = renderItem;
        }

        #region RenderPanel Event
        private void Rp__SizeChange(object sender, EventArgs e)
        {
            if (!EngineLoaded)
            {
                return;
            }
            RenderPanel rp = sender as RenderPanel;
            RenderDelegate.ChageFrameSize((int)rp.ActualWidth, (int)rp.ActualHeight);
        }

        private void Rp__KeyUp(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (!EngineLoaded)
            {
                return;
            }

            string k = e.Key.ToString();
            App.vm_MainWindow.RenderDelegate.KeyUp((sbyte)k[0]);
        }

        private void Rp__KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (!EngineLoaded)
            {
                return;
            }

            string k = e.Key.ToString();
            App.vm_MainWindow.RenderDelegate.KeyDown((sbyte)k[0]);
        }

        private void Rp__MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (!EngineLoaded)
            {
                return;
            }
            RenderDelegate.MouseMove(e.Location.X, e.Location.Y);
        }

        private void Rp__MouseLeftButtonUp(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (!EngineLoaded)
            {
                return;
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                RenderDelegate.MouseUp((int)eMouseButton.eLeftButton, e.Location.X, e.Location.Y);
            }
            else if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                RenderDelegate.MouseUp((int)eMouseButton.eRightButton, e.Location.X, e.Location.Y);
            }
            else if (e.Button == System.Windows.Forms.MouseButtons.Middle)
            {
                RenderDelegate.MouseUp((int)eMouseButton.eMiddleButton, e.Location.X, e.Location.Y);
            }
        }

        private void Rp__MouseLeftButtonDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (!EngineLoaded)
            {
                return;
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                RenderDelegate.MouseDown((int)eMouseButton.eLeftButton, e.Location.X, e.Location.Y);
            }
            else if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                RenderDelegate.MouseDown((int)eMouseButton.eRightButton, e.Location.X, e.Location.Y);
            }
            else if (e.Button == System.Windows.Forms.MouseButtons.Middle)
            {
                RenderDelegate.MouseDown((int)eMouseButton.eMiddleButton, e.Location.X, e.Location.Y);
            }
        }

        private void Rp_Loaded(IntPtr handle, Size renderSize)
        {
            if (engineLoaded)
            {
                RenderDelegate.ChangeSurface(handle);
                RenderDelegate.ChageFrameSize((int)renderSize.Width, (int)renderSize.Height);
            }
            else
            {
                RenderDelegate.SetupRenderSystem(handle, (int)renderSize.Width, (int)renderSize.Height);
                RenderDelegate.StartAppliaction();
                RenderDelegate.CreateEditor();
                engineLoaded = true;
            }
        }
        #endregion

        public void LoadScene(string scenePath)
        {
            string _sceneName = System.IO.Path.GetFileName(scenePath);
            E3DEngine.SceneRef scene = E3DEngine.SceneManageRef.GetInstance().GetCurScene();
            if (scene != null && scene.GetName() == _sceneName)
            {
                return;
            }

            E3DEngine.SceneManageRef.GetInstance().LoadScene(scenePath);
            mainWnd.objectList.Items.Clear();
            loadGameObjectList();
        }

        private void loadGameObjectList()
        {
            E3DEngine.GameObjectRef gameRootObj = E3DEngine.SceneManageRef.GetInstance().GetCurScene().GetRootObject();
            List<E3DEngine.GameObjectRef> _gameObjectList = gameRootObj.GetChilds();
            gameObjectList = new ObservableCollection<GameObjectNode>();
            GameObjectNode node = new GameObjectNode();
            node.Name = E3DEngine.SceneManageRef.GetInstance().GetCurScene().GetName();
            node.ShowText = node.Name;
            node.mGameObject = gameRootObj;
            gameObjectList.Add(node);
            fillNodeList(_gameObjectList, node.Childs);

            mainWnd.objectList.ItemsSource = gameObjectList;
            RenderDelegate.CreateEditor();
        }

        private Dictionary<int, TabItemWithClose> editorItemMap = new Dictionary<int, TabItemWithClose>();

        public ObservableCollection<GameObjectNode> gameObjectList
        {
            get
            {
                return (ObservableCollection<GameObjectNode>)GetValue(gameObjectListProperty);
            }
            set
            {
                SetValue(gameObjectListProperty, value);
            }
        }

        public static readonly DependencyProperty gameObjectListProperty = DependencyProperty.Register("gameObjectList", 
            typeof(ObservableCollection<GameObjectNode>), typeof(VM_MainWindow));

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        private double prograssBarValue = 0;
        public double PrograssBarValue
        {
            get
            {
                return prograssBarValue;
            }
            set
            {
                prograssBarValue = value;
                OnPropertyChanged("PrograssBarValue");
            }
        }

        private string stateLable = "";
        public string State
        {
            get { return stateLable; }
            set
            {
                stateLable = value;
                OnPropertyChanged("State");
            }
        }

        public BaseCommand MainMenuDeleteButtonCommand
        {
            get
            {
                return new BaseCommand(MainMenuDeleteButtonCommand_Excuted);
            }
        }

        public void MainMenuDeleteButtonCommand_Excuted(object obj)
        {
           
        }


        public bool PauseEngine
        {
            set
            {
                if (!EngineLoaded)
                {
                    return;
                }
                COPYDATASTRUCT stru = new COPYDATASTRUCT();
                stru.dwData = new IntPtr(1);
                bool isCheck = (bool)value;
                if (isCheck)
                {
                    stru.cbData = 1;
                }
                else
                {
                    stru.cbData = 0;
                }

                SendMsg2WindowsPlayer(stru);
            }
        }

        private bool isEditor = true;
        public bool IsEditor
        {
            get
            {
                return isEditor;
            }
            set
            {
                isEditor = value;
            }
        }
        
        public BaseCommand MainMenuNewButtonCommand
        {
            get
            {
                return new BaseCommand(MainMenuNewButtonCommand_Excuted);
            }
        }

        public void MainMenuNewButtonCommand_Excuted(object obj)
        {
        }

        public BaseCommand MainTitleButtonCommand
        {
            get
            {
                return new BaseCommand(MainButtonCommand_Executed);
            }
        }

        public void MainButtonCommand_Executed(object obj)
        {
            string pageName = obj.ToString();
            switch (pageName)
            {
                case "Close":
                    {
                        if (windowsPlayer != null)
                        {
                            windowsPlayer.Kill();
                        }
                        Environment.Exit(0);
                    }
                    break;
                case "Min":
                    {
                        _MainWindow.WindowState = WindowState.Minimized;
                    }
                    break;
                case "Run":
                    {
                        runGame();
                    }
                    break;
                default:break;
            }
        }

        private void runGame()
        {
            if (Config.GamePath == "")
                return;
            string path = System.Windows.Forms.Application.StartupPath;
            if (windowsPlayer != null)
            {
                mainWnd.renderPanel.SelectedItem = gameItem;
            }
            else
            {
                string cmdLine = Config.GamePath + "," + (new WindowInteropHelper(mainWnd).Handle);
                windowsPlayer = Process.Start(path + "/../WindowsPlayer/Client.exe", cmdLine);
                windowsPlayer.Exited += WindowsPlayer_Exited;
                while (windowsPlayer.MainWindowHandle == IntPtr.Zero)
                {

                }
                windowsPlayerHandle = windowsPlayer.MainWindowHandle;
                createGameWindow();
            }
            PauseEngine = (bool)mainWnd.Pause.IsChecked;
        }

        private void createGameWindow()
        {
            RenderPanel rp = null;
            if (gameItem != null)
            {
                rp = gameItem.Content as RenderPanel;
            }
            else
            {
                gameItem = new TabItemWithClose();
                gameItem.Header = "Game";
                gameItem.Width = 150;
                gameItem.Height = 20;
                gameItem.Closed += GameItem_Closed;
                rp = new RenderPanel();
                rp._SizeChange += Rp__SizeChange1;
                rp.Loaded += Rp_Loaded1;
                gameItem.Content = rp;

            }

            mainWnd.renderPanel.Items.Add(gameItem);
            mainWnd.renderPanel.SelectedItem = gameItem;

            Win32.SetParent(windowsPlayerHandle, rp.Handle);
            Int32 wndStyle = Win32.GetWindowLong(windowsPlayerHandle, Win32.GWL_STYLE);
            wndStyle &= ~Win32.WS_BORDER;
            wndStyle &= ~Win32.WS_THICKFRAME;
            Win32.SetWindowLong(windowsPlayerHandle, Win32.GWL_STYLE, wndStyle);
            Win32.SetWindowPos(windowsPlayerHandle, IntPtr.Zero, 0, 0, 0, 0,  Win32.SWP_NOMOVE | Win32.SWP_NOSIZE | Win32.SWP_NOZORDER | Win32.SWP_FRAMECHANGED);

        }

        private void Rp_Loaded1(object sender, RoutedEventArgs e)
        {
            RenderPanel rp = gameItem.Content as RenderPanel;
            // 在Resize事件中更新目标应用程序的窗体尺寸. 
            Win32.SetWindowPos(windowsPlayerHandle, IntPtr.Zero, 0, 0, (int)rp.ActualWidth, (int)rp.ActualHeight, Win32.SWP_NOZORDER);
        }

        private void Rp__SizeChange1(object sender, EventArgs e)
        {
            RenderPanel rp = gameItem.Content as RenderPanel;
            // 在Resize事件中更新目标应用程序的窗体尺寸. 
            Win32.SetWindowPos(windowsPlayerHandle, IntPtr.Zero, 0, 0, (int)rp.ActualWidth, (int)rp.ActualHeight, Win32.SWP_NOZORDER);
        }

        private void GameItem_Closed(object sender, EventArgs e)
        {
            if (windowsPlayer == null)
                return;
            windowsPlayer.Kill();
            windowsPlayer = null;
        }

        private void WindowsPlayer_Exited(object sender, EventArgs e)
        {
            windowsPlayer = null;
        }

        public void RevWindowsPlayerData(COPYDATASTRUCT data)
        {
            switch(data.dwData.ToInt32())
            {
                case (int)DataType.eLog:
                    {
                        string log = data.lpData.ToString();
                        ShowLog(log);
                    }
                    break;
            }
        }

        public void SendMsg2WindowsPlayer(COPYDATASTRUCT data)
        {
            Win32.SendMessage(windowsPlayerHandle, Win32.WM_COPYDATA, IntPtr.Zero, ref data);
        }

        public PropertiesView PropertyView
        {
            get { return _MainWindow.properties; }
        }
        
        private void item_Closed(object sender, EventArgs e)
        {
           
        }
        
        public void ShowLog(string log)
        {
            if (log == null)
                return;
            LogEntiry loge = new LogEntiry();
            loge.LogStr = log;
            if (log.Contains("[error]"))
            {
                loge.LogColor = Brushes.Red;
            }
            else if (log.Contains("[warning]"))
            {
                loge.LogColor = Brushes.Yellow;
            }
            else
            {
                loge.LogColor = Brushes.White;
            }
            _MainWindow.logList.Items.Add(loge);
            _MainWindow.logList.ScrollIntoView(loge);
        }

        private void fillNodeList(List<E3DEngine.GameObjectRef> _gameObjectList,ObservableCollection<GameObjectNode> nodeList)
        {
            for (int i = 0; i < _gameObjectList.Count; i++)
            {
                GameObjectNode node = new GameObjectNode();
                node.Name = _gameObjectList[i].GetName();
                node.ShowText = node.Name;
                node.mGameObject = _gameObjectList[i];
                fillNodeList(_gameObjectList[i].GetChilds(), node.Childs);
                nodeList.Add(node);
            }
        }

        public void MenuItemCommand(string menuName)
        {
            if (menuName == "openSln")
            {
                openSln();
            }
            else if(menuName == "newSln")
            {

            }
        }

        private void loadEditorMenuItem()
        {
            string dllPath = Config.GamePath + "../Library/EditorCSharp.dll";
            externAsm = Assembly.LoadFrom(dllPath);
            if (externAsm == null)
            {
                return;
            }
            Type[] types = externAsm.GetTypes();
            object[] menuItems = externAsm.GetCustomAttributes(typeof(MenuItemAttribute), false);
            for(int i = 0; i < menuItems.Length; i++)
            {

            }
        }

        private void openSln()
        {
            string filePath = IOFile.OpenFile();
            string[] fileContents = System.IO.File.ReadAllLines(filePath);
            for (int i = 0; i < fileContents.Length; i++)
            {
                if (fileContents[i].Contains("assets"))
                {
                    Config.GamePath = System.IO.Path.GetDirectoryName(filePath) + "/" + fileContents[i].Split('=')[1] + "/";

                    RenderDelegate.SetAppDataPath(Config.GamePath);
                    createRenderPanel();
                    mainWnd.fileView.viewModel.LoadDirectory();
                    loadEditorMenuItem();
                }
            }
        }
    }
}
