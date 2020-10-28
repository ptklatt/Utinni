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
using UtinniCoreDotNet.Hotkeys;

namespace UtinniCoreDotNet.UI.Forms
{
    public partial class FormHotkeyEditorDialog : UtinniForm
    {
        private readonly Hotkey hotkey;
        public string NewValue = "";

        public FormHotkeyEditorDialog(Hotkey hotkey)
        {
            InitializeComponent();
            base.Text = hotkey.Text;

            this.hotkey = hotkey;
            txtInput.Text = hotkey.GetKeyComboString();
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            txtInput.Text = (keyData & Keys.Modifiers) + " + " + (keyData & Keys.KeyCode);
            return base.ProcessCmdKey(ref msg, keyData);
        }

        private void txtInput_TextChanged(object sender, System.EventArgs e)
        {
            NewValue = txtInput.Text;
        }
    }
}
