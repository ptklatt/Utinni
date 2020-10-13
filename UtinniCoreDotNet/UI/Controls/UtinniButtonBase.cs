using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniButtonBase : Button
    {
        [Description("Draw Outline"), Category("Data")]
        public bool DrawOutline { get; set; } = false;
        private Pen outlinePen;

        [Description("Darken on Disable"), Category("Data")]
        public bool UseDisableColor { get; set; } = true;

        public bool IsHovered;
        public bool IsPressed;

        private SolidBrush primaryBrush;
        private SolidBrush highlightBackColorHighlightBrush;
        private SolidBrush pressedBackColorBrush;
        private SolidBrush disabledBackColorBrush;

        public UtinniButtonBase()
        {
            SetBackColors(Colors.Primary());
        }

        public UtinniButtonBase(Color hoverColor)
        {
            SetBackColors(hoverColor);
        }

        public UtinniButtonBase(Color backColor, Color hoverColor)
        {
            SetBackColors(backColor, hoverColor);
        }

        public void SetBackColors(Color hoverColor)
        {
            SetBackColors(Colors.Primary(), hoverColor);
        }

        public void SetBackColors(Color backColor, Color hoverColor)
        {
            primaryBrush = new SolidBrush(backColor);
            highlightBackColorHighlightBrush = new SolidBrush(ThemeUtility.ScaleColor(hoverColor, Colors.HighlightScalar)); // ToDo this shouldn't use the scale
            pressedBackColorBrush = new SolidBrush(ThemeUtility.ScaleColor(hoverColor, Colors.PressedScalar));
            disabledBackColorBrush = new SolidBrush(ThemeUtility.ScaleColor(hoverColor, Colors.DisabledScalar));

            outlinePen = new Pen(Colors.ControlBorder(), 1);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            // Draw the main rect
            if (IsHovered && !IsPressed && Enabled)
            {
                e.Graphics.FillRectangle(highlightBackColorHighlightBrush, 0, 0, Width, Height);
            }
            else if (IsHovered && IsPressed && Enabled)
            {
                e.Graphics.FillRectangle(pressedBackColorBrush, 0, 0, Width, Height);
            }
            else if (!Enabled && UseDisableColor)
            {
                e.Graphics.FillRectangle(disabledBackColorBrush, 0, 0, Width, Height);
            }
            else
            {
                e.Graphics.FillRectangle(primaryBrush, 0, 0, Width, Height);
            }

            // Draw the outline
            if (DrawOutline)
            {
                e.Graphics.DrawRectangle(outlinePen, 0, 0, Width - 1, Height - 1);
            }
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            IsPressed = true;
            Invalidate();

            base.OnMouseDown(e);
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            IsPressed = false;
            Invalidate();

            base.OnMouseUp(e);
        }

        protected override void OnMouseEnter(EventArgs e)
        {
            IsHovered = true;
            Invalidate();

            base.OnMouseEnter(e);
        }

        protected override void OnMouseLeave(EventArgs e)
        {
            IsHovered = false;
            Invalidate();

            base.OnMouseLeave(e);
        }

        protected override void OnEnabledChanged(EventArgs e)
        {
            base.OnEnabledChanged(e);

            if (Enabled)
            {
                ForeColor = Colors.Font();
            }
            else
            {
                ForeColor = Colors.FontDisabled();
            }
        }
    }
}
