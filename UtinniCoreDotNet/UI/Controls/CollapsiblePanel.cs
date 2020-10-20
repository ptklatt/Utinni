using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace UtinniCoreDotNet.UI.Controls
{
    public partial class CollapsiblePanel : Panel
    {
        [Description("Panel Text"), Category("Data")]
        public string CollapsablePanelText
        {
            get { return btnExpand.Text; }
            set { btnExpand.Text = value; }
        }

        [Description("Panel Open"), Category("Data")]
        public bool Open
        {
            get { return btnExpand.Checked; }
            set { btnExpand.Checked = value; }
        }

        [Description("Checkbox Panel Autosize"), Category("Data")]
        public bool CollapsablePanelAutosize
        {
            get { return subPanel.AutoSize; }
            set { subPanel.AutoSize = value; }
        }

        [Description("Checkbox Panel Autosize Mode"), Category("Data")]
        public AutoSizeMode CollapsablePanelAutoSizeMode
        {
            get { return AutoSizeMode; }
            set { AutoSizeMode = value; }
        }

        private readonly SubPanel subPanel;

        public CollapsiblePanel(SubPanel subPanel, string panelText = "", int width = 420)
        {
            InitializeComponent();

            this.subPanel = subPanel;
            CollapsablePanelText = panelText;
            Open = this.subPanel.IsOpenByDefault;

            Width = width;
            this.subPanel.Width = Width - 6;
        }

        private void btnExpand_CheckedChanged(object sender, EventArgs e)
        {
            if (Open)
            {
                subPanel.Location = new Point(3, 24);
                Controls.Add(subPanel);
                Height = subPanel.Height + 30;
            }
            else
            {
                if (Controls.Count > 1) // First control of UserControl = CheckboxButton
                {
                    Height = 26;
                    Controls.RemoveAt(1); // Second (Dynamic) control of UserControl = Custom Panel, remove it to keep the whole thing lighter. Unsure how efficient .RemoveAt is
                }
            }
        }
    }
    
}
