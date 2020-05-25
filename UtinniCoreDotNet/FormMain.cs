using System;
using System.Drawing;
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
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData) // ToDo figure out how to handle this inside PanelGame potentially
        {
            if (game.HasFocus)
            {
                if (keyData == Keys.Tab)
                {
                    return true;
                }
                else
                {
                    return false; // Block key input if the game has focus, to prevent the input firing things inside WinForms
                }
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        private void FormMain_Shown(object sender, EventArgs e)
        {

            Point thisPos = PointToScreen(Point.Empty);
            Cursor.Position = new Point(thisPos.X + 20, thisPos.Y + 20);
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
