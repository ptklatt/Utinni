using System;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniTitlebarToggleButton : UtinniTitlebarButton
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
                    SetBackColors(Colors.Primary(), Colors.Primary());
                }

                OnCheckedChanged();
                Invalidate();
            }
        }

        public UtinniTitlebarToggleButton(string text) : base(text)
        {
            SetBackColors(Colors.Primary(), Colors.Primary());
        }

        public UtinniTitlebarToggleButton(Bitmap image) : base(image)
        {
            SetBackColors(Colors.Primary(), Colors.Primary());
        }

        public UtinniTitlebarToggleButton(Bitmap image, Color hoverBackColor) : base(image, hoverBackColor)
        {
            SetBackColors(Colors.Primary(), Colors.Primary());
        }

        protected override void OnMouseClick(MouseEventArgs e)
        {
            base.OnMouseClick(e);
            Checked = !Checked;
        }
    }
}
