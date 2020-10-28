/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniToggle : CheckBox
    {
        [Description("Draw Outline"), Category("Data")]
        public bool DrawOutline { get; set; } = false;
        private Pen outlinePen;

        public bool IsHovered;
        public bool IsPressed;

        private Point togglePosition = new Point(1,  0);

        private const int boxWidth = 60;
        private const int boxHeight = 20;

        private const int toggleWidth = 13;
        private int toggleOffset;

        private int textLength;

        private SolidBrush foreColorBrush;

        private SolidBrush primaryBrush;
        private SolidBrush hoverBackColorHighlightBrush;
        private SolidBrush pressedBackColorBrush;
        private SolidBrush disabledBackColorBrush;

        public UtinniToggle()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw |
                     ControlStyles.UserPaint | ControlStyles.SupportsTransparentBackColor, true);

            Width = boxWidth;
            Height = boxHeight;
            SetBackColors(Colors.PrimaryHighlight());
            foreColorBrush = new SolidBrush(Colors.Font());
        }

        public void SetBackColors(Color primaryColor)
        {
            primaryBrush = new SolidBrush(primaryColor);
            hoverBackColorHighlightBrush = new SolidBrush(ThemeUtility.ScaleColor(primaryColor, Colors.HighlightScalar));
            pressedBackColorBrush = new SolidBrush(ThemeUtility.ScaleColor(primaryColor, Colors.PressedScalar));
            disabledBackColorBrush = new SolidBrush(ThemeUtility.ScaleColor(primaryColor, Colors.DisabledScalar));

            outlinePen = new Pen(Colors.ControlBorder(), 1);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            e.Graphics.Clear(Colors.Primary());

            if (TextAlign == ContentAlignment.MiddleLeft)
            {
                toggleOffset = textLength + 3;
            }
            else
            {
                toggleOffset = 0;
            }

            // Draw the main box
            if (IsHovered && !IsPressed && Enabled)
            {
                e.Graphics.FillRectangle(hoverBackColorHighlightBrush, toggleOffset, 0, boxWidth, boxHeight);
            }
            else if (IsHovered && IsPressed && Enabled)
            {
                e.Graphics.FillRectangle(pressedBackColorBrush, toggleOffset, 0, boxWidth, boxHeight);
            }
            else if (!Enabled)
            {
                e.Graphics.FillRectangle(disabledBackColorBrush, toggleOffset, 0, boxWidth, boxHeight);
            }
            else
            {
                e.Graphics.FillRectangle(primaryBrush, toggleOffset, 0, boxWidth, boxHeight);
            }

            // Draw the outline
            if (DrawOutline)
            {
                e.Graphics.DrawRectangle(outlinePen, toggleOffset, 0, boxWidth - 4, boxHeight - 1);
            }

            OnPaintForeground(e);
        }

        protected virtual void OnPaintForeground(PaintEventArgs e)
        {
            // Draw the toggle
            e.Graphics.FillRectangle(foreColorBrush, togglePosition.X + toggleOffset, togglePosition.Y, toggleWidth, 20);


            // Draw the Text
            Rectangle textRect;
            if (TextAlign == ContentAlignment.MiddleLeft)
            {
                textRect = new Rectangle(0, 0, textLength, ClientRectangle.Height);
            }
            else
            {
                textRect = new Rectangle(boxWidth + 3, 0, textLength, ClientRectangle.Height);
            }

            TextRenderer.DrawText(e.Graphics, Text, Font, textRect, ForeColor);
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

        protected override void OnKeyDown(KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Space)
            {
                IsPressed = true;
                Invalidate();
            }

            base.OnKeyDown(e);
        }

        protected override void OnKeyUp(KeyEventArgs e)
        {
            Invalidate();

            base.OnKeyUp(e);
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

        protected override void OnSizeChanged(EventArgs e)
        {
            UpdateWidth();
        }

        protected override void OnTextChanged(EventArgs e)
        {
            UpdateWidth();
        }

        private void UpdateWidth()
        {
            Size size = TextRenderer.MeasureText(Text, Font);
            textLength = size.Width;
            Width = boxWidth + textLength;
        }

        protected override void OnCheckedChanged(EventArgs e)
        {
            base.OnCheckedChanged(e);

            if (Checked)
            {
                togglePosition = new Point(boxWidth - toggleWidth - 4, 0);
                SetBackColors(Colors.Secondary());
            }
            else
            {
                togglePosition = new Point(1, 0);
                SetBackColors(Colors.PrimaryHighlight());
            }

            Invalidate();
        }

        public override bool AutoSize // AutoSize breaks a lot of things, hacky workaround is to always return/set false
        {
            set { base.AutoSize = false; }
            get { return base.AutoSize; }
        }

    }
}
