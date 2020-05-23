using System;
using System.Windows.Forms;

namespace UtinniCoreDotNet
{
    public partial class FormMain : Form
    {
        private PanelGame game;

        public FormMain()
        {
            InitializeComponent();

            game = new PanelGame();
            pnlGame.Controls.Add(game);

            KeyPreview = true;
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData) // ToDo figure out how to handle this inside PanelGame potentially
        {
            if (game.HasFocus && keyData == Keys.Tab)
            {
                return true; // Block the TAB key from firing inside WinForms when the game has focus
            }

            if (game.HasFocus )
            {
                return false; // Block other key input if the game has focus, to prevent the input firing things inside WinForms
            }

            return base.ProcessCmdKey(ref msg, keyData);
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
    }
}
