using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Forms;

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
    public partial class RenderPanel : System.Windows.Controls.UserControl
    {
        System.Windows.Forms.Timer myTimer = new System.Windows.Forms.Timer();
        public event MouseEventHandler _MouseButtonDown;
        public event MouseEventHandler _MouseButtonUp;
        public event MouseEventHandler _MouseMove;
        public event System.Windows.Input.KeyEventHandler _KeyDown;
        public event System.Windows.Input.KeyEventHandler _KeyUp;
        public event EventHandler _SizeChange;
        public bool NeedUpdate = true;
        public IntPtr Handle
        {
            get
            {
                return editorContent.Handle;
            }
        }


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
                App.vm_MainWindow.ShowLog(ex.ToString());
            }
            if (NeedUpdate)
            {
                myTimer.Tick += new EventHandler(update);
                myTimer.Enabled = true;
                myTimer.Interval = 10;
                myTimer.Start();
            }
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
            _SizeChange?.Invoke(this, e);
        }

        private void editorContent_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            _MouseButtonDown?.Invoke(this, e);
        }
        

        private void editorContent_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            _MouseMove?.Invoke(this, e);
        }

        private void editorContent_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            _MouseButtonUp?.Invoke(this, e);
        }

        private void editorContent_MouseWheel(object sender, System.Windows.Forms.MouseEventArgs e)
        {

        }

        private void Grid_PreviewKeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            _KeyDown?.Invoke(this, e);
        }

        private void Grid_PreviewKeyUp(object sender, System.Windows.Input.KeyEventArgs e)
        {
            _KeyUp?.Invoke(this, e);
        }
    }
}
