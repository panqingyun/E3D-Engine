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
    public partial class ParticleEditor : Form
    {
        public ParticleEditor()
        {
            InitializeComponent();
            this.Load += ParticleEditor_Load;
        }

        TreeNode selectNodes = null;
        TreeNode rootNodes = null;

        void ParticleEditor_Load(object sender, EventArgs e)
        {
            rootNodes = normalProperty.Nodes.Add("ParticleConfig");
            selectNodes = rootNodes;
        }

        private void normalProperty_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                createMenu.Show(this, e.Location);
            }
        }

        private void iDToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void c类ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 影响器ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 发射器ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 材质ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 文理UVToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void shaderIndexToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void normalProperty_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (e.Node.Text == "ConfigItem")
            {
                selectNodes = e.Node;
            }
            
        }

        private void 添加粒子团ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            selectNodes = selectNodes.Nodes.Add("ConfigItem");
        }
    }
}
