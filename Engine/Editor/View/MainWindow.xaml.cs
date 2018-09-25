using E3DEditor.Common;
using E3DEditor.ViewModel;
using E3DEditor.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Interop;
using System.Text;
using System.Runtime.InteropServices;

namespace E3DEditor.View
{
    /// <summary>
    /// Window1.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            App.vm_MainWindow._MainWindow = this;
            prograss.SetBinding(ProgressBar.ValueProperty, new Binding("PrograssBarValue") { Source = App.vm_MainWindow });
            state.SetBinding(Label.ContentProperty, new Binding("State") { Source = App.vm_MainWindow });
           
            Min.SetBinding(Button.CommandProperty, new Binding("MainTitleButtonCommand") { Source = App.vm_MainWindow });
            Close.SetBinding(Button.CommandProperty, new Binding("MainTitleButtonCommand") { Source = App.vm_MainWindow });
            Run.SetBinding(Button.CommandProperty, new Binding("MainTitleButtonCommand") { Source = App.vm_MainWindow });
            _MenuItemNew.SetBinding(Button.CommandProperty, new Binding("MainMenuNewButtonCommand") { Source = App.vm_MainWindow });
            _MenuItemDel.SetBinding(Button.CommandProperty, new Binding("MainMenuDeleteButtonCommand") { Source = App.vm_MainWindow });
            
        }

        private void objectList_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (objectList.SelectedItem == null)
            {
                return;
            }
            properties.SelectedObject = objectList.SelectedItem;
        }

        private void menu_Click(object sender, RoutedEventArgs e)
        {
            App.vm_MainWindow.MenuItemCommand((sender as MenuItem).Name);
        }

        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);
            HwndSource source = PresentationSource.FromVisual(this) as HwndSource;
            source.AddHook(WndProc);
        }

        private IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            try
            {
                switch (msg)
                {
                    case Win32.WM_COPYDATA:
                        {
                            COPYDATASTRUCT data = (COPYDATASTRUCT)Marshal.PtrToStructure(lParam, typeof(COPYDATASTRUCT));
                            App.vm_MainWindow.RevWindowsPlayerData(data);
                        }
                        break;
                }
            }
            catch (Exception ex)
            {
                App.vm_MainWindow.ShowLog(ex.Message);
            }
            return IntPtr.Zero;
        }
        
        private void Pause_Checked(object sender, RoutedEventArgs e)
        {
            App.vm_MainWindow.PauseEngine = (bool)Pause.IsChecked;
        }
    }
}
