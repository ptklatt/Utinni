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
using System.Collections.Generic;
using System.Security.Permissions;
using System.Threading;
using System.Windows.Forms;
using UtinniCoreDotNet.Callbacks;
using UtinniCoreDotNet.Hotkeys;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.Properties;
using UtinniCoreDotNet.UI.Controls;
using UtinniCoreDotNet.UI.Theme;
using UtinniCoreDotNet.UndoRedo;
using UtinniCoreDotNet.Utility;
using Point = System.Drawing.Point;

namespace UtinniCoreDotNet.UI.Forms
{
    public partial class FormMain : UtinniForm
    {
        private readonly PanelGame game;
        private readonly UndoRedoManager undoRedoManager;
        private readonly HotkeyManager formHotkeyManager = new HotkeyManager(true);

        private readonly UtinniTitlebarDropDownButton tbddWindows;
        private readonly UndoRedoTitlebarButton tbbtnUndo;
        private readonly UndoRedoTitlebarButton tbbtnRedo;

        private readonly List<IEditorPlugin> editorPlugins = new List<IEditorPlugin>();
        private readonly List<SubPanelContainer> subContainers = new List<SubPanelContainer>();
        private readonly List<Form> formChildren = new List<Form>();

        [SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
        protected override void WndProc(ref Message m)
        {
            if (m.Msg == Native.WM_SYSCOMMAND)
            {
                int command = m.WParam.ToInt32() & 0xFFF0;

                if (command == Native.SC_MINIMIZE || command == Native.SC_RESTORE || command == Native.SC_MAXIMIZE)
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

            Width = UtinniCore.Utinni.utinni.GetConfig().GetInt("Editor", "width");
            Height = UtinniCore.Utinni.utinni.GetConfig().GetInt("Editor", "height");

            undoRedoManager = new UndoRedoManager(OnUpdateCommandsCallback, OnUndo, OnRedo);

            foreach (IPlugin plugin in pluginLoader.Plugins)
            {
                IEditorPlugin editorPlugin = (IEditorPlugin) plugin;
                if (editorPlugin != null)
                {
                    editorPlugins.Add(editorPlugin);
                }
            }

            game = new PanelGame(pluginLoader);
            pnlGame.Controls.Add(game);

            pnlPlugins.BackColor = Colors.Primary();
            pnlPlugins.ForeColor = Colors.Font();

            tbddWindows = new UtinniTitlebarDropDownButton("Open...");

            ToolStripDropDownItem tsddItem = new ToolStripMenuItem("Log");
            tsddItem.Click += (sender, args) =>
            {
                OpenLogWindow();
            };

            tbddWindows.Menu.Items.Add(tsddItem);

            CreatePluginControls();

            tbbtnUndo = new UndoRedoTitlebarButton(this, "Undo", Resources.undo, undoRedoManager.Undo);
            tbbtnRedo = new UndoRedoTitlebarButton(this, "Redo", Resources.redo, undoRedoManager.Redo);

            tbbtnUndo.Click += TbbtnUndo_Click;
            tbbtnRedo.Click += TbbtnRedo_Click;

            LeftTitleBarButtons.Add(tbddWindows);
            LeftTitleBarButtons.Add(tbbtnUndo);
            LeftTitleBarButtons.Add(tbbtnRedo);

            formHotkeyManager.Add(new Hotkey("Undo", "Undo", "Control + Z", undoRedoManager.Undo, true));
            formHotkeyManager.Add(new Hotkey("Redo", "Redo", "Control + Y", undoRedoManager.Redo, true));
            formHotkeyManager.Add(new Hotkey("ToggleUI", "Toggle UI", "Shift + Oemtilde", ToggleFullWindowGame, true));

            formHotkeyManager.CreateSettings();
            formHotkeyManager.Load();

            InitializeEditorCallbacks(); // Initialize callbacks that are purely editor related


            UtinniTitlebarButton tbbtnHotkeyEditor = new UtinniTitlebarButton("Hotkey Editor");
            tbbtnHotkeyEditor.Click += (sender, args) =>
            {
                FormHotkeyEditor form = new FormHotkeyEditor(formHotkeyManager, editorPlugins);
                form.Show();
            };

            RightTitleBarButtons.Add(tbbtnHotkeyEditor);

            if (UtinniCore.Utinni.utinni.GetConfig().GetBool("Editor", "autoOpenLogWindow"))
            {
                OpenLogWindow();
                this.BringToFront();
                this.Focus();
            }
        }

        private void FormMain_Resize(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Minimized || WindowState == FormWindowState.Normal || WindowState == FormWindowState.Maximized)
            {
                UtinniCore.DirectX.directx9.BlockPresent(false); // Restore Present, which we blocked in the WndProc catch
            }
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            // Handle the form HotkeyManager first
            if (game.HasFocus && formHotkeyManager.OnGameFocusOnly)
            {
                formHotkeyManager.ProcessInput(keyData & Keys.Modifiers, keyData & Keys.KeyCode, game.HasFocus);
            }

            // Then handle the each plugins HotkeyManager
            foreach (IEditorPlugin editorPlugin in editorPlugins)
            {
                HotkeyManager hotkeyManager = editorPlugin.GetHotkeyManager();
                if (hotkeyManager == null)
                {
                    continue;
                }

                if (!hotkeyManager.OnGameFocusOnly)
                {
                    hotkeyManager.ProcessInput(keyData & Keys.Modifiers, keyData & Keys.KeyCode, game.HasFocus);
                }
                else if (game.HasFocus && hotkeyManager.OnGameFocusOnly)
                {
                    hotkeyManager.ProcessInput(keyData & Keys.Modifiers, keyData & Keys.KeyCode, game.HasFocus);
                }
            }

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

        private void TbbtnUndo_Click(object sender, EventArgs e)
        {
            if (tbbtnUndo.IsDropDownClickAreaPressed)
            {
                tbbtnUndo.DropDown.Display(undoRedoManager.UndoCommands);
            }
            else
            {
                undoRedoManager.Undo();
            }
        }

        private void TbbtnRedo_Click(object sender, EventArgs e)
        {
            if (tbbtnRedo.IsDropDownClickAreaPressed)
            {
                tbbtnRedo.DropDown.Display(undoRedoManager.RedoCommands);
            }
            else
            {
                undoRedoManager.Redo();
            }
        }

        private void OnUpdateCommandsCallback()
        {
            tbbtnUndo.Enabled = undoRedoManager.UndoCommands.Count > 0;
            tbbtnRedo.Enabled = undoRedoManager.RedoCommands.Count > 0;
        }

        private void OnUndo()
        {
            tbbtnUndo.Enabled = undoRedoManager.UndoCommands.Count > 0;
            tbbtnRedo.Enabled = undoRedoManager.RedoCommands.Count > 0;
        }

        private void OnRedo()
        {
            tbbtnUndo.Enabled = undoRedoManager.UndoCommands.Count > 0;
            tbbtnRedo.Enabled = undoRedoManager.RedoCommands.Count > 0;
        }

        private int cmbPanelsPreviousIndex = -1;
        private void cmbPanels_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbPanelsPreviousIndex != cmbPanels.SelectedIndex)
            {
                pnlPlugins.Controls.RemoveAt(1); // cmbPanels is index 0, the flp is at index 1
                pnlPlugins.Controls.Add(subContainers[cmbPanels.SelectedIndex]);
                cmbPanelsPreviousIndex = cmbPanels.SelectedIndex;
            }
            pnlPlugins.Focus(); // 'Hack' to prevent the highlighting of the ComboBox text after a select was made
            // ToDo see if there is a way to remove the highlight flashing
        }

