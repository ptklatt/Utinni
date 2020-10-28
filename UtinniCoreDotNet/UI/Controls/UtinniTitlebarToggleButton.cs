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
