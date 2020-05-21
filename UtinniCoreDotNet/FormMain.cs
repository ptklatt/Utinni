using System;
using System.Windows.Forms;
using UtinniCore.Utinni;

namespace UtinniCoreDotNet
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
            pnlGame.Controls.Add(new PanelGame());
        }

        private void FormMain_Shown(object sender, EventArgs e)
        {
        }

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
        }

        private void button1_Click(object sender, EventArgs e)
        {
			
        }

        private void button2_Click(object sender, EventArgs e)
        {
			
        }

        private void button3_Click(object sender, EventArgs e)
        {
        }

        private void pnlGame_SizeChanged(object sender, EventArgs e)
        {

        }

        private void pnlGame_Resize(object sender, EventArgs e)
        {

        }
    }
}
