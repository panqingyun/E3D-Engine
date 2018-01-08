namespace EngineEditor
{
    partial class ParticleEditor
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.normalProperty = new System.Windows.Forms.TreeView();
            this.label1 = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.createMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.新建ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.iDToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.c类ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.影响器ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.发射器ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.材质ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.文理UVToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.shaderIndexToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.添加粒子团ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.createMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.BackColor = System.Drawing.Color.White;
            this.splitContainer1.Panel1.Controls.Add(this.normalProperty);
            this.splitContainer1.Panel1.Controls.Add(this.label1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.panel2);
            this.splitContainer1.Size = new System.Drawing.Size(404, 1092);
            this.splitContainer1.SplitterDistance = 496;
            this.splitContainer1.TabIndex = 0;
            // 
            // normalProperty
            // 
            this.normalProperty.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.normalProperty.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.normalProperty.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.normalProperty.Location = new System.Drawing.Point(0, 33);
            this.normalProperty.Name = "normalProperty";
            this.normalProperty.Size = new System.Drawing.Size(404, 461);
            this.normalProperty.TabIndex = 2;
            this.normalProperty.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.normalProperty_NodeMouseClick);
            this.normalProperty.MouseUp += new System.Windows.Forms.MouseEventHandler(this.normalProperty_MouseUp);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(12, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(42, 22);
            this.label1.TabIndex = 1;
            this.label1.Text = "属性";
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(404, 592);
            this.panel2.TabIndex = 0;
            // 
            // createMenu
            // 
            this.createMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.新建ToolStripMenuItem,
            this.添加粒子团ToolStripMenuItem});
            this.createMenu.Name = "createMenu";
            this.createMenu.Size = new System.Drawing.Size(137, 48);
            // 
            // 新建ToolStripMenuItem
            // 
            this.新建ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.iDToolStripMenuItem,
            this.c类ToolStripMenuItem,
            this.影响器ToolStripMenuItem,
            this.发射器ToolStripMenuItem,
            this.材质ToolStripMenuItem,
            this.文理UVToolStripMenuItem,
            this.shaderIndexToolStripMenuItem});
            this.新建ToolStripMenuItem.Name = "新建ToolStripMenuItem";
            this.新建ToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.新建ToolStripMenuItem.Text = "新建";
            // 
            // iDToolStripMenuItem
            // 
            this.iDToolStripMenuItem.Name = "iDToolStripMenuItem";
            this.iDToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.iDToolStripMenuItem.Text = "ID";
            this.iDToolStripMenuItem.Click += new System.EventHandler(this.iDToolStripMenuItem_Click);
            // 
            // c类ToolStripMenuItem
            // 
            this.c类ToolStripMenuItem.Name = "c类ToolStripMenuItem";
            this.c类ToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.c类ToolStripMenuItem.Text = "C++类";
            this.c类ToolStripMenuItem.Click += new System.EventHandler(this.c类ToolStripMenuItem_Click);
            // 
            // 影响器ToolStripMenuItem
            // 
            this.影响器ToolStripMenuItem.Name = "影响器ToolStripMenuItem";
            this.影响器ToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.影响器ToolStripMenuItem.Text = "影响器";
            this.影响器ToolStripMenuItem.Click += new System.EventHandler(this.影响器ToolStripMenuItem_Click);
            // 
            // 发射器ToolStripMenuItem
            // 
            this.发射器ToolStripMenuItem.Name = "发射器ToolStripMenuItem";
            this.发射器ToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.发射器ToolStripMenuItem.Text = "发射器";
            this.发射器ToolStripMenuItem.Click += new System.EventHandler(this.发射器ToolStripMenuItem_Click);
            // 
            // 材质ToolStripMenuItem
            // 
            this.材质ToolStripMenuItem.Name = "材质ToolStripMenuItem";
            this.材质ToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.材质ToolStripMenuItem.Text = "材质";
            this.材质ToolStripMenuItem.Click += new System.EventHandler(this.材质ToolStripMenuItem_Click);
            // 
            // 文理UVToolStripMenuItem
            // 
            this.文理UVToolStripMenuItem.Name = "文理UVToolStripMenuItem";
            this.文理UVToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.文理UVToolStripMenuItem.Text = "文理UV";
            this.文理UVToolStripMenuItem.Click += new System.EventHandler(this.文理UVToolStripMenuItem_Click);
            // 
            // shaderIndexToolStripMenuItem
            // 
            this.shaderIndexToolStripMenuItem.Name = "shaderIndexToolStripMenuItem";
            this.shaderIndexToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.shaderIndexToolStripMenuItem.Text = "ShaderIndex";
            this.shaderIndexToolStripMenuItem.Click += new System.EventHandler(this.shaderIndexToolStripMenuItem_Click);
            // 
            // 添加粒子团ToolStripMenuItem
            // 
            this.添加粒子团ToolStripMenuItem.Name = "添加粒子团ToolStripMenuItem";
            this.添加粒子团ToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.添加粒子团ToolStripMenuItem.Text = "添加粒子团";
            this.添加粒子团ToolStripMenuItem.Click += new System.EventHandler(this.添加粒子团ToolStripMenuItem_Click);
            // 
            // ParticleEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(404, 1092);
            this.Controls.Add(this.splitContainer1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "ParticleEditor";
            this.Text = "ParticleEditor";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.createMenu.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TreeView normalProperty;
        private System.Windows.Forms.ContextMenuStrip createMenu;
        private System.Windows.Forms.ToolStripMenuItem 新建ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem iDToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem c类ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 影响器ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 发射器ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 材质ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 文理UVToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem shaderIndexToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 添加粒子团ToolStripMenuItem;
    }
}