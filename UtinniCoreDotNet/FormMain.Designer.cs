namespace UtinniCoreDotNet
{
    partial class FormMain
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.pnlGame = new System.Windows.Forms.Panel();
            this.flpnlPlugins = new System.Windows.Forms.FlowLayoutPanel();
            this.tsMain = new System.Windows.Forms.ToolStrip();
            this.tsbtnUndo = new System.Windows.Forms.ToolStripButton();
            this.tsbtnRedo = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.tsMain.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlGame
            // 
            this.pnlGame.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pnlGame.Location = new System.Drawing.Point(452, 34);
            this.pnlGame.Name = "pnlGame";
            this.pnlGame.Size = new System.Drawing.Size(742, 460);
            this.pnlGame.TabIndex = 3;
            // 
            // flpnlPlugins
            // 
            this.flpnlPlugins.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.flpnlPlugins.Location = new System.Drawing.Point(0, 28);
            this.flpnlPlugins.Name = "flpnlPlugins";
            this.flpnlPlugins.Size = new System.Drawing.Size(446, 460);
            this.flpnlPlugins.TabIndex = 4;
            // 
            // tsMain
            // 
            this.tsMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbtnUndo,
            this.tsbtnRedo,
            this.toolStripButton1,
            this.toolStripButton2});
            this.tsMain.Location = new System.Drawing.Point(0, 0);
            this.tsMain.Name = "tsMain";
            this.tsMain.Size = new System.Drawing.Size(1207, 25);
            this.tsMain.TabIndex = 5;
            this.tsMain.Text = "toolStrip1";
            // 
            // tsbtnUndo
            // 
            this.tsbtnUndo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tsbtnUndo.Image = ((System.Drawing.Image)(resources.GetObject("tsbtnUndo.Image")));
            this.tsbtnUndo.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbtnUndo.Name = "tsbtnUndo";
            this.tsbtnUndo.Size = new System.Drawing.Size(40, 22);
            this.tsbtnUndo.Text = "Undo";
            this.tsbtnUndo.Click += new System.EventHandler(this.tsbtnUndo_Click);
            // 
            // tsbtnRedo
            // 
            this.tsbtnRedo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tsbtnRedo.Image = ((System.Drawing.Image)(resources.GetObject("tsbtnRedo.Image")));
            this.tsbtnRedo.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbtnRedo.Name = "tsbtnRedo";
            this.tsbtnRedo.Size = new System.Drawing.Size(38, 22);
            this.tsbtnRedo.Text = "Redo";
            this.tsbtnRedo.Click += new System.EventHandler(this.tsbtnRedo_Click);
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(98, 22);
            this.toolStripButton1.Text = "toolStripButton1";
            this.toolStripButton1.Click += new System.EventHandler(this.toolStripButton1_Click);
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripButton2.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton2.Image")));
            this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Size = new System.Drawing.Size(98, 22);
            this.toolStripButton2.Text = "toolStripButton1";
            this.toolStripButton2.Click += new System.EventHandler(this.toolStripButton2_Click);
            // 
            // cmbPanels
            // 
            this.cmbPanels.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPanels.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cmbPanels.FormattingEnabled = true;
            this.cmbPanels.Location = new System.Drawing.Point(0, 34);
            this.cmbPanels.Name = "cmbPanels";
            this.cmbPanels.Size = new System.Drawing.Size(446, 21);
            this.cmbPanels.TabIndex = 6;
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1207, 500);
            this.Controls.Add(this.cmbPanels);
            this.Controls.Add(this.tsMain);
            this.Controls.Add(this.flpnlPlugins);
            this.Controls.Add(this.pnlGame);
            this.Name = "FormMain";
            this.Text = "FormMain";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
            this.Shown += new System.EventHandler(this.FormMain_Shown);
            this.Resize += new System.EventHandler(this.FormMain_Resize);
            this.tsMain.ResumeLayout(false);
            this.tsMain.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Panel pnlGame;
        private System.Windows.Forms.FlowLayoutPanel flpnlPlugins;
        private System.Windows.Forms.ToolStrip tsMain;
        private System.Windows.Forms.ToolStripButton tsbtnUndo;
        private System.Windows.Forms.ToolStripButton tsbtnRedo;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.ToolStripButton toolStripButton2;
    }
}