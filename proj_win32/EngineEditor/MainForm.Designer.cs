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
            this.EngineContener = new System.Windows.Forms.Panel();
            this.file = new System.Windows.Forms.ToolStrip();
            this.openFile = new System.Windows.Forms.ToolStripDropDownButton();
            this.打开ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.粒子ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.文字ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.保存ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.日志ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.item = new System.Windows.Forms.ToolStripDropDownButton();
            this.粒子编辑ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.文字特效ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.滤镜特效ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.清理场景ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.清理并切换场景ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.frameSpeed = new System.Windows.Forms.ToolStripLabel();
            this.pauseButton = new System.Windows.Forms.ToolStripButton();
            this.nextFrame = new System.Windows.Forms.ToolStripButton();
            this.treeViewFile = new System.Windows.Forms.TreeView();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.新建ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.OK_btn = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.effectMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.暂停ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.停止ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.lodPanel = new System.Windows.Forms.Panel();
            this.file.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.effectMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // EngineContener
            // 
            this.EngineContener.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.EngineContener.Location = new System.Drawing.Point(325, 35);
            this.EngineContener.Name = "EngineContener";
            this.EngineContener.Size = new System.Drawing.Size(929, 688);
            this.EngineContener.TabIndex = 0;
            this.EngineContener.MouseDown += new System.Windows.Forms.MouseEventHandler(this.EngineContener_MouseDown);
            this.EngineContener.MouseMove += new System.Windows.Forms.MouseEventHandler(this.EngineContener_MouseMove);
            this.EngineContener.MouseUp += new System.Windows.Forms.MouseEventHandler(this.EngineContener_MouseUp);
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
            this.file.TabIndex = 2;
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
            this.日志ToolStripMenuItem.Click += new System.EventHandler(this.日志ToolStripMenuItem_Click);
            // 
            // item
            // 
            this.item.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.item.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.粒子编辑ToolStripMenuItem,
            this.文字特效ToolStripMenuItem,
            this.滤镜特效ToolStripMenuItem,
            this.清理场景ToolStripMenuItem,
            this.清理并切换场景ToolStripMenuItem});
            this.item.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.item.ForeColor = System.Drawing.Color.Silver;
            this.item.Image = ((System.Drawing.Image)(resources.GetObject("item.Image")));
            this.item.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.item.Name = "item";
            this.item.Size = new System.Drawing.Size(45, 29);
            this.item.Text = "选项";
            // 
            // 粒子编辑ToolStripMenuItem
            // 
            this.粒子编辑ToolStripMenuItem.Name = "粒子编辑ToolStripMenuItem";
            this.粒子编辑ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.粒子编辑ToolStripMenuItem.Text = "粒子编辑";
            // 
            // 文字特效ToolStripMenuItem
            // 
            this.文字特效ToolStripMenuItem.Name = "文字特效ToolStripMenuItem";
            this.文字特效ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.文字特效ToolStripMenuItem.Text = "文字特效";
            // 
            // 滤镜特效ToolStripMenuItem
            // 
            this.滤镜特效ToolStripMenuItem.Name = "滤镜特效ToolStripMenuItem";
            this.滤镜特效ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.滤镜特效ToolStripMenuItem.Text = "滤镜特效";
            // 
            // 清理场景ToolStripMenuItem
            // 
            this.清理场景ToolStripMenuItem.Name = "清理场景ToolStripMenuItem";
            this.清理场景ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.清理场景ToolStripMenuItem.Text = "清理场景";
            // 
            // 清理并切换场景ToolStripMenuItem
            // 
            this.清理并切换场景ToolStripMenuItem.Name = "清理并切换场景ToolStripMenuItem";
            this.清理并切换场景ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.清理并切换场景ToolStripMenuItem.Text = "场景列表";
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
            // pauseButton
            // 
            this.pauseButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.pauseButton.Image = ((System.Drawing.Image)(resources.GetObject("pauseButton.Image")));
            this.pauseButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.pauseButton.Margin = new System.Windows.Forms.Padding(600, 5, 0, 5);
            this.pauseButton.Name = "pauseButton";
            this.pauseButton.Size = new System.Drawing.Size(23, 22);
            this.pauseButton.ToolTipText = "单击启动";
            this.pauseButton.Click += new System.EventHandler(this.pauseButton_Click);
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
            // treeViewFile
            // 
            this.treeViewFile.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.treeViewFile.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.treeViewFile.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.treeViewFile.Location = new System.Drawing.Point(0, 35);
            this.treeViewFile.Name = "treeViewFile";
            this.treeViewFile.Size = new System.Drawing.Size(319, 688);
            this.treeViewFile.TabIndex = 3;
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
            this.OK_btn.Location = new System.Drawing.Point(193, 826);
            this.OK_btn.Name = "OK_btn";
            this.OK_btn.Size = new System.Drawing.Size(85, 30);
            this.OK_btn.TabIndex = 0;
            this.OK_btn.Text = "确定";
            this.OK_btn.UseVisualStyleBackColor = true;
            // 
            // panel2
            // 
            this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel2.AutoScroll = true;
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.panel2.Controls.Add(this.OK_btn);
            this.panel2.Location = new System.Drawing.Point(1262, 35);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(323, 870);
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
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // timer2
            // 
            this.timer2.Enabled = true;
            this.timer2.Interval = 1000;
            // 
            // lodPanel
            // 
            this.lodPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lodPanel.Location = new System.Drawing.Point(0, 729);
            this.lodPanel.Name = "lodPanel";
            this.lodPanel.Size = new System.Drawing.Size(1256, 176);
            this.lodPanel.TabIndex = 4;
            // 
            // EffectEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1589, 911);
            this.Controls.Add(this.lodPanel);
            this.Controls.Add(this.treeViewFile);
            this.Controls.Add(this.file);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.EngineContener);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "EffectEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Engine Windows";
            this.Activated += new System.EventHandler(this.EffectEditor_Activated);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.EffectEditor_FormClosed);
            this.Load += new System.EventHandler(this.EffectEditor_Load_1);
            this.SizeChanged += new System.EventHandler(this.EffectEditor_SizeChanged);
            this.file.ResumeLayout(false);
            this.file.PerformLayout();
            this.contextMenuStrip1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.effectMenu.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel EngineContener;
        private System.Windows.Forms.ToolStrip file;
        private System.Windows.Forms.ToolStripDropDownButton openFile;
        private System.Windows.Forms.ToolStripMenuItem 打开ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 保存ToolStripMenuItem;
        private System.Windows.Forms.ToolStripDropDownButton item;
        private System.Windows.Forms.ToolStripMenuItem 粒子编辑ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 文字特效ToolStripMenuItem;
        private System.Windows.Forms.TreeView treeViewFile;
        private System.Windows.Forms.ToolStripMenuItem 粒子ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 文字ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 清理场景ToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 新建ToolStripMenuItem;
        private System.Windows.Forms.Button OK_btn;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.ContextMenuStrip effectMenu;
        private System.Windows.Forms.ToolStripMenuItem 暂停ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 停止ToolStripMenuItem;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripLabel frameSpeed;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.ToolStripMenuItem 滤镜特效ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 清理并切换场景ToolStripMenuItem;
        private System.Windows.Forms.ToolStripButton pauseButton;
        private System.Windows.Forms.ToolStripButton nextFrame;
        private System.Windows.Forms.ToolStripMenuItem 日志ToolStripMenuItem;
        private System.Windows.Forms.Panel lodPanel;
    }
}

