using System;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using UtinniCoreDotNet.Utility;

namespace UtinniCoreDotNet.UI.Forms
{
    public partial class FormLog : Form
    {
        public FormLog()
        {
            InitializeComponent();

            Log.AddOuputSinkCallback(OnOutputSinkCallback);
        }

        private void FormLog_Load(object sender, EventArgs e)
        {
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

                // There seems to be an issue with this form seeing the STAThread on main.cs,
                // this is a workaround. ToDo try and figure out the issue in the future
                Thread STAThread = new Thread(() =>
                {
                    Clipboard.SetText(sb.ToString());
                });

                STAThread.SetApartmentState(ApartmentState.STA);
                STAThread.Start();
                STAThread.Join();
            }
        }

    }
}
