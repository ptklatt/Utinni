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

using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniContextMenuStripRenderer : ToolStripProfessionalRenderer
    {
        public UtinniContextMenuStripRenderer() : base(new UtinniContextMenuStripColorTable()) { }
        public UtinniContextMenuStripRenderer(Color hoverColor) : base(new UtinniContextMenuStripColorTable(hoverColor)) { }

        protected override void OnRenderToolStripBorder(ToolStripRenderEventArgs e)
        {
            // Override to remove the border -- ToDo Potentially add sides + bottom border with Colors.Secondary()
        }
    }

    public class UtinniContextMenuStripColorTable : ProfessionalColorTable
    {
        private readonly Color hoverBackColor;

        public UtinniContextMenuStripColorTable()
        {
            hoverBackColor = ThemeUtility.ScaleColor(Colors.Secondary(), Colors.HighlightScalar);
        }

        public UtinniContextMenuStripColorTable(Color hoverColor)
        {
            hoverBackColor = hoverColor;
        }

        public override Color MenuItemSelected
        {
            get { return hoverBackColor; }
        }
        public override Color MenuItemSelectedGradientBegin
        {
            get { return hoverBackColor; }
        }
        public override Color MenuItemSelectedGradientEnd
        {
            get { return hoverBackColor; }
        }

        public override Color MenuItemBorder
        {
            get { return hoverBackColor; }
        }
    }
}
