using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.Hotkeys;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.UI.Controls;

namespace UtinniCoreDotNet.UI.Forms
{
    public partial class FormHotkeyEditor : UtinniForm
    {
        private bool hasChanges;
        public bool HasChanges
        {
            get { return hasChanges; }
            set
            {
                hasChanges = value;
                btnSave.Enabled = hasChanges;
            }
        }

        private readonly HotkeyManager mainHotkeyManager;
        private readonly List<IEditorPlugin> editorPlugins;
        private readonly SubPanelContainer spnlContainer = new SubPanelContainer("Hotkeys");

        public FormHotkeyEditor(HotkeyManager mainHotkeyManager, List<IEditorPlugin> editorPlugins)
        {
            InitializeComponent();
            this.mainHotkeyManager = mainHotkeyManager;
            this.editorPlugins = editorPlugins;

            spnlContainer.Dock = DockStyle.Fill;

            CreateControls();
        }

        private void CreateControls()
        {
            spnlContainer.Controls.Add(CreatePanel("Utinni", mainHotkeyManager));

            foreach (IEditorPlugin editorPlugin in editorPlugins)
            {
                HotkeyManager hotkeyManager = editorPlugin.GetHotkeyManager();

                if (hotkeyManager != null)
                {
                    spnlContainer.Controls.Add(CreatePanel(editorPlugin.Information.Name, hotkeyManager));
                }
            }

            Controls.Add(spnlContainer);
            spnlContainer.Size = new Size(700, 546);
            spnlContainer.Anchor = AnchorStyles.Bottom | AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
        }

        private CollapsiblePanel CreatePanel(string text, HotkeyManager hotkeyManager)
        {
            SubPanel spnl = new SubPanel("", true, false);

            int yOffset = 3;
            foreach (var hotkeyEntry in hotkeyManager.Hotkeys)
            {
                UtinniLabel lbl = new UtinniLabel
                {
                    Text = hotkeyEntry.Key, 
                    Location = new Point(0, yOffset),
                    Width = 350
                };

                UtinniButton btn = new UtinniButton
                {
                    Width = 350,
                    Text = hotkeyEntry.Value.GetKeyComboString(),
                    Location = new Point(350, yOffset),
                };

                btn.Click += (sender, args) =>
                {
                    // ToDo add popup which lets you set it, with an accept button and then if accepted, sets the text

                    // ToDo also set HasChanges with the result of accept or decline
                };

                spnl.Controls.Add(lbl);
                spnl.Controls.Add(btn);

                yOffset += 23;
            }
            spnl.Height = yOffset + 23;

            var cpnl = new CollapsiblePanel(spnl, text, 700)
            {
                Margin = new Padding(0, 3, 0, 3),
                Height = spnl.Height + 3
            };

            return cpnl;
        }

        private void btnSave_Click(object sender, System.EventArgs e)
        {
            DialogResult confirmResult = MessageBox.Show("Are you sure you want to Save?", "Confirm Save", MessageBoxButtons.OKCancel);
            if (confirmResult == DialogResult.Yes)
            {
                mainHotkeyManager.Save();

                foreach (IEditorPlugin editorPlugin in editorPlugins)
                {
                    HotkeyManager hotkeyManager = editorPlugin.GetHotkeyManager();

                    if (hotkeyManager != null)
                    {
                        hotkeyManager.Save();
                    }
                }
            }
        }
    }
}
