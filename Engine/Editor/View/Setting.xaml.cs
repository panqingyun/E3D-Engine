using E3DEditor.Common;
using E3DEditor.Model;
using System;
using System.Windows;
using System.Windows.Controls;

namespace E3DEditor.View
{
    /// <summary>
    /// Setting.xaml 的交互逻辑
    /// </summary>
    public partial class Setting : Window
    {
        public Setting()
        {
            InitializeComponent();
            Loaded += Setting_Loaded;
        }

        public string ProjectPath = "";
        public string ProjectName = "";

        private void Setting_Loaded(object sender, RoutedEventArgs e)
        {
            resPath.Text = Config.GamePath;
        }

        private void sure_Click(object sender, RoutedEventArgs e)
        {
            ProjectPath = resPath.Text;
            ProjectName = projName.Text;
            Close();
        }
        
    }
}
