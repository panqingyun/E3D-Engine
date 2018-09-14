using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace E3DEditor.View
{
    public delegate void OpenFileOrFolderCallBackDelegate(object sender, string path);
    /// <summary>
    /// OpenFileTextbox.xaml 的交互逻辑
    /// </summary>
    public partial class OpenFileTextBox : System.Windows.Controls.UserControl
    {
        public string Text
        {
            get { return path.Text; }
            set { path.Text = value; }
        }

        public bool IsOpenFolder
        {
            get { return (bool)GetValue(IsOpenFolderProperty); }
            set { SetValue(IsOpenFolderProperty,value); }
        }
        public static readonly DependencyProperty IsOpenFolderProperty = DependencyProperty.Register("IsOpenFolder", typeof(bool), typeof(OpenFileTextBox));

        public string FileExtention
        {
            get { return (string)GetValue(FileExtentionProperty); }
            set { SetValue(FileExtentionProperty, value); }
        }

        public static readonly DependencyProperty FileExtentionProperty = DependencyProperty.Register("FileExtention", typeof(string), typeof(OpenFileTextBox));

        public OpenFileOrFolderCallBackDelegate OpenCallBack;

        public OpenFileTextBox()
        {
            InitializeComponent();
        }

        private void tabSrcBtn_Click(object sender, RoutedEventArgs e)
        {
            string path = "";
            if (IsOpenFolder)
            {
                FolderBrowserDialog m_Dialog = new FolderBrowserDialog();
                DialogResult result = m_Dialog.ShowDialog();

                if (result == System.Windows.Forms.DialogResult.OK)
                {
                    path = m_Dialog.SelectedPath.Trim();
                    Text = path;
                }
            }
            else
            {
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.Filter = FileExtention;
                ofd.ValidateNames = true;
                ofd.CheckPathExists = true;
                ofd.CheckFileExists = true;
                if (ofd.ShowDialog() == DialogResult.OK)
                {
                    path = ofd.FileName;
                    Text = path;
                }
            }

            OpenCallBack?.Invoke(this, path);
        }
    }
}
