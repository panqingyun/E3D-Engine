﻿using E3DEditor.Common;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Interop;
using System.Runtime.InteropServices;
using System.Windows.Controls.Primitives;

namespace E3DEditor.View
{
    /// <summary>
    /// Window1.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool isInRun = false;
        public MainWindow()
        {
            InitializeComponent();
            DataContext = App.vm_MainWindow;
            CommandBindings.Add(new CommandBinding(ApplicationCommands.Save, App.vm_MainWindow.ExecuteCommand, App.vm_MainWindow.CanExecuteCommand));
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
            if (sender == emptyLog)
            {
                logList.Items.Clear();
            }
            else
            {
                App.vm_MainWindow.MenuItemCommand((sender as MenuItem).Name);
            }
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

        private void RunScene_Click(object sender, RoutedEventArgs e)
        {
            if (isInRun)
            {
                runScene.Visibility = Visibility.Visible;
                stopRunScene.Visibility = Visibility.Hidden;
            }
            else
            {
                stopRunScene.Visibility = Visibility.Visible;
                runScene.Visibility = Visibility.Hidden;
            }

            isInRun = !isInRun;
            App.vm_MainWindow.RunCurrentScene(isInRun);
        }
    }
}