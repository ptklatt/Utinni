using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniButton : UtinniButtonBase
    {
        private Pen outlinePen;

        public UtinniButton()
        {
            SetBackColors(Colors.Secondary(), Colors.Secondary());
            Height = 20;

            outlinePen = new Pen(Colors.ControlBorder(), 1);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Rectangle textRect = new Rectangle(0, 0, ClientRectangle.Width, ClientRectangle.Height);
            TextRenderer.DrawText(e.Graphics, Text, Font, textRect, ForeColor);

            if (DrawOutline)
            {
                e.Graphics.DrawRectangle(outlinePen, 0, 0, Width - 1, Height - 1);
            }
        }
    }
}
