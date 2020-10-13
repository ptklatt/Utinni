using System;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniTitlebarButton : UtinniButtonBase
    {
        private readonly Point centerPoint = new Point(23, 16);
        private readonly Point imagePos16x16 = new Point(15, 8);
        private Bitmap image;

        public UtinniTitlebarButton(string text)
        {
            Setup(Colors.Primary());
            base.Text = text;
            UpdateWidth();
        }

        public UtinniTitlebarButton(Bitmap image) : this(image, Colors.Primary()) { }

        public UtinniTitlebarButton(Bitmap image, Color hoverBackColor)
        {
            this.image = ThemeUtility.UpdateImageColor(image, Color.FromArgb(32, 32, 32), Colors.Font());
            UseDisableColor = false;
            Setup(hoverBackColor);
            UpdateImageForecolor();

            Width = 46;
        }

        private void Setup(Color hoverBackColor)
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw | ControlStyles.UserPaint, true);
            SetBackColors(hoverBackColor);

            Height = 32;
        }

        private void UpdateImageForecolor()
        {
            if (Enabled)
            {
                image = ThemeUtility.UpdateImageColor(image, Colors.FontDisabled(), Colors.Font());
            }
            else
            {
                image = ThemeUtility.UpdateImageColor(image, Colors.Font(), Colors.FontDisabled());
            }
        }

        public void SetImage(Bitmap image)
        {
            this.image = ThemeUtility.UpdateImageColor(image, Color.FromArgb(32, 32, 32), Colors.Font());
            UpdateImageForecolor();
            Invalidate();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            if (image != null)
            {
                // Draw the image
                e.Graphics.DrawImage(image, imagePos16x16);
            }
            else
            {
                // Draw the Text if there is no image
                Rectangle textRect = new Rectangle(0, 0, ClientRectangle.Width, ClientRectangle.Height);
                TextRenderer.DrawText(e.Graphics, Text, Font, textRect, Colors.Font());
            }
        }

        protected override void OnTextChanged(EventArgs e)
        {
            base.OnTextChanged(e);
            UpdateWidth();
        }

        private void UpdateWidth()
        {
            Size size = TextRenderer.MeasureText(Text, Font);
            Width = 3 + size.Width;
        }

        protected override void OnEnabledChanged(EventArgs e)
        {
            base.OnEnabledChanged(e);

            UpdateImageForecolor();
        }
    }

}
