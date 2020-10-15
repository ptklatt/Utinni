
namespace UtinniCoreDotNet.UI.Forms
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
            this.cmbPanels = new UtinniCoreDotNet.UI.Controls.UtinniComboBox();
            this.pnlPlugins = new System.Windows.Forms.Panel();
            this.pnlPlugins.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlGame
            // 
            this.pnlGame.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pnlGame.BackColor = System.Drawing.Color.Black;
            this.pnlGame.Location = new System.Drawing.Point(452, 34);
            this.pnlGame.Name = "pnlGame";
            this.pnlGame.Size = new System.Drawing.Size(742, 460);
            this.pnlGame.TabIndex = 3;
            // 
            // cmbPanels
            // 
            this.cmbPanels.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(40)))), ((int)(((byte)(40)))), ((int)(((byte)(40)))));
            this.cmbPanels.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.cmbPanels.DrawOutline = true;
            this.cmbPanels.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPanels.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cmbPanels.ForeColor = System.Drawing.Color.WhiteSmoke;
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
            this.pnlPlugins.Size = new System.Drawing.Size(446, 460);
            this.pnlPlugins.TabIndex = 7;
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1207, 500);
            this.Controls.Add(this.pnlPlugins);
            this.Controls.Add(this.pnlGame);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.IconImage = global::UtinniCoreDotNet.Properties.Resources.TJT1;
            this.KeyPreview = true;
            this.Name = "FormMain";
            this.Text = "Utinni";
            this.Shown += new System.EventHandler(this.FormMain_Shown);
            this.Resize += new System.EventHandler(this.FormMain_Resize);
            this.pnlPlugins.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Panel pnlGame;
        private UtinniCoreDotNet.UI.Controls.UtinniComboBox cmbPanels;
        private System.Windows.Forms.Panel pnlPlugins;
    }
}