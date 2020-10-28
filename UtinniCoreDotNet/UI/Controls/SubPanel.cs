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
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public partial class SubPanel : UserControl
    {
        public readonly string CheckboxPanelText;
        public readonly bool IsOpenByDefault;
        private readonly bool forceWidth;
        private const int width = 417;

        public SubPanel()
        {
            Width = width;
            base.BackColor = Colors.Primary();
            base.ForeColor = Colors.Font();
        }

        public SubPanel(bool forceWidth = true) : this()
        {
            this.forceWidth = forceWidth;
        }

        public SubPanel(string name, bool isOpenByDefault = false, bool forceWidth = true) : this(forceWidth)
        {
            CheckboxPanelText = name;
            IsOpenByDefault = isOpenByDefault;
        }
        
        // This is needed because the Visual Studio Designer handles inheritance incorrectly.
        // Overriding this, makes sure the width stays the same, to fit correctly into the plugin control area
        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            if (forceWidth)
            {
                Width = width;
            }
        }
    }
}
