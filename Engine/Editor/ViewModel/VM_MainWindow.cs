using E3DEditor.Model;
using E3DEditor.View;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls;
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

        public VM_MainWindow()
        {
            try
            {
                RenderDelegate = new E3DEngine.EngineDelegateRef();
                RenderDelegate.SetAppDataPath(Config.GamePath);
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
                createRenderPanel();
            }
        }

        private void createRenderPanel()
        {
            TabItemWithClose item = new TabItemWithClose();
            item.Width = 150;
            item.Height = 20;
            item.FontSize = 13;
            item.Header = "编辑器";
            item.HorizontalAlignment = HorizontalAlignment.Stretch;
            item.VerticalAlignment = VerticalAlignment.Stretch;
            RenderPanel rp = new RenderPanel();
            rp.RenderLoaded += Rp_Loaded;
            item.Content = rp;
            mainWnd.renderPanel.Items.Add(item);
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
            E3DEngine.TransformRef trans = gameRootObj.GetTransform();
            node.Position = trans.Position;
            node.Scale = trans.Scale;
            node.Rotation = trans.Rotation;
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
            get
            {
                return (bool)GetValue(PauseEngineProperty);
            }
            set
            {
                SetValue(PauseEngineProperty, value);
            }
        }

        public static readonly DependencyProperty PauseEngineProperty = DependencyProperty.Register("PauseEngine", typeof(bool), typeof(RenderPanel),
            new PropertyMetadata(false, null, coerceValueCallback: pauseCallBcal));

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

        private static object pauseCallBcal(DependencyObject d, object baseValue)
        {
            //if (baseValue != null)
            //{
            //    RenderPanel view = d as RenderPanel;
            //    if (!view.engineLoaded)
            //    {
            //        return baseValue;
            //    }
            //    renderDelegate.PauseEngine((bool)baseValue);
            //}

            return baseValue;
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
            string path = System.Windows.Forms.Application.StartupPath;
            switch (pageName)
            {
                case "Close":
                    {
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
                        Process.Start(path + "/../WindowsPlayer/Client.exe");
                    }
                    break;
                default:break;
            }
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

        private static void fillNodeList(List<E3DEngine.GameObjectRef> _gameObjectList,ObservableCollection<GameObjectNode> nodeList)
        {
            for (int i = 0; i < _gameObjectList.Count; i++)
            {
                GameObjectNode node = new GameObjectNode();
                node.Name = _gameObjectList[i].GetName();
                node.ShowText = node.Name;
                E3DEngine.TransformRef trans = _gameObjectList[i].GetTransform();
                node.Position = trans.Position;
                node.Scale = trans.Scale;
                node.Rotation = trans.Rotation;
                fillNodeList(_gameObjectList[i].GetChilds(), node.Childs);
                nodeList.Add(node);
            }
        }
    }
}
