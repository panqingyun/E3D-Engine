using E3DEditor.Common;
using E3DEditor.ViewModel;
using E3DEditor.View;
using System.Windows;
using System.ComponentModel;

namespace E3DEditor
{
    /// <summary>
    /// App.xaml 的交互逻辑
    /// App 入口
    /// </summary>
    public partial class App : Application , INotifyPropertyChanged
    {
        public App()
        {
            _Instance = this;
            InitEnv();
            vm_MainWindow = new VM_MainWindow();
        }

        public string this[string index]
        {
            get
            {
                if (Resources.Contains(index))
                {
                    return Resources[index].ToString();
                }
                return index;
            }
        }

        private static VM_MainWindow _mainWindowViewModel = null;
        public static VM_MainWindow vm_MainWindow
        {
            get
            {
                return _mainWindowViewModel;
            }
            private set
            {
                _mainWindowViewModel = value;
                Instance.OnPropertyChanged("vm_MainWindow");
            }
        }

        private static App _Instance;

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        public static App Instance
        {
            get
            {
                return _Instance;
            }
        }
        
        
        public IOFile ioFile
        {
            get;private set;
        }
        
        public void SaveFile()
        {
            ShowState(this["SaveDone"]);
            MessageBox.Show(this["SaveDone"], this["Info"], MessageBoxButton.OK, MessageBoxImage.Information);
        }
        
        public void InitEnv()
        {
            Config.Init();
            ioFile = new IOFile();
            if (Config.GamePath == "")
            {
              //  Setting();
            }
        }

        public void Log(LogLevel level, string logFormat, params string[] param)
        {
            string log = string.Format(logFormat, param);

        }

        public void ShowPropertyInMainWindow(object obj)
        {
            vm_MainWindow.PropertyView.SelectedObject = obj;
        }

        public void ShowPrograss(double prograss)
        {
            Current.Dispatcher.Invoke(() =>
            {
                vm_MainWindow.PrograssBarValue = prograss;
            });
        }
        
        public void ShowState(string state)
        {
            Application.Current.Dispatcher.Invoke(() =>
            {
                vm_MainWindow.State = state;
            });
        }
        
    }
}
