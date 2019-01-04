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
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;

public class LogEntiry
{
    public string LogStr { get; set; }
    public SolidColorBrush LogColor { get; set; }
    public ImageSource LogIcon { get; set; }
}

namespace E3DEditor.ViewModel
{
    public delegate void ThreadOperateDelegate(int thread_id, int thread_op_type);
    public class VM_MainWindow : DependencyObject, INotifyPropertyChanged
    {
        #region Property Field

        public E3DEngine.EngineDelegateRef RenderDelegate = null;

        System.Windows.Forms.Timer myTimer = new System.Windows.Forms.Timer();
        private System.Threading.Thread physicsThread = null;
        private System.Threading.Thread renderThread = null;
        private ShowLogDelegate outFunc = null;
        private ThreadOperateDelegate threadFunc = null;
        private ThreadOperateDelegate threadLockFunc = null;
        private IntPtr windowsPlayerHandle = IntPtr.Zero;
        private Process windowsPlayer = null;
        private Assembly externAsm = null;
        private string curScenePath = "";
        private bool sceneIsStart = false;
        private TabItemWithClose gameItem = null;
        private TabItemWithClose renderItem = null;
        private Size renderViewInitSize;
        private IntPtr renderViewHandle;
        private bool renderInited = false;

        private object renderLock = new object();
        private object physicLock = new object();
        private Dictionary<int, Thread> threadMap = new Dictionary<int, Thread>();

        private bool engineLoaded = false;
        public bool EngineLoaded
        {
            get
            {
                return engineLoaded;
            }
            private set
            {
                if (engineLoaded == true)
                {
                    return;
                }
                engineLoaded = value;
                E3DEngine.SceneManageRef.GetInstance().SetRunPath(System.Windows.Forms.Application.StartupPath);
                myTimer.Tick += new EventHandler(engineUpdate);
                myTimer.Enabled = true;
                myTimer.Interval = 10;
                myTimer.Start();
            }
        }

