namespace EngineEditor
{
    partial class PositionContener
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
            this.X = new System.Windows.Forms.TextBox();
            this.Y = new System.Windows.Forms.TextBox();
            this.Z = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // name
            // 
            this.name.AutoSize = true;
            this.name.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.name.Location = new System.Drawing.Point(3, 4);
            this.name.Name = "name";
            this.name.Size = new System.Drawing.Size(68, 17);
            this.name.TabIndex = 2;
            this.name.Text = "最大粒子数";
            // 
            // X
            // 
            this.X.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.X.BackColor = System.Drawing.Color.Black;
            this.X.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.X.ForeColor = System.Drawing.Color.White;
            this.X.Location = new System.Drawing.Point(111, 2);
            this.X.Name = "X";
            this.X.Size = new System.Drawing.Size(56, 23);
            this.X.TabIndex = 3;
            this.X.Text = "1000";
            this.X.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.X_KeyPress);
            // 
            // Y
            // 
            this.Y.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Y.BackColor = System.Drawing.Color.Black;
            this.Y.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Y.ForeColor = System.Drawing.Color.White;
            this.Y.Location = new System.Drawing.Point(173, 2);
            this.Y.Name = "Y";
            this.Y.Size = new System.Drawing.Size(56, 23);
            this.Y.TabIndex = 4;
            this.Y.Text = "1000";
            // 
            // Z
            // 
            this.Z.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Z.BackColor = System.Drawing.Color.Black;
            this.Z.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Z.ForeColor = System.Drawing.Color.White;
            this.Z.Location = new System.Drawing.Point(235, 2);
            this.Z.Name = "Z";
            this.Z.Size = new System.Drawing.Size(56, 23);
            this.Z.TabIndex = 5;
            this.Z.Text = "1000";
            // 
            // PositionContener
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.Controls.Add(this.Z);
            this.Controls.Add(this.Y);
            this.Controls.Add(this.X);
            this.Controls.Add(this.name);
            this.Name = "PositionContener";
            this.Size = new System.Drawing.Size(294, 26);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label name;
        private System.Windows.Forms.TextBox X;
        private System.Windows.Forms.TextBox Y;
        private System.Windows.Forms.TextBox Z;
    }
}
