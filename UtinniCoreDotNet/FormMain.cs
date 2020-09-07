using System;
using System.Collections.Generic;
using System.Security.Permissions;
using System.Threading;
using System.Windows.Forms;
using UtinniCoreDotNet.Callbacks;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.UI;
using UtinniCoreDotNet.UndoRedo;
using UtinniCoreDotNet.Utility;
using Point = System.Drawing.Point;

namespace UtinniCoreDotNet
{
    public partial class FormMain : Form
    {
        private readonly PanelGame game;
        private readonly PluginLoader pluginLoader;
        private readonly UndoRedoManager undoRedoManager;

        private const int WM_SYSCOMMAND = 0x0112;
        private const int SC_MINIMIZE = 0xF020;
        private const int SC_RESTORE = 0xF120;
        private const int SC_MAXIMIZE = 0xF030;

        [SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
        protected override void WndProc(ref Message m)
        {
            if (m.Msg == WM_SYSCOMMAND)
            {
                int command = m.WParam.ToInt32() & 0xFFF0;

                if (command == SC_MINIMIZE || command == SC_RESTORE || command == SC_MAXIMIZE)
                {
                    UtinniCore.DirectX.directx9.BlockPresent(true);

                    // Due to SWG's thread and this one not being in sync, we need to wait until Present is actually blocked.
                    // ToDo: Find better solution in the future
                    while (!UtinniCore.DirectX.directx9.IsPresentBlocked())
                    {
                        Thread.Sleep(1);
                    }

                }
            }

            base.WndProc(ref m);
        }

        public FormMain(PluginLoader pluginLoader)
        {
            InitializeComponent();
            undoRedoManager = new UndoRedoManager();
            this.pluginLoader = pluginLoader;

            CreatePluginPanels();

            game = new PanelGame();
            pnlGame.Controls.Add(game);

            InitializeEditorCallbacks(); // Initialize callbacks that are purely editor related
        }

        private void FormMain_Resize(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Minimized || WindowState == FormWindowState.Normal || WindowState == FormWindowState.Maximized)
            {
                UtinniCore.DirectX.directx9.BlockPresent(false); // Restore Present, which we blocked in the WndProc catch
            }
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

        private void ToggleFullWindowGame() // ToDo see if there is a way to prevent the flickering on switch
        {
            SuspendLayout();
            if (game.Parent == pnlGame)
            {
                pnlGame.Controls.Remove(game);
                Controls.Add(game);
                game.BringToFront();
            }
            else
            {
                Controls.Remove(game);
                pnlGame.Controls.Add(game);
            }
            ResumeLayout();
        }

        private void tsbtnUndo_Click(object sender, EventArgs e)
        {
            undoRedoManager.Undo();
        }

        private void tsbtnRedo_Click(object sender, EventArgs e)
        {
            undoRedoManager.Redo();
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {

        }

        private void CreatePluginPanels()
        {
            pnlPlugins.SuspendLayout();
            flpPlugins.SuspendLayout();
            foreach (var plugin in pluginLoader.Plugins)
            {
                // If the plugin is an IEditorPlugin, add it as a CollapsiblePanel with the plugins name as text
                IEditorPlugin editorPlugin = (IEditorPlugin)plugin;
                if (editorPlugin != null)
                {
                    undoRedoManager.AddUndoCommand(editorPlugin);

                    Log.Info("Editor Plugin: [" + editorPlugin.Information.Name + "] loaded");

                    // ToDo implement main panel switching

                    if (editorPlugin.GetSubPanels() != null)
                    {
                        foreach (var subPanel in editorPlugin.GetSubPanels())
                        {
                            flpPlugins.Controls.Add(new CollapsiblePanel(subPanel, subPanel.CheckboxPanelText));
                        }
                    }

                    if (editorPlugin.GetStandalonePanels() != null)
                    {
                        foreach (var subPanel in editorPlugin.GetStandalonePanels())
                        {
                            flpPlugins.Controls.Add(new CollapsiblePanel(subPanel, subPanel.CheckboxPanelText));
                        }
                    }

                }
            }
            flpPlugins.ResumeLayout();
            pnlPlugins.ResumeLayout();
        }

        private void InitializeEditorCallbacks()
        {
            ImGuiCallbacks.Initialize();
        }
    }
}
