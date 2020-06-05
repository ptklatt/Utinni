using System;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.UI;

namespace UtinniCoreDotNet
{
    public partial class FormMain : Form
    {
        private PanelGame game;
        private PluginLoader pluginLoader;

        public FormMain(PluginLoader pluginLoader)
        {
            InitializeComponent();

            this.pluginLoader = pluginLoader;

            foreach (var plugin in pluginLoader.Plugins)
            {
                // If the plugin is an IEditorPlugin, add it as a CollapsiblePanel with the plugins name as text
                IEditorPlugin editorPlugin = (IEditorPlugin)plugin;
                if (editorPlugin != null)
                {
                    flpnlPlugins.Controls.Add(new CollapsiblePanel(editorPlugin.GetControl(), editorPlugin.Information.Name));
                }
            }

            game = new PanelGame();
            pnlGame.Controls.Add(game);
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData) // ToDo figure out how to handle this inside PanelGame potentially
        {
            if (game.HasFocus)
            {
                if (keyData == Keys.Tab)
                {
                    return true;
                }

                return false; // Block key input if the game has focus, to prevent the input firing things inside WinForms
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        private void FormMain_Shown(object sender, EventArgs e)
        {
            Point thisPos = PointToScreen(Point.Empty);
            Cursor.Position = new Point(thisPos.X + 20, thisPos.Y + 20);
        }

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {

        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            MessageBox.Show(UtinniCore.Utinni.utinni.GetConfig().GetString("Launcher", "swgClientName"));
        }
    }
}
