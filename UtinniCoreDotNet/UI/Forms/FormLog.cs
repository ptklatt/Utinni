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
using System.Text;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;
using UtinniCoreDotNet.Utility;

namespace UtinniCoreDotNet.UI.Forms
{
    public partial class FormLog : UtinniForm
    {
        public FormLog()
        {
            InitializeComponent();
            lbLog.BackColor = Colors.Primary();
            lbLog.ForeColor = Colors.Font();
            lbLog.BorderStyle = BorderStyle.None;

            Log.AddOuputSinkCallback(OnOutputSinkCallback);
            UpdateListboxItems();
        }

        private void FormLog_FormClosing(object sender, FormClosingEventArgs e)
        {
            Log.RemoveOuputSinkCallback(OnOutputSinkCallback);
        }

        private bool UpdateListboxItems() // Returns true if there is a count difference between the listbox and the log message buffer
        {
            int logMsgCount = UtinniCore.Utinni.Log.log.GetMessageBufferCount();
            int msgCountDif = logMsgCount - lbLog.Items.Count;

            if (msgCountDif > 0)
            {
                int startIdx = logMsgCount - msgCountDif;
                for (int i = 0; i < msgCountDif; i++)
                {
                    lbLog.Items.Add(UtinniCore.Utinni.Log.log.GetMessageAt(startIdx + i));
                }
                lbLog.TopIndex = lbLog.Items.Count - 1;

                return true;
            }

            return false;
        }

        private void OnOutputSinkCallback(string msg)
        {
            if (lbLog.Visible)
            {
                lbLog.BeginInvoke((Action)(() =>
                {
                    if (!UpdateListboxItems())
                    {
                        lbLog.Items.Add(msg);
                        lbLog.TopIndex = lbLog.Items.Count - 1;
                    }
                }));
            }
        }

        private void lbLog_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Modifiers == Keys.Control && e.KeyCode == Keys.C)
            {

                StringBuilder sb = new StringBuilder();
                foreach (var selectedItem in lbLog.SelectedItems)
                {
                    sb.Append(selectedItem.ToString());
                }

                Clipboard.SetText(sb.ToString());
            }
        }

    }
}
