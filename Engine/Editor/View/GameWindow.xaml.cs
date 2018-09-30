using System.Windows;

namespace E3DEditor.View
{
    /// <summary>
    /// GameWindow.xaml 的交互逻辑
    /// </summary>
    public partial class GameWindow : Window
    {
        private bool isInShow = false;
        public GameWindow()
        {
            InitializeComponent();
            Loaded += GameWindow_Loaded;
            Closing += GameWindow_Closing;
        }

        private void GameWindow_Loaded(object sender, RoutedEventArgs e)
        {
            isInShow = true;
        }

        private void GameWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            ShowWindow(false);
            e.Cancel = true;
        }

        public void ShowWindow(bool isShow)
        {
            if(isShow)
            {
                if (!isInShow)
                {
                    Show();
                }
                Visibility = Visibility.Visible;
            }
            else
            {
                Visibility = Visibility.Hidden;
            }
        }
    }
}
