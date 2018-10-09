using System;
using System.Collections.Generic;
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
using System.Windows.Shapes;

namespace E3DEditor.View
{
    /// <summary>
    /// Load.xaml 的交互逻辑
    /// </summary>
    public partial class Load : Window
    {
        System.Windows.Forms.Timer myTimer = new System.Windows.Forms.Timer();
        public Load()
        {
            InitializeComponent();
            Loaded += Load_Loaded;
        }

        private void Load_Loaded(object sender, RoutedEventArgs e)
        {
            myTimer.Tick += new EventHandler(tick);
            myTimer.Enabled = true;
            myTimer.Interval = 1000 * 3;
            myTimer.Start();
        }

        private void tick(object sender, EventArgs e)
        {
            myTimer.Stop();
            Visibility = Visibility.Hidden;
            App.vm_MainWindow.ShowMainWindow();
        }
    }
}