        public bool IsRun
        {
            get { return sceneIsStart; }
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

        private string windowTitle = "";
        public string WindowTitle
        {
            get
            {
                return windowTitle;
            }
            set
            {
                windowTitle = value;
                OnPropertyChanged("WindowTitle");
            }
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

        private int fps = 0;
        public int GameFPS
        {
            get
            {
                return RenderDelegate.GetFPS();
            }
            set
            {
                OnPropertyChanged("GameFPS");
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

        private bool pauseEngine = false;
        public bool PauseEngine
        {
            get { return pauseEngine; }
            set
            {
                if (!EngineLoaded)
                {
                    return;
                }
                pauseGame(value);
                if (!IsRun)
                {
                    return;
                }
                pauseEngine = value;
                if (sceneIsStart)
                {
                    RenderDelegate.RunCurrentScene(!value);
                }
                OnPropertyChanged("PauseEngine");
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
        public PropertiesView PropertyView
        {
            get { return _MainWindow.properties; }
        }

        private string sceneName = "";
        public string SceneName
        {
            get { return sceneName; }
            set
            {
                sceneName = value;
                OnPropertyChanged("SceneName");
            }
        }

        private bool isHorMove = true;
        public bool IsHorzitalMove
        {
            get { return isHorMove; }
            set
            {
                isHorMove = value;
                if(value)
                {
                    E3DEngine.SceneManageRef.GetInstance().SetMoveDirection(E3DEngine.ObjectMoveDirection.HORZITAL);
                }
                OnPropertyChanged("IsHorzitalMove");
            }
        }

        private bool isVerMove = false;
        public bool IsVerticalMove
        {
            get { return isVerMove; }
            set
            {
                isVerMove = value;
                if (value)
                {
                    E3DEngine.SceneManageRef.GetInstance().SetMoveDirection(E3DEngine.ObjectMoveDirection.VERTICAL);
                }
                OnPropertyChanged("IsVerticalMove");
            }
        }

        #endregion

        public VM_MainWindow()
        {
            RenderDelegate = new E3DEngine.EngineDelegateRef();
            RenderDelegate.InitilizeEngine();
            outFunc = ShowLog;
            threadFunc = operateThread;
            threadLockFunc = lockThread;
            IntPtr ptr = Marshal.GetFunctionPointerForDelegate(outFunc);
            IntPtr tptr = Marshal.GetFunctionPointerForDelegate(threadFunc);

            RenderDelegate.RegisterThreadFunc(tptr);
            RenderDelegate.SetDebugLogOutFunc(ptr);
            Common.Debug.ShowLogHandle = ShowLog;
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
            renderViewInitSize = renderSize;
            renderViewHandle = handle;

            physicsThread = new System.Threading.Thread(physicsUpdate);
            threadMap[E3DEngine.ThreadInfoDefine.PHYSIC_THREAD_ID] = physicsThread;
            physicsThread.Start();

            threadMap[E3DEngine.ThreadInfoDefine.LOGIC_THREAD_ID] = Thread.CurrentThread;
            if (Config.MutiThreadRender == 1)
            {
                renderThread = new System.Threading.Thread(renderUpdate);
                threadMap[E3DEngine.ThreadInfoDefine.RENDER_THREAD_ID] = renderThread;
                renderThread.Start();
                while (!renderInited)
                {
                    System.Threading.Thread.Sleep(1);
                } // 等待render初始化
                RenderDelegate.CreateShareContext();
            }
            else
            {
                int renderType = Config.RenderSystemType;
                RenderDelegate.SetupRenderSystem(renderType, renderViewHandle, (int)renderViewInitSize.Width, (int)renderViewInitSize.Height);
            }
            RenderDelegate.StartAppliaction();
            EngineLoaded = true;
            mainWnd.objectList.ItemsSource = null;
            if (E3DEngine.SceneManageRef.GetInstance().GetCurScene() == null)
            {
                E3DEngine.SceneManageRef.GetInstance().LoadScene("../Data/Scene/default.scene");
            }
            curScenePath = E3DEngine.SceneManageRef.GetInstance().GetCurScene().GetScenePath();
            loadGameObjectList();
        }

        #endregion

        #region Load Scene
        public void LoadScene(string scenePath)
        {
            string _sceneName = System.IO.Path.GetFileName(scenePath);
            E3DEngine.SceneRef scene = E3DEngine.SceneManageRef.GetInstance().GetCurScene();
            if (scene != null && scene.GetName() == _sceneName)
            {
                return;
            }

            E3DEngine.SceneManageRef.GetInstance().LoadScene(scenePath);
            mainWnd.objectList.ItemsSource = null;
            curScenePath = scenePath;
            loadGameObjectList();
        }

        private void reloadCurSene()
        {
            if (curScenePath == "")
                return;
            mainWnd.Pause.IsChecked = false;
            E3DEngine.SceneManageRef.GetInstance().LoadScene(curScenePath);
            mainWnd.objectList.ItemsSource = null;
            loadGameObjectList();
        }

        private void loadGameObjectList()
        {
            E3DEngine.GameObjectRef gameRootObj = E3DEngine.SceneManageRef.GetInstance().GetCurScene().GetRootObject();
            List<E3DEngine.GameObjectRef> _gameObjectList = gameRootObj.GetChilds();
            gameObjectList = new ObservableCollection<GameObjectNode>();
            GameObjectNode node = new GameObjectNode();
            SceneName = E3DEngine.SceneManageRef.GetInstance().GetCurScene().GetName();
            //node.ShowText = node.Name;
            //node.mGameObject = gameRootObj;
            //gameObjectList.Add(node);
            fillNodeList(_gameObjectList, gameObjectList);

            mainWnd.objectList.ItemsSource = gameObjectList;
            E3DEngine.SceneManageRef.GetInstance().LoadEditorObject();
            if (curScenePath != "")
            {
                WindowTitle = curScenePath;
                if (Config.RenderSystemType == E3DEngine.RenderSystemType.OPENGL)
                {
                    WindowTitle += "<OpenGL>";
                }
                else if (Config.RenderSystemType == E3DEngine.RenderSystemType.OPENGLES)
                {
                    WindowTitle += "<OpenGL ES>";
                }
            }
            mainWnd.properties.SelectedObject = null;
        }

        private void fillNodeList(List<E3DEngine.GameObjectRef> _gameObjectList, ObservableCollection<GameObjectNode> nodeList)
        {
            for (int i = 0; i < _gameObjectList.Count; i++)
            {
                if((_gameObjectList[i].GetFlag() & E3DEngine.GameObjectFlag.HIDE_IN_HIERARCHY) != 0)
                {
                    continue;
                }
                GameObjectNode node = new GameObjectNode();
                node.Name = _gameObjectList[i].GetName();
                node.ShowText = node.Name;
                node.mGameObject = _gameObjectList[i];
                fillNodeList(_gameObjectList[i].GetChilds(), node.Childs);
                nodeList.Add(node);
            }
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

        #endregion

        #region Method

        public void SelectObject(GameObjectNode node)
        {
            mainWnd.SelectItems(node);
            mainWnd.properties.SelectedObject = node;
        }

        public void ShowMainWindow()
        {
            if (mainWnd == null)
            {
                mainWnd = new MainWindow();
            }
            mainWnd.ShowDialog();
        }

        private void pauseGame(bool value)
        {
            if (windowsPlayer == null)
                return;
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

        public void RunCurrentScene(bool isRun)
        {
            if (isRun)
            {
                saveCurrentScene();
            }
            sceneIsStart = isRun;
            RenderDelegate.RunCurrentScene(isRun);
            reloadCurSene();
        }

        private void runGame()
        {
            if (Config.GamePath == "")
                return;
            mainWnd.Pause.IsChecked = false;
            string path = System.Windows.Forms.Application.StartupPath;
            if (windowsPlayer != null)
            {
                mainWnd.renderPanel.SelectedItem = gameItem;
            }
            else
            {
                string cmdLine = Config.GamePath + "," + (new WindowInteropHelper(mainWnd).Handle) + "," + curScenePath;
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
                rp._SizeChange += gamePanel_SizeChange;
                rp.Loaded += gamePanel_Loaded;
                gameItem.Content = rp;
            }

            mainWnd.renderPanel.Items.Add(gameItem);
            mainWnd.renderPanel.SelectedItem = gameItem;

            Win32.SetParent(windowsPlayerHandle, rp.Handle);
            Int32 wndStyle = Win32.GetWindowLong(windowsPlayerHandle, Win32.GWL_STYLE);
            wndStyle &= ~Win32.WS_BORDER;
            wndStyle &= ~Win32.WS_THICKFRAME;
            Win32.SetWindowLong(windowsPlayerHandle, Win32.GWL_STYLE, wndStyle);
            Win32.SetWindowPos(windowsPlayerHandle, IntPtr.Zero, 0, 0, 0, 0, Win32.SWP_NOMOVE | Win32.SWP_NOSIZE | Win32.SWP_NOZORDER | Win32.SWP_FRAMECHANGED);

        }

        private void gamePanel_Loaded(object sender, RoutedEventArgs e)
        {
            RenderPanel rp = gameItem.Content as RenderPanel;
            // 在Resize事件中更新目标应用程序的窗体尺寸. 
            Win32.SetWindowPos(windowsPlayerHandle, IntPtr.Zero, 0, 0, (int)rp.ActualWidth, (int)rp.ActualHeight, Win32.SWP_NOZORDER);
        }

        private void gamePanel_SizeChange(object sender, EventArgs e)
        {
            RenderPanel rp = gameItem.Content as RenderPanel;
            // 在Resize事件中更新目标应用程序的窗体尺寸. 
            Win32.SetWindowPos(windowsPlayerHandle, IntPtr.Zero, 0, 0, (int)rp.ActualWidth, (int)rp.ActualHeight, Win32.SWP_NOZORDER);
        }

        private void GameItem_Closed(object sender, EventArgs e)
        {
            if (windowsPlayer == null)
                return;
            try
            {
                windowsPlayer.Kill();
                windowsPlayer = null;
            }
            catch (Exception ex)
            {
                Common.Debug.Error(ex.ToString());
            }
        }

        private void WindowsPlayer_Exited(object sender, EventArgs e)
        {
            windowsPlayer = null;
        }

        public void RevWindowsPlayerData(COPYDATASTRUCT data)
        {
            switch (data.dwData.ToInt32())
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

        public void ShowLog(string log)
        {
            Dispatcher.Invoke(() =>
            {
                if (log == null)
                    return;
                LogEntiry loge = new LogEntiry();
                if (log.Contains("[error]"))
                {
                    loge.LogStr = log.Replace("[error]", "");
                    loge.LogColor = Brushes.Red;
                    loge.LogIcon = new BitmapImage(new Uri(CONST_STRING.ErrorIcon, UriKind.Relative));
                }
                else if (log.Contains("[warning]"))
                {
                    loge.LogStr = log.Replace("[warning]", "");
                    loge.LogColor = Brushes.Yellow;
                    loge.LogIcon = new BitmapImage(new Uri(CONST_STRING.WarningIcon, UriKind.Relative));
                }
                else
                {
                    loge.LogStr = log;
                    loge.LogColor = Brushes.White;
                    loge.LogIcon = new BitmapImage(new Uri(CONST_STRING.InfoIcon, UriKind.Relative));
                }
                _MainWindow.logList.Items.Add(loge);
                State = loge.LogStr;
                _MainWindow.logList.ScrollIntoView(loge);
            });
            Console.WriteLine(log);
        }

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

        #endregion

        #region Menu Command
        public void MenuItemCommand(string menuName)
        {
            if (menuName == "openSln")
            {
                string filePath = IOFile.OpenSlnFile();
                openSln(filePath);
            }
            else if (menuName == "newSln")
            {
                createProject();
            }
            else if (menuName == "GL4RS" && Config.RenderSystemType != E3DEngine.RenderSystemType.OPENGL)
            {
                Config.WriteConfig(CONST_STRING.Config_renderSystemType, E3DEngine.RenderSystemType.OPENGL.ToString());
                restartApp();
            }
            else if (menuName == "ES2RS" && Config.RenderSystemType != E3DEngine.RenderSystemType.OPENGLES)
            {
                Config.WriteConfig(CONST_STRING.Config_renderSystemType, E3DEngine.RenderSystemType.OPENGLES.ToString());
                restartApp();
            }
        }

        private void restartApp()
        {
            System.Windows.Forms.Application.Restart();
            if (windowsPlayer != null)
            {
                windowsPlayer.Kill();
            }
            Environment.Exit(0);
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
            for (int i = 0; i < menuItems.Length; i++)
            {

            }
        }

        private void openSln(string filePath)
        {
            if (filePath == "")
            {
                return;
            }
            try
            {
                string[] fileContents = System.IO.File.ReadAllLines(filePath);
                for (int i = 0; i < fileContents.Length; i++)
                {
                    if (fileContents[i].Contains("assets"))
                    {
                        Config.GamePath = System.IO.Path.GetDirectoryName(filePath) + "/" + fileContents[i].Split('=')[1] + "/";

                        RenderDelegate.SetAppDataPath(Config.GamePath);
                        RenderDelegate.SetMonoPath("../Data/E3DAssembly", Config.GamePath + "../Library/AssemblyCSharp.dll", Config.GamePath + "../Library/E3DEngine.dll");
                        createRenderPanel();
                        mainWnd.fileView.viewModel.LoadDirectory();
                        // loadEditorMenuItem();
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void createProject()
        {
            Setting set = new Setting();
            set.ShowDialog();
            string project_path = set.ProjectPath;
            string project_name = set.ProjectName;

            if (project_path == "" || project_name == "")
            {
                return;
            }
            bool ret = ZipHelper.UnZip("../Data/project_template", project_path + "/" + project_name);
            if (ret)
            {
                openSln(project_path + "/" + project_name + "/project.esln");
            }
        }

        private void saveCurrentScene()
        {
            if (E3DEngine.SceneManageRef.GetInstance().GetCurScene() == null)
            {
                return;
            }

            if(sceneIsStart)
            {
                return;
            }

            if (curScenePath == "")
            {
                string filePath = IOFile.SaveScene("scene.scene");
                curScenePath = filePath;
            }

            E3DEngine.SceneManageRef.GetInstance().GetCurScene().SaveScene(curScenePath);
        }

        #endregion

        #region ... Command
        public void ExecuteCommand(object sender, ExecutedRoutedEventArgs e)
        {
            if (e.Command == ApplicationCommands.Save)
            {
                saveCurrentScene();
            }
        }

        public void CanExecuteCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            if (e.Command == ApplicationCommands.Save)
            {
                e.CanExecute = true;
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
                        saveCurrentScene();
                        runGame();
                    }
                    break;
                default: break;
            }
        }
        #endregion

        #region Thread

        private void operateThread(int thread_id, int thread_op_type)
        {
            if (threadMap.ContainsKey(thread_id))
            {
                if (thread_op_type == E3DEngine.ThreadInfoDefine.RESUME_THREAD)
                {
                    threadMap[thread_id].Resume();
                }
                else if (thread_op_type == E3DEngine.ThreadInfoDefine.SUSPEND_THREAD)
                {
                    threadMap[thread_id].Suspend();
                }
                else if (thread_id == E3DEngine.ThreadInfoDefine.LOGIC_THREAD_ID)
                {
                    Dispatcher.Invoke(() =>
                    {
                        if (E3DEngine.ThreadInfoDefine.LOCK_THREAD == thread_op_type)
                        {
                            Monitor.Enter(renderLock);
                            Monitor.Enter(physicLock);
                        }
                        else if (E3DEngine.ThreadInfoDefine.LOCK_END == thread_op_type)
                        {
                            Monitor.Exit(renderLock);
                            Monitor.Exit(physicLock);
                        }
                    });
                }

            }
        }

        private void lockThread(int thread_id, int thread_op_type)
        {

        }

        #endregion

        #region Update

        private void renderUpdate()
        {
            int renderType = Config.RenderSystemType;
            RenderDelegate.SetupRenderSystem(renderType, renderViewHandle, (int)renderViewInitSize.Width, (int)renderViewInitSize.Height);
            renderInited = true;
            while(true)
            {
                Thread.Sleep(1);
                RenderDelegate.RenderUpdate();
            }
        }

        private void physicsUpdate()
        {
            while (true)
            {
                Thread.Sleep(1);
                RenderDelegate.UpdatePhysics();
            }
        }
        
        private void engineUpdate(object sender, EventArgs e)
        {
            if (EngineLoaded)
            {
                RenderDelegate.LogicUpdate();
                GameFPS = 0;
                //RenderDelegate.RenderUpdate();
            }
        }


        #endregion
    }
}
