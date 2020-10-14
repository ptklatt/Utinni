using System;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniToggleButton : UtinniButtonBase
    {
        public event EventHandler CheckedChanged;
        private void OnCheckedChanged()
        {
            if (CheckedChanged != null)
            {
                CheckedChanged(this, EventArgs.Empty);
            }
        }

        private bool isChecked;
        public bool Checked
        {
            get { return isChecked; }
            set
            {
                isChecked = value;

                if (isChecked)
                {
                    SetBackColors(Colors.Secondary(), Colors.Secondary());
                }
                else
                {
                    SetBackColors(Colors.PrimaryHighlight(), Colors.PrimaryHighlight());
                }

                OnCheckedChanged();
                Invalidate();
            }
        }

        public UtinniToggleButton()
        {
            SetBackColors(Colors.PrimaryHighlight(), Colors.PrimaryHighlight());
            Height = 20;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Rectangle textRect = new Rectangle(0, 0, ClientRectangle.Width, ClientRectangle.Height);
            TextRenderer.DrawText(e.Graphics, Text, Font, textRect, ForeColor);
        }

        protected override void OnMouseClick(MouseEventArgs e)
        {
            base.OnMouseClick(e);
            Checked = !Checked;
        }
    }
}
