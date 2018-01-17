using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EngineEditor
{
    public partial class EffectEditor : Form
    {
        TCPServer srv = null;
        private List<FileInfo> file_info_list = new List<FileInfo>();
        Dictionary<string, int> particleList = new Dictionary<string, int>();
        Dictionary<string, ParticleEditor> particleEditors = new Dictionary<string, ParticleEditor>();

        LogOutPutFunc logPrint = null;
        SceneList sceneList = null;
        LogWindow logWindow = null;
        bool isLoaded = false;
        int m_fps = 0;
        public EffectEditor()
        {
            InitializeComponent();
            logWindow = new LogWindow();
            this.Load += EffectEditor_Load;
            // 初始化 TCP
            srv = new TCPServer();
            srv.LogOutputEvent = new LogOutput((string log) =>
            {
                logWindow.ShowLog(log);
            });
            srv.FrameSpeedChange = new FPSChange((int fps)=>
            {
                m_fps = fps;
            });
            srv.StartServer();
            this.IsMdiContainer = true;//设置父窗体是容器
            logWindow.MdiParent = this;
            logWindow.Parent = this.lodPanel;
            logWindow.FormBorderStyle = FormBorderStyle.None;
            logWindow.Dock = DockStyle.Fill;
            logWindow.Show();
        }

        void EffectEditor_Load(object sender, EventArgs e)
        {
            EngineDLL.SetAppDataPath(Application.StartupPath);
            EngineDLL.InitilizeEngine();
            EngineDLL.SetupRenderSystem(sceneContener.Handle, sceneContener.Width, sceneContener.Height);
            EngineDLL.StartAppliaction();
            EngineDLL.CreateEditorGrid();
            isLoaded = true;
        }

        private void EffectEditor_FormClosed(object sender, FormClosedEventArgs e)
        {
            EngineDLL.StopAppliaction();
            RenderContent.Close();
            srv.ShutDown();
            System.Environment.Exit(0);
        }

        const int WM_SYSCOMMAND = 0x112;
        const int SC_CLOSE = 0xF060;
        const int SC_MINIMIZE = 0xF020;
        const int SC_MAXIMIZE = 0xF030;
        protected override void WndProc(ref Message m)
        {
            if (m.Msg == WM_SYSCOMMAND)
            {
                if (m.WParam.ToInt32() == SC_MINIMIZE)
                {
                    this.WindowState = FormWindowState.Minimized;
                    if (sceneList != null)
                    {
                        sceneList.WindowState = FormWindowState.Minimized;
                    }
                }
            }
            base.WndProc(ref m);
        }

        private void EffectEditor_Activated(object sender, EventArgs e)
        {
            if (sceneList == null)
            {
                return;
            }
            if (WindowState == FormWindowState.Minimized)
            {
                if (sceneList.WindowState == FormWindowState.Minimized)
                {
                    sceneList.WindowState = FormWindowState.Normal;
                }
            }
        }

        private void 日志ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            logWindow.Show();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (!isLoaded)
            {
                return;
            }
            EngineDLL.EngineUpdate();
            frameSpeed.Text = m_fps.ToString();
            srv.Tick(0.2f);
        }

        private void EngineContener_MouseDown(object sender, MouseEventArgs e)
        {
            if (!isLoaded)
            {
                return;
            }
            if (e.Button == MouseButtons.Left)
            {
                EngineDLL.MouseDown((int)EngineDLL.MouseButton.eLeftButton, e.X, e.Y);
            }
            else if (e.Button == MouseButtons.Right)
            {
                EngineDLL.MouseDown((int)EngineDLL.MouseButton.eRightButton, e.X, e.Y);
            }
            else if (e.Button == MouseButtons.Middle)
            {
                EngineDLL.MouseDown((int)EngineDLL.MouseButton.eMiddleButton, e.X, e.Y);
            }
        }

        private void EngineContener_MouseUp(object sender, MouseEventArgs e)
        {
            if (!isLoaded)
            {
                return;
            }
            if (e.Button == MouseButtons.Left)
            {
                EngineDLL.MouseUp((int)EngineDLL.MouseButton.eLeftButton, e.X, e.Y);
            }
            else if (e.Button == MouseButtons.Right)
            {
                EngineDLL.MouseUp((int)EngineDLL.MouseButton.eRightButton, e.X, e.Y);
            }
            else if (e.Button == MouseButtons.Middle)
            {
                EngineDLL.MouseUp((int)EngineDLL.MouseButton.eMiddleButton, e.X, e.Y);
            }
        }

        private void EngineContener_MouseMove(object sender, MouseEventArgs e)
        {
            if (!isLoaded)
            {
                return;
            }
            EngineDLL.MouseMove(e.X, e.Y);
        }

        private void EffectEditor_SizeChanged(object sender, EventArgs e)
        {
            if (!isLoaded)
            {
                return;
            }
            EngineDLL.ChageFrameSize(sceneContener.Width, sceneContener.Height);
        }

        private void pauseButton_Click(object sender, EventArgs e)
        {
            pauseButton.Checked = !pauseButton.Checked;
            if (pauseButton.Checked)
            {
               
            }
            else
            {
                //EngineDLL.StopAppliaction();
            }
        }

        private void EffectEditor_Load_1(object sender, EventArgs e)
        {

        }

        private void EffectEditor_KeyDown(object sender, KeyEventArgs e)
        {
            if (!isLoaded)
            {
                return;
            }
            EngineDLL.KeyDown((char)e.KeyValue);
        }

        private void EffectEditor_KeyUp(object sender, KeyEventArgs e)
        {
            if (!isLoaded)
            {
                return;
            }
            EngineDLL.KeyUp((char)e.KeyValue);
        }
    }
}
