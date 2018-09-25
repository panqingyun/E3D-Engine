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

        private void Setting_Loaded(object sender, RoutedEventArgs e)
        {
            resPath.Text = Config.GamePath;
            width.Text = Config.GameWidth.ToString();
            height.Text = Config.GameHeight.ToString();
        }

        private void sure_Click(object sender, RoutedEventArgs e)
        {
            Config.WriteConfig(CONST_STRING.Config_resourceFilePath, resPath.Text);
            Config.WriteConfig(CONST_STRING.Config_gameHeight, height.Text);
            Config.WriteConfig(CONST_STRING.Config_gameWidht, width.Text);
            Config.SaveConfig();
            Close();
        }
        
    }
}
