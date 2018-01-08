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
    public partial class SceneList : Form
    {
        public TCPServer Srv = null;
        public event EventHandler ChangeSceneEvent;
        public bool isShow = false;
        public SceneList()
        {
            InitializeComponent();
            treeViewScene.Nodes.Clear();
            TreeNode node = treeViewScene.Nodes.Add("SceneRoot");
            for (int i = 0; i < 5; i++)
            {
                node.Nodes.Add(i.ToString(), "场景" + i);
            }

            this.Load += SceneList_Load;
            this.FormClosed += SceneList_FormClosed;
            this.FormClosing += SceneList_FormClosing;
        }

        void SceneList_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }

        void SceneList_FormClosed(object sender, FormClosedEventArgs e)
        {
            isShow = false;
        }

        void SceneList_Load(object sender, EventArgs e)
        {
            isShow = true;
        }
        NetCommand cmd = new NetCommand();
        private int currentScene = 0;
        private void treeViewScene_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (e.Node.Name == "")
            {
                return;
            }
            if (currentScene == Convert.ToInt32(e.Node.Name))
            {
                return;
            }
            currentScene = Convert.ToInt32(e.Node.Name);
            if (ChangeSceneEvent != null)
            {
                ChangeSceneEvent(null, null);
            }
            cmd.ID = (int)NetCommandEnum.ChangeScenes;
            cmd.Content = e.Node.Name;
            foreach (EditorClient client in Srv.Clients)
            {
                client.SendMsg(cmd);
            }
        }
    }
}
