using System;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniButton : UtinniButtonBase
    {
        public UtinniButton()
        {
            SetBackColors(Colors.Secondary(), Colors.Secondary());
            Height = 20;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Rectangle textRect = new Rectangle(0, 0, ClientRectangle.Width, ClientRectangle.Height);
            TextRenderer.DrawText(e.Graphics, Text, Font, textRect, ForeColor);
        }
    }
}
