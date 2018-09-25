using E3DEditor.Common;
using E3DEditor.ViewModel;
using E3DEditor.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace E3DEditor.View
{
    /// <summary>
    /// FileView.xaml 的交互逻辑
    /// </summary>
    public partial class FileView : UserControl
    {
        public PropertiesView propertiesView
        {
            get { return (PropertiesView)GetValue(PropertiesViewProperty); }
            set { SetValue(PropertiesViewProperty, value); }
        }

        public static readonly DependencyProperty PropertiesViewProperty = DependencyProperty.Register("propertiesView", typeof(PropertiesView), typeof(FileView));

        public string HeaderText
        {
            get { return (string)GetValue(HeaderTextProperty); }
            set { SetValue(HeaderTextProperty, value); }
        }

        public static readonly DependencyProperty HeaderTextProperty = DependencyProperty.Register("HeaderText", typeof(string), typeof(FileView), new PropertyMetadata(defaultValue:"资源视图", propertyChangedCallback:null, coerceValueCallback:headerTextChangeCallBack));

        private static object headerTextChangeCallBack(DependencyObject d, object baseValue)
        {
            if (baseValue != null)
            {
                FileView view = d as FileView;
                view.header.Header = baseValue;
            }

            return baseValue;
        }

        public VM_FleView viewModel = null;

        public FileView()
        {
            InitializeComponent();
            Loaded += FileView_Loaded;
        }

        private void FileView_Loaded(object sender, RoutedEventArgs e)
        {
            viewModel = new VM_FleView();
            folderTreeView.ItemsSource = viewModel.Directory;
            viewModel._View = this;
        }

        private void fileView_PreviewMouseUp(object sender, MouseButtonEventArgs e)
        {
            ItemNodeBase file = fileView.SelectedItem as ItemNodeBase;
            propertiesView.SelectedObject = file;
        }
      
        private void fileTreeView_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            DirectoryRecord item = folderTreeView.SelectedItem as DirectoryRecord;
            fileView.Items.Clear();
            viewModel.SelectedItemChanged(fileView,item);
        }

        private void MenuItemOpenInFoder_Click(object sender, RoutedEventArgs e)
        {
            if (fileView.SelectedItem == null)
            {
                return;
            }
            ItemNodeBase file = fileView.SelectedItem as ItemNodeBase;
            IOFile.OpenInFolder(Config.GamePath + "\\" + file.FileFullName);
        }

        private void TextBlock_PreviewMouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton != MouseButtonState.Pressed)
            {
                return;
            }
            if (fileView.SelectedItem == null)
            {
                return;
            }
            viewModel.DoDrag(fileView, fileView.SelectedItem as ItemNodeBase);
  
            e.Handled = true;
        }

        private void _FileViewMenuItemNewFile_Click(object sender, RoutedEventArgs e)
        {
            
        }

        public void ShowFileInView(string filePath)
        {
            if (!System.IO.File.Exists(Config.GamePath + "/" + filePath))
            {
                return;
            }
            string fileName = System.IO.Path.GetFileName(filePath);
            filePath = "resources/" + System.IO.Path.GetDirectoryName(filePath);
        }

        private void fileView_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (fileView.SelectedItem == null)
            {
                return;
            }

            ItemNodeBase file = fileView.SelectedItem as ItemNodeBase;
            string ext = System.IO.Path.GetExtension(file.FileFullName);
            if (ext == ".scene")
            {
                App.vm_MainWindow.LoadScene(Config.GamePath + file.FileFullName);
            }
        }
    }
}
