namespace EngineEditor
{
    partial class EffectEditor
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EffectEditor));
            this.nextFrame = new System.Windows.Forms.ToolStripButton();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.新建ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.OK_btn = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.effectMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.暂停ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.停止ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.treeViewFile = new System.Windows.Forms.TreeView();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.lodPanel = new System.Windows.Forms.Panel();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.sceneTab = new System.Windows.Forms.TabPage();
            this.sceneContener = new System.Windows.Forms.Panel();
            this.gameTab = new System.Windows.Forms.TabPage();
            this.gameContener = new System.Windows.Forms.Panel();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.pauseButton = new System.Windows.Forms.ToolStripButton();
            this.file = new System.Windows.Forms.ToolStrip();
            this.openFile = new System.Windows.Forms.ToolStripDropDownButton();
            this.打开ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.粒子ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.文字ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.保存ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.日志ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.item = new System.Windows.Forms.ToolStripDropDownButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.frameSpeed = new System.Windows.Forms.ToolStripLabel();
            this.contextMenuStrip1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.effectMenu.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.sceneTab.SuspendLayout();
            this.gameTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).BeginInit();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.Panel2.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            this.file.SuspendLayout();
            this.SuspendLayout();
            // 
            // nextFrame
            // 
            this.nextFrame.AutoSize = false;
            this.nextFrame.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.nextFrame.Enabled = false;
            this.nextFrame.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.nextFrame.Image = ((System.Drawing.Image)(resources.GetObject("nextFrame.Image")));
            this.nextFrame.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.nextFrame.Margin = new System.Windows.Forms.Padding(0, 0, 0, 2);
            this.nextFrame.Name = "nextFrame";
            this.nextFrame.Size = new System.Drawing.Size(30, 30);
            this.nextFrame.ToolTipText = "下一帧";
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.新建ToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(101, 26);
            // 
            // 新建ToolStripMenuItem
            // 
            this.新建ToolStripMenuItem.Name = "新建ToolStripMenuItem";
            this.新建ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.新建ToolStripMenuItem.Text = "新建";
            // 
            // OK_btn
            // 
            this.OK_btn.Location = new System.Drawing.Point(97, 730);
            this.OK_btn.Name = "OK_btn";
            this.OK_btn.Size = new System.Drawing.Size(85, 30);
            this.OK_btn.TabIndex = 0;
            this.OK_btn.Text = "确定";
            this.OK_btn.UseVisualStyleBackColor = true;
            // 
            // panel2
            // 
            this.panel2.AutoScroll = true;
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.panel2.Controls.Add(this.OK_btn);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(274, 879);
            this.panel2.TabIndex = 1;
            // 
            // effectMenu
            // 
            this.effectMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.暂停ToolStripMenuItem,
            this.停止ToolStripMenuItem});
            this.effectMenu.Name = "effectMenu";
            this.effectMenu.Size = new System.Drawing.Size(101, 48);
            // 
            // 暂停ToolStripMenuItem
            // 
            this.暂停ToolStripMenuItem.Name = "暂停ToolStripMenuItem";
            this.暂停ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.暂停ToolStripMenuItem.Text = "暂停";
            // 
            // 停止ToolStripMenuItem
            // 
            this.停止ToolStripMenuItem.Name = "停止ToolStripMenuItem";
            this.停止ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.停止ToolStripMenuItem.Text = "停止";
            // 
            // treeViewFile
            // 
            this.treeViewFile.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.treeViewFile.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeViewFile.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.treeViewFile.Location = new System.Drawing.Point(0, 0);
            this.treeViewFile.Name = "treeViewFile";
            this.treeViewFile.Size = new System.Drawing.Size(291, 668);
            this.treeViewFile.TabIndex = 3;
            // 
            // timer2
            // 
            this.timer2.Enabled = true;
            // 
            // lodPanel
            // 
            this.lodPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lodPanel.Location = new System.Drawing.Point(0, 0);
            this.lodPanel.Name = "lodPanel";
            this.lodPanel.Size = new System.Drawing.Size(1311, 207);
            this.lodPanel.TabIndex = 4;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Margin = new System.Windows.Forms.Padding(0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.lodPanel);
            this.splitContainer1.Size = new System.Drawing.Size(1311, 879);
            this.splitContainer1.SplitterDistance = 668;
            this.splitContainer1.TabIndex = 5;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Margin = new System.Windows.Forms.Padding(0);
            this.splitContainer2.Name = "splitContainer2";
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.treeViewFile);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.tabControl1);
            this.splitContainer2.Size = new System.Drawing.Size(1311, 668);
            this.splitContainer2.SplitterDistance = 291;
            this.splitContainer2.TabIndex = 0;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.sceneTab);
            this.tabControl1.Controls.Add(this.gameTab);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tabControl1.ItemSize = new System.Drawing.Size(100, 25);
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Margin = new System.Windows.Forms.Padding(0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.Padding = new System.Drawing.Point(0, 0);
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1016, 668);
            this.tabControl1.TabIndex = 1;
            // 
            // sceneTab
            // 
            this.sceneTab.BackColor = System.Drawing.Color.Gray;
            this.sceneTab.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.sceneTab.Controls.Add(this.sceneContener);
            this.sceneTab.Location = new System.Drawing.Point(4, 29);
            this.sceneTab.Margin = new System.Windows.Forms.Padding(0);
            this.sceneTab.Name = "sceneTab";
            this.sceneTab.Size = new System.Drawing.Size(1008, 635);
            this.sceneTab.TabIndex = 0;
            this.sceneTab.Text = "Scene";
            // 
            // sceneContener
            // 
            this.sceneContener.Dock = System.Windows.Forms.DockStyle.Fill;
            this.sceneContener.Location = new System.Drawing.Point(0, 0);
            this.sceneContener.Name = "sceneContener";
            this.sceneContener.Size = new System.Drawing.Size(1008, 635);
            this.sceneContener.TabIndex = 0;
            this.sceneContener.SizeChanged += new System.EventHandler(this.EffectEditor_SizeChanged);
            this.sceneContener.MouseDown += new System.Windows.Forms.MouseEventHandler(this.EngineContener_MouseDown);
            this.sceneContener.MouseMove += new System.Windows.Forms.MouseEventHandler(this.EngineContener_MouseMove);
            this.sceneContener.MouseUp += new System.Windows.Forms.MouseEventHandler(this.EngineContener_MouseUp);
            // 
            // gameTab
            // 
            this.gameTab.Controls.Add(this.gameContener);
            this.gameTab.Location = new System.Drawing.Point(4, 29);
            this.gameTab.Name = "gameTab";
            this.gameTab.Padding = new System.Windows.Forms.Padding(3);
            this.gameTab.Size = new System.Drawing.Size(1008, 635);
            this.gameTab.TabIndex = 1;
            this.gameTab.Text = "Game";
            this.gameTab.UseVisualStyleBackColor = true;
            // 
            // gameContener
            // 
            this.gameContener.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gameContener.Location = new System.Drawing.Point(3, 3);
            this.gameContener.Name = "gameContener";
            this.gameContener.Size = new System.Drawing.Size(1002, 629);
            this.gameContener.TabIndex = 1;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // splitContainer3
            // 
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.Location = new System.Drawing.Point(0, 32);
            this.splitContainer3.Margin = new System.Windows.Forms.Padding(0);
            this.splitContainer3.Name = "splitContainer3";
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.splitContainer1);
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.Controls.Add(this.panel2);
            this.splitContainer3.Size = new System.Drawing.Size(1589, 879);
            this.splitContainer3.SplitterDistance = 1311;
            this.splitContainer3.TabIndex = 8;
            // 
            // pauseButton
            // 
            this.pauseButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.pauseButton.Image = ((System.Drawing.Image)(resources.GetObject("pauseButton.Image")));
            this.pauseButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.pauseButton.Margin = new System.Windows.Forms.Padding(600, 5, 0, 5);
            this.pauseButton.Name = "pauseButton";
            this.pauseButton.Size = new System.Drawing.Size(23, 22);
            this.pauseButton.ToolTipText = "单击启动";
            // 
            // file
            // 
            this.file.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.file.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openFile,
            this.item,
            this.toolStripSeparator1,
            this.frameSpeed,
            this.pauseButton,
            this.nextFrame});
            this.file.Location = new System.Drawing.Point(0, 0);
            this.file.Name = "file";
            this.file.Size = new System.Drawing.Size(1589, 32);
            this.file.TabIndex = 7;
            this.file.Text = "文件";
            // 
            // openFile
            // 
            this.openFile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.openFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.打开ToolStripMenuItem,
            this.保存ToolStripMenuItem,
            this.日志ToolStripMenuItem});
            this.openFile.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.openFile.ForeColor = System.Drawing.Color.Silver;
            this.openFile.Image = ((System.Drawing.Image)(resources.GetObject("openFile.Image")));
            this.openFile.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.openFile.Name = "openFile";
            this.openFile.Size = new System.Drawing.Size(45, 29);
            this.openFile.Text = "文件";
            // 
            // 打开ToolStripMenuItem
            // 
            this.打开ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.粒子ToolStripMenuItem,
            this.文字ToolStripMenuItem});
            this.打开ToolStripMenuItem.Name = "打开ToolStripMenuItem";
            this.打开ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.打开ToolStripMenuItem.Text = "新建";
            // 
            // 粒子ToolStripMenuItem
            // 
            this.粒子ToolStripMenuItem.Name = "粒子ToolStripMenuItem";
            this.粒子ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.粒子ToolStripMenuItem.Text = "粒子";
            // 
            // 文字ToolStripMenuItem
            // 
            this.文字ToolStripMenuItem.Name = "文字ToolStripMenuItem";
            this.文字ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.文字ToolStripMenuItem.Text = "文字";
            // 
            // 保存ToolStripMenuItem
            // 
            this.保存ToolStripMenuItem.Name = "保存ToolStripMenuItem";
            this.保存ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.保存ToolStripMenuItem.Text = "保存";
            // 
            // 日志ToolStripMenuItem
            // 
            this.日志ToolStripMenuItem.Name = "日志ToolStripMenuItem";
            this.日志ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.日志ToolStripMenuItem.Text = "日志";
            // 
            // item
            // 
            this.item.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.item.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.item.ForeColor = System.Drawing.Color.Silver;
            this.item.Image = ((System.Drawing.Image)(resources.GetObject("item.Image")));
            this.item.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.item.Name = "item";
            this.item.Size = new System.Drawing.Size(45, 29);
            this.item.Text = "选项";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 32);
            // 
            // frameSpeed
            // 
            this.frameSpeed.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.frameSpeed.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.frameSpeed.ForeColor = System.Drawing.Color.Green;
            this.frameSpeed.Name = "frameSpeed";
            this.frameSpeed.Size = new System.Drawing.Size(137, 29);
            this.frameSpeed.Text = "toolStripLabel1";
            // 
            // EffectEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1589, 911);
            this.Controls.Add(this.splitContainer3);
            this.Controls.Add(this.file);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.Name = "EffectEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Engine Windows";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Activated += new System.EventHandler(this.EffectEditor_Activated);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.EffectEditor_FormClosed);
            this.Load += new System.EventHandler(this.EffectEditor_Load_1);
            this.SizeChanged += new System.EventHandler(this.EffectEditor_SizeChanged);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.EffectEditor_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.EffectEditor_KeyUp);
            this.contextMenuStrip1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.effectMenu.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.sceneTab.ResumeLayout(false);
            this.gameTab.ResumeLayout(false);
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).EndInit();
            this.splitContainer3.ResumeLayout(false);
            this.file.ResumeLayout(false);
            this.file.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStripButton nextFrame;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 新建ToolStripMenuItem;
        private System.Windows.Forms.Button OK_btn;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.ContextMenuStrip effectMenu;
        private System.Windows.Forms.ToolStripMenuItem 暂停ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 停止ToolStripMenuItem;
        private System.Windows.Forms.TreeView treeViewFile;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.Panel lodPanel;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage sceneTab;
        private System.Windows.Forms.Panel sceneContener;
        private System.Windows.Forms.TabPage gameTab;
        private System.Windows.Forms.Panel gameContener;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.ToolStripButton pauseButton;
        private System.Windows.Forms.ToolStrip file;
        private System.Windows.Forms.ToolStripDropDownButton openFile;
        private System.Windows.Forms.ToolStripMenuItem 打开ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 粒子ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 文字ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 保存ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 日志ToolStripMenuItem;
        private System.Windows.Forms.ToolStripDropDownButton item;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripLabel frameSpeed;
    }
}

