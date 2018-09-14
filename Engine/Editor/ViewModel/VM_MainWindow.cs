using E3DEditor.Common;
using E3DEditor.Model;
using E3DEditor.View;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;

namespace E3DEditor.ViewModel
{
    public class VM_MainWindow : DependencyObject, INotifyPropertyChanged
    {
        public MainWindow _MainWindow { get; set; }

        private Dictionary<int, TabItemWithClose> editorItemMap = new Dictionary<int, TabItemWithClose>();

        public ObservableCollection<NodeBase> SegmentList
        {
            get
            {
                return (ObservableCollection<NodeBase>)GetValue(SegmentListProperty);
            }
            set
            {
                SetValue(SegmentListProperty, value);
            }
        }

        public static readonly DependencyProperty SegmentListProperty = DependencyProperty.Register("SegmentList", typeof(ObservableCollection<NodeBase>), typeof(VM_MainWindow));

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
                case "OpenBtn":
                    {
                        IOFile.OpenFile();
                    }
                    break;
                case "SaveBtn":
                    {
                        App.Instance.SaveFile();
                    }
                    break;
                case "SetBtn":
                    {
                        App.Instance.Setting();
                    }
                    break;
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
                default:break;
            }
        }

        public PropertiesView PropertyView
        {
            get { return _MainWindow.properties; }
        }

        public TabControl EditorPanel
        {
            get { return _MainWindow.EditorPanel; }
        }

        public VM_MainWindow()
        {
            try
            {
               
            }
            catch
            {
                App.Instance.Setting();
            }
        }

        
        private void item_Closed(object sender, EventArgs e)
        {
           
        }
        
    }
}
