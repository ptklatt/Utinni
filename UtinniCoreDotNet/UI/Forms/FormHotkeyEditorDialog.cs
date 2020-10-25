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
            base.Text = hotkey.Name;

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
