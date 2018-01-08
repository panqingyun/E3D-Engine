using AsyncSocketServer;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EngineEditor
{
    public partial class LogWindow : Form
    {
        public LogWindow()
        {
            InitializeComponent();
        }

        private bool bPause = false;
        private static object lockObj = new object();
        private List<string> LogText1 = new List<string>();
        private List<string> LogText2 = new List<string>();
        private int currentReadLog = 1;
        private string allLogText = "";

        public void ShowLog(string log)
        {
            allLogText += log + "\n";
            lock (lockObj)
            {
                if (currentReadLog == 1)
                {
                    LogText2.Add(log);
                }
                else
                {
                    LogText1.Add(log);
                }
            }
        }

        private void richTextBox1_MouseClick(object sender, MouseEventArgs e)
        {
           
        }

        private void 清理ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            logRichTextBox.Text = "";
            allLogText = "";
        }

        private void 暂停ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bPause = !bPause;
            timer1.Enabled = !bPause;
            if (bPause)
            {
                暂停ToolStripMenuItem.Text = "继续";
            }
            else
            {
                暂停ToolStripMenuItem.Text = "暂停";
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (bPause)
            {
                return;
            }
            lock(lockObj)
            {
                if (currentReadLog == 1)
                {
                    for (int i = 0; i < LogText1.Count; i++ )
                    {
                        appendLog(LogText1[i]);
                    }
                    LogText1.Clear();
                    currentReadLog = 2;
                }
                else
                {
                    for (int i = 0; i < LogText2.Count; i++)
                    {
                        appendLog(LogText2[i]);
                    }
                    LogText2.Clear();
                    currentReadLog = 1;
                }
            }
        }

        private void appendLog(string log)
        {
            if (log.Contains("error"))
            {
                logRichTextBox.SelectionColor = Color.Red;
                logRichTextBox.SelectionFont = new System.Drawing.Font("微软雅黑", 14, FontStyle.Bold);
                Debug.Error(log);
            }
            else if (log.Contains("warning"))
            {
                logRichTextBox.SelectionColor = Color.Yellow;
                logRichTextBox.SelectionFont = new System.Drawing.Font("微软雅黑", 13, FontStyle.Italic);
                Debug.Warning(log);
            }
            else if (log.Contains("debug"))
            {
                logRichTextBox.SelectionColor = Color.Green;
                logRichTextBox.SelectionFont = new System.Drawing.Font("微软雅黑", 12, FontStyle.Underline);
                Debug.LogDebug(log);
            }
            else
            {
                logRichTextBox.SelectionColor = Color.White;
                logRichTextBox.SelectionFont = new System.Drawing.Font("微软雅黑", 11, FontStyle.Regular);
                Debug.Log(log);
            }
            logRichTextBox.AppendText("["+ DateTime.Now.ToString() +"]" + "\t" + log + "\r\n");
        }

        private void logRichTextBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                clearMenu.Show(this, e.Location);
            }
        }

        private void LogWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }
    }
}
