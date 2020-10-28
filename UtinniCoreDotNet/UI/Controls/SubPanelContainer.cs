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

using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class SubPanelContainer : FlowLayoutPanel
    {
        public SubPanelContainer(string text)
        {
            InitializeComponent();
            base.BackColor = Colors.Primary();
            base.ForeColor = Colors.Font();
            base.Text = text;
        }

        public SubPanelContainer(string text, SubPanel[] subPanels)
        {
            InitializeComponent();
            base.Text = text;
            SuspendLayout();
            foreach (SubPanel subPanel in subPanels)
            {
                Controls.Add(new CollapsiblePanel(subPanel, subPanel.CheckboxPanelText));
            }
            ResumeLayout();
        }

        private void InitializeComponent()
        {
            Location = new System.Drawing.Point(0, 30);
            AutoSize = true;
            AutoSizeMode = AutoSizeMode.GrowAndShrink;
            MinimumSize = new System.Drawing.Size(420, 0);
            Size = new System.Drawing.Size(420, 0);
            FlowDirection = FlowDirection.TopDown;
            WrapContents = false;
        }
    }
}
