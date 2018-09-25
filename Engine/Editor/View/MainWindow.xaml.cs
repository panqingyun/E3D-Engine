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
    }
}
