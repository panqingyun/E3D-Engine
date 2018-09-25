using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace E3DEditor.View
{
    public enum eMouseButton
    {
        eLeftButton = 0,
		eRightButton,
		eMiddleButton,
		eUnKnown
    };

    public delegate void RenderHandler(IntPtr hwnd, Size renderSize);
    /// <summary>
    /// RenderPanel.xaml 的交互逻辑
    /// </summary>
    public partial class RenderPanel : UserControl
    {
        System.Windows.Forms.Timer myTimer = new System.Windows.Forms.Timer();

        public event RenderHandler RenderLoaded;

        public RenderPanel()
        {
            InitializeComponent();
            editorContent.SizeChanged += EditorContent_SizeChanged;
            Loaded += RenderPanel_Loaded;
        }

        private void RenderPanel_Loaded(object sender, RoutedEventArgs e)
        {
            try
            {
                RenderLoaded?.Invoke(editorContent.Handle, new Size(ActualWidth, ActualHeight));
            }
            catch(Exception ex)
            {
                int i = 0;
            }
            myTimer.Tick += new EventHandler(update);
            myTimer.Enabled = true;
            myTimer.Interval = 10;
            myTimer.Start();
        }
        
        private void update(object sender, EventArgs e)
        {
            if (App.vm_MainWindow.EngineLoaded)
            {
                App.vm_MainWindow.RenderDelegate.EngineUpdate();
            }
        }

        private void EditorContent_SizeChanged(object sender, EventArgs e)
        {
            if (!App.vm_MainWindow.EngineLoaded)
            {
                return;
            }
            App.vm_MainWindow.RenderDelegate.ChageFrameSize((int)ActualWidth, (int)ActualHeight);
        }

        private void editorContent_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (!App.vm_MainWindow.EngineLoaded)
            {
                return;
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                App.vm_MainWindow.RenderDelegate.MouseDown((int) eMouseButton.eLeftButton, e.Location.X, e.Location.Y);
            }
            else if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                App.vm_MainWindow.RenderDelegate.MouseDown((int)eMouseButton.eRightButton, e.Location.X, e.Location.Y);
            }
            else if (e.Button == System.Windows.Forms.MouseButtons.Middle)
            {
                App.vm_MainWindow.RenderDelegate.MouseDown((int)eMouseButton.eMiddleButton, e.Location.X, e.Location.Y);
            }
        }

        private void editorContent_PreviewKeyDown(object sender, System.Windows.Forms.PreviewKeyDownEventArgs e)
        {
           
        }

        private void editorContent_KeyUp(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            if (!App.vm_MainWindow.EngineLoaded)
            {
                return;
            }
            char key = (char)e.KeyValue;
            App.vm_MainWindow.RenderDelegate.KeyUp((sbyte)key);
        }

        private void editorContent_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (!App.vm_MainWindow.EngineLoaded)
            {
                return;
            }
            App.vm_MainWindow.RenderDelegate.MouseMove(e.Location.X, e.Location.Y);
        }

        private void editorContent_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (!App.vm_MainWindow.EngineLoaded)
            {
                return;
            }
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                App.vm_MainWindow.RenderDelegate.MouseUp((int)eMouseButton.eLeftButton, e.Location.X, e.Location.Y);
            }
            else if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                App.vm_MainWindow.RenderDelegate.MouseUp((int)eMouseButton.eRightButton, e.Location.X, e.Location.Y);
            }
            else if (e.Button == System.Windows.Forms.MouseButtons.Middle)
            {
                App.vm_MainWindow.RenderDelegate.MouseUp((int)eMouseButton.eMiddleButton, e.Location.X, e.Location.Y);
            }
        }

        private void editorContent_MouseWheel(object sender, System.Windows.Forms.MouseEventArgs e)
        {

        }

        private void Grid_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (!App.vm_MainWindow.EngineLoaded)
            {
                return;
            }

            string k = e.Key.ToString();
            App.vm_MainWindow.RenderDelegate.KeyDown((sbyte)k[0]);
        }

        private void Grid_PreviewKeyUp(object sender, KeyEventArgs e)
        {

            if (!App.vm_MainWindow.EngineLoaded)
            {
                return;
            }

            string k = e.Key.ToString();
            App.vm_MainWindow.RenderDelegate.KeyUp((sbyte)k[0]);
        }
    }
}
