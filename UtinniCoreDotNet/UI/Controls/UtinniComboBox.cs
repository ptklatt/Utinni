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
    public class UtinniComboBox : ComboBox
    {
        [Description("Draw Outline"), Category("Data")]
        public bool DrawOutline { get; set; } = true;
        private Pen outlinePen;
        private Pen outlineHoverPen;

        public bool IsHovered;

        private SolidBrush fontBrush;
        private Pen fontPen;

        private SolidBrush backgroundBrush;
        private SolidBrush arrowBackgroundBrush;

        public UtinniComboBox()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw | ControlStyles.UserPaint, true);

            base.BackColor = Colors.Primary();
            this.DropDownStyle = ComboBoxStyle.DropDownList;
            this.DrawMode = DrawMode.OwnerDrawFixed;
            UpdateColors();
        }

        private void UpdateColors()
        {
            ForeColor = Colors.Font();
            fontBrush = new SolidBrush(ForeColor);
            fontPen = new Pen(ForeColor, 1);

            outlinePen = new Pen(Colors.ControlBorder(), 1);
            outlineHoverPen = new Pen(Colors.Secondary(), 1);

            backgroundBrush = new SolidBrush(Colors.PrimaryHighlight());
            arrowBackgroundBrush = new SolidBrush(Colors.Secondary());
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            e.Graphics.Clear(Colors.Primary());

            // Visual workaround for the height being 21 for some reason, this way it'll only visibly be 20 -- ToDo fix proper in the future
            e.Graphics.FillRectangle(backgroundBrush,0, 0, Width, Height - 1 );

            // Draw arrow background
            e.Graphics.FillRectangle(arrowBackgroundBrush, Width - 17, 0, 17, Height - 1);

            // Draw downward arrow
            e.Graphics.DrawLine(fontPen, Width - 11, 9, Width - 7, 9);
            e.Graphics.DrawLine(fontPen, Width - 10, 10, Width - 8, 10);
            e.Graphics.FillRectangle(fontBrush, Width - 9, 11, 1, 1);

            // Draw selected text
            Rectangle textRect = new Rectangle(2, 2, Width - 40, Height - 4);
            TextRenderer.DrawText(e.Graphics, Text, Font, textRect, ForeColor, TextFormatFlags.Left | TextFormatFlags.VerticalCenter);

            if (IsHovered)
            {
                e.Graphics.DrawRectangle(outlineHoverPen, 0, 0, Width - 1, Height - 2);
            }
            else if (DrawOutline)
            {
                e.Graphics.DrawRectangle(outlinePen, 0, 0, Width - 1, Height - 2);
            }
        }

        protected override void OnDrawItem(DrawItemEventArgs e)
        {
            e.DrawBackground();

            if (Items.Count > 0 && e.Index >= 0)
            {
                e.Graphics.DrawString(Items[e.Index].ToString(), Font, fontBrush, e.Bounds.X, e.Bounds.Y);
            }
        }

        protected override void OnMouseHover(EventArgs e)
        {
            if (!IsHovered)
            {
                IsHovered = true;
                Invalidate();
            }
            base.OnMouseHover(e);
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

        protected override void OnLostFocus(EventArgs e)
        {
            IsHovered = false;

            base.OnLostFocus(e);
        }

        protected override void OnEnabledChanged(EventArgs e)
        {
            base.OnEnabledChanged(e);

            if (Enabled)
            {
                ForeColor = Colors.Font();
                arrowBackgroundBrush = new SolidBrush(Colors.Secondary());
            }
            else
            {
                ForeColor = Colors.FontDisabled();
                arrowBackgroundBrush = new SolidBrush(ThemeUtility.ScaleColor(Colors.Secondary(), Colors.DisabledScalar));
            }

            fontPen = new Pen(ForeColor, 1);
            fontBrush = new SolidBrush(ForeColor);
        }
    }
}
