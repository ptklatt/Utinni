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
            this.tsMain = new System.Windows.Forms.ToolStrip();
            this.tsddbtnWindows = new System.Windows.Forms.ToolStripDropDownButton();
            this.tsmiLog = new System.Windows.Forms.ToolStripMenuItem();
            this.tsbtnUndo = new System.Windows.Forms.ToolStripSplitButton();
            this.tsbtnRedo = new System.Windows.Forms.ToolStripSplitButton();
            this.tsbtnToggleUI = new System.Windows.Forms.ToolStripButton();
            this.cmbPanels = new System.Windows.Forms.ComboBox();
            this.pnlPlugins = new System.Windows.Forms.Panel();
            this.tsMain.SuspendLayout();
            this.pnlPlugins.SuspendLayout();
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
            // tsMain
            // 
            this.tsMain.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.tsMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsddbtnWindows,
            this.tsbtnUndo,
            this.tsbtnRedo,
            this.tsbtnToggleUI});
            this.tsMain.Location = new System.Drawing.Point(0, 0);
            this.tsMain.Name = "tsMain";
            this.tsMain.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.tsMain.Size = new System.Drawing.Size(1207, 25);
            this.tsMain.TabIndex = 5;
            this.tsMain.Text = "toolStrip1";
            // 
            // tsddbtnWindows
            // 
            this.tsddbtnWindows.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tsddbtnWindows.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiLog});
            this.tsddbtnWindows.Image = ((System.Drawing.Image)(resources.GetObject("tsddbtnWindows.Image")));
            this.tsddbtnWindows.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsddbtnWindows.Name = "tsddbtnWindows";
            this.tsddbtnWindows.Size = new System.Drawing.Size(58, 22);
            this.tsddbtnWindows.Text = "Open...";
            // 
            // tsmiLog
            // 
            this.tsmiLog.Name = "tsmiLog";
            this.tsmiLog.Size = new System.Drawing.Size(94, 22);
            this.tsmiLog.Text = "Log";
            this.tsmiLog.Click += new System.EventHandler(this.tsmiLog_Click);
            // 
            // tsbtnUndo
            // 
            this.tsbtnUndo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tsbtnUndo.Enabled = false;
            this.tsbtnUndo.Image = ((System.Drawing.Image)(resources.GetObject("tsbtnUndo.Image")));
            this.tsbtnUndo.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbtnUndo.Name = "tsbtnUndo";
            this.tsbtnUndo.Size = new System.Drawing.Size(52, 22);
            this.tsbtnUndo.Text = "Undo";
            this.tsbtnUndo.ButtonClick += new System.EventHandler(this.tsbtnUndo_Click);
            this.tsbtnUndo.DropDownOpening += new System.EventHandler(this.tsbtnUndo_DropDownOpening);
            // 
            // tsbtnRedo
            // 
            this.tsbtnRedo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tsbtnRedo.Enabled = false;
            this.tsbtnRedo.Image = ((System.Drawing.Image)(resources.GetObject("tsbtnRedo.Image")));
            this.tsbtnRedo.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbtnRedo.Name = "tsbtnRedo";
            this.tsbtnRedo.Size = new System.Drawing.Size(50, 22);
            this.tsbtnRedo.Text = "Redo";
            this.tsbtnRedo.ButtonClick += new System.EventHandler(this.tsbtnRedo_Click);
            this.tsbtnRedo.DropDownOpening += new System.EventHandler(this.tsbtnRedo_DropDownOpening);
            // 
            // tsbtnToggleUI
            // 
            this.tsbtnToggleUI.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.tsbtnToggleUI.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tsbtnToggleUI.Image = ((System.Drawing.Image)(resources.GetObject("tsbtnToggleUI.Image")));
            this.tsbtnToggleUI.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbtnToggleUI.Name = "tsbtnToggleUI";
            this.tsbtnToggleUI.Size = new System.Drawing.Size(60, 22);
            this.tsbtnToggleUI.Text = "Toggle UI";
            this.tsbtnToggleUI.Click += new System.EventHandler(this.tsbtnToggleUI_Click);
            // 
            // cmbPanels
            // 
            this.cmbPanels.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPanels.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cmbPanels.FormattingEnabled = true;
            this.cmbPanels.Location = new System.Drawing.Point(3, 3);
            this.cmbPanels.Name = "cmbPanels";
            this.cmbPanels.Size = new System.Drawing.Size(420, 21);
            this.cmbPanels.TabIndex = 6;
            this.cmbPanels.TabStop = false;
            // 
            // pnlPlugins
            // 
            this.pnlPlugins.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.pnlPlugins.AutoScroll = true;
            this.pnlPlugins.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.pnlPlugins.BackColor = System.Drawing.SystemColors.Control;
            this.pnlPlugins.Controls.Add(this.cmbPanels);
            this.pnlPlugins.Location = new System.Drawing.Point(0, 34);
            this.pnlPlugins.Name = "pnlPlugins";
            this.pnlPlugins.Size = new System.Drawing.Size(446, 433);
            this.pnlPlugins.TabIndex = 7;
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1207, 500);
            this.Controls.Add(this.pnlPlugins);
            this.Controls.Add(this.tsMain);
            this.Controls.Add(this.pnlGame);
            this.KeyPreview = true;
            this.Name = "FormMain";
            this.Text = "Utinni";
            this.Shown += new System.EventHandler(this.FormMain_Shown);
            this.Resize += new System.EventHandler(this.FormMain_Resize);
            this.tsMain.ResumeLayout(false);
            this.tsMain.PerformLayout();
            this.pnlPlugins.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Panel pnlGame;
        private System.Windows.Forms.ToolStrip tsMain;
        private System.Windows.Forms.ComboBox cmbPanels;
        private System.Windows.Forms.Panel pnlPlugins;
        private System.Windows.Forms.ToolStripSplitButton tsbtnUndo;
        private System.Windows.Forms.ToolStripSplitButton tsbtnRedo;
        private System.Windows.Forms.ToolStripDropDownButton tsddbtnWindows;
        private System.Windows.Forms.ToolStripMenuItem tsmiLog;
        private System.Windows.Forms.ToolStripButton tsbtnToggleUI;
    }
}