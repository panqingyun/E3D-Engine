namespace EngineEditor
{
    partial class BoolenContener
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

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.name = new System.Windows.Forms.Label();
            this.yes = new System.Windows.Forms.RadioButton();
            this.no = new System.Windows.Forms.RadioButton();
            this.SuspendLayout();
            // 
            // name
            // 
            this.name.AutoSize = true;
            this.name.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.name.Location = new System.Drawing.Point(3, 4);
            this.name.Name = "name";
            this.name.Size = new System.Drawing.Size(68, 17);
            this.name.TabIndex = 1;
            this.name.Text = "最大粒子数";
            // 
            // yes
            // 
            this.yes.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.yes.AutoSize = true;
            this.yes.Location = new System.Drawing.Point(137, 4);
            this.yes.Name = "yes";
            this.yes.Size = new System.Drawing.Size(35, 16);
            this.yes.TabIndex = 2;
            this.yes.TabStop = true;
            this.yes.Text = "是";
            this.yes.UseVisualStyleBackColor = true;
            // 
            // no
            // 
            this.no.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.no.AutoSize = true;
            this.no.Location = new System.Drawing.Point(202, 4);
            this.no.Name = "no";
            this.no.Size = new System.Drawing.Size(35, 16);
            this.no.TabIndex = 3;
            this.no.TabStop = true;
            this.no.Text = "否";
            this.no.UseVisualStyleBackColor = true;
            // 
            // BoolenContener
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.Controls.Add(this.no);
            this.Controls.Add(this.yes);
            this.Controls.Add(this.name);
            this.Name = "BoolenContener";
            this.Size = new System.Drawing.Size(240, 26);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label name;
        private System.Windows.Forms.RadioButton yes;
        private System.Windows.Forms.RadioButton no;
    }
}
