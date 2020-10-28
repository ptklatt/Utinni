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
    public class UtinniTitlebarDropDownButton : UtinniTitlebarButton
    {
        [Description("ContextMenu"), Category("Data")]
        public UtinniContextMenuStrip Menu { get; set; } = null;

        [Description("Use the entire Button for Menu"), Category("Data")]
        public bool UseEntireButtonForMenu { get; set; } = true;

        private const int dropDownClickArea = 15;

        private SolidBrush fontBrush;
        private Pen fontPen;

        public UtinniTitlebarDropDownButton(string text) : base(text)
        {
            Width += dropDownClickArea + 3;
            Setup();
        }

        public UtinniTitlebarDropDownButton(Bitmap image) : base(image)
        {
            Setup();
        }

        public UtinniTitlebarDropDownButton(Bitmap image, Color hoverBackColor) : base(image, hoverBackColor)
        {
            Setup();
        }

        private void Setup()
        {
            UpdateColors();
            Menu = new UtinniContextMenuStrip();
        }

        private void UpdateColors()
        {
            fontBrush = new SolidBrush(Colors.Font());
            fontPen = new Pen(Colors.Font(), 1);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            // Draw the arrow
            e.Graphics.DrawLine(fontPen, Width - 11, 15, Width - 7, 15);
            e.Graphics.DrawLine(fontPen, Width - 10, 16, Width - 8, 16);
            e.Graphics.FillRectangle(fontBrush, Width - 9, 17, 1, 1);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            if (Menu != null && e.Button == MouseButtons.Left && (UseEntireButtonForMenu || e.X >= Width - dropDownClickArea))
            {
                Menu.Show(this, 0, Height);
            }
            else
            {
                base.OnMouseDown(e);
            }
        }

        protected override void OnForeColorChanged(EventArgs e)
        {
            base.OnForeColorChanged(e);
            fontPen = new Pen(ForeColor, 1);
            fontBrush = new SolidBrush(ForeColor);
        }
    }
}