        private void CreatePluginControls()
        {
            pnlPlugins.SuspendLayout();

            SubPanelContainer defaultContainer = new SubPanelContainer("");
            subContainers.Add(defaultContainer);
            cmbPanels.Items.Add("Main Controls");
            defaultContainer.SuspendLayout();

            string defaultPanelName = UtinniCore.Utinni.utinni.GetConfig().GetString("Editor", "defaultPluginPanel");
            int defaultPanelIndex = 0;

            foreach (IEditorPlugin editorPlugin in editorPlugins)
            {
                undoRedoManager.AddUndoCommand(editorPlugin);

                Log.Info("Editor Plugin: [" + editorPlugin.Information.Name + "] loaded");

                var subPanels = editorPlugin.GetSubPanels();
                if (subPanels != null)
                {
                    foreach (var subPanel in subPanels)
                    {
                        defaultContainer.Controls.Add(new CollapsiblePanel(subPanel, subPanel.CheckboxPanelText));
                    }
                }

                var standalonePanels = editorPlugin.GetStandalonePanels();
                if (standalonePanels != null)
                {
                    foreach (var panelContainer in editorPlugin.GetStandalonePanels())
                    {
                        subContainers.Add(panelContainer);
                        string cmbText = editorPlugin.Information.Name + " - " + panelContainer.Text;
                        cmbPanels.Items.Add(cmbText);

                        if (cmbText == defaultPanelName)
                        {
                            defaultPanelIndex = cmbPanels.Items.Count - 1;
                        }
                    }
                }

                var forms = editorPlugin.GetForms();
                if (forms != null)
                {
                    foreach (IEditorForm iEditorForm in forms)
                    {
                        ToolStripDropDownItem tsddItem = new ToolStripMenuItem(editorPlugin.Information.Name + " - " + iEditorForm.GetName());
                        tsddItem.Click += (sender, args) =>
                        {
                            Form form = iEditorForm.Create(editorPlugin, formChildren);
                            if (form != null)
                            {
                                form.Closing += (o, eventArgs) =>
                                {
                                    formChildren.Remove(form);
                                };
                            }
                        };

                        tbddWindows.Menu.Items.Add(tsddItem);
                    }
                }
            }
            defaultContainer.ResumeLayout();

            cmbPanels.SelectedIndex = defaultPanelIndex;
            cmbPanels.SelectedIndexChanged += cmbPanels_SelectedIndexChanged;
            pnlPlugins.Controls.Add(subContainers[defaultPanelIndex]);

            pnlPlugins.ResumeLayout();
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

        private void InitializeEditorCallbacks()
        {
            ImGuiCallbacks.Initialize();
        }

        private void OpenLogWindow()
        {
            // Check if the log is already open
            foreach (Form form in formChildren)
            {
                if (form.GetType() == typeof(FormLog)) // ToDo fix this, it's broken since using UtinniForm
                {
                    form.Activate();
                    return;
                }
            }

            // If not, create a new one
            FormLog formLog = new FormLog();
            formLog.Show();
            formChildren.Add(formLog);
            formLog.Closing += (o, eventArgs) =>
            {
                formChildren.Remove(formLog);
            };
        }

        private void tsbtnToggleUI_Click(object sender, EventArgs e)
        {
            ToggleFullWindowGame();
        }

    }
}
