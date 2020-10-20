using System;
using System.Diagnostics;
using System.Windows.Forms;
using UtinniCore.ImguiImpl;
using UtinniCore.Utinni;
using UtinniCoreDotNet.Hotkeys;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.Utility;

namespace UtinniCoreDotNet.UI.Controls
{
    public class PanelGame : Panel
    {
        protected override void WndProc(ref Message m)
        {
            IntPtr swgWndProc = new IntPtr(0x00AA0970);
            Native.CallWindowProc(swgWndProc, m.HWnd, m.Msg, m.WParam, m.LParam); // Call and handle SWG's WndProc
            base.WndProc(ref m);
        }

        public bool HasFocus;
        private bool isCursorVisible;

        private readonly PluginLoader pluginLoader;

        public PanelGame(PluginLoader pluginLoader)
        {
            base.Dock = DockStyle.Fill;
            base.AllowDrop = true;

            Disposed += PanelGame_Disposed;

            MouseEnter += PanelGame_MouseEnter;
            MouseLeave += PanelGame_MouseLeave;
            MouseMove += PanelGame_MouseMove;

            GotFocus += PanelGame_GotFocus;
            LostFocus += PanelGame_LostFocus;

            KeyDown += PanelGame_KeyDown;

            Layout += PanelGame_Layout;

            GameDragDropEventHandlers.Initialize(this);

            this.pluginLoader = pluginLoader;
        }

        private void PanelGame_GotFocus(object sender, EventArgs e)
        {
            ResumeGameInput();
        }

        private void PanelGame_LostFocus(object sender, EventArgs e)
        {
            SuspendGameInput();
        }

        private void PanelGame_Layout(object sender, LayoutEventArgs e)
        {
            Client.SetHwnd(Handle);
            Client.SetHInstance(Process.GetCurrentProcess().Handle);
        }

        private void PanelGame_Disposed(object sender, EventArgs e)
        {
            Game.Quit();
        }

        private void PanelGame_MouseEnter(object sender, EventArgs e)
        {
            Focus();
        }

        private void PanelGame_MouseLeave(object sender, EventArgs e)
        {
            SuspendGameInput();
        }

        private void PanelGame_MouseMove(object sender, MouseEventArgs e)
        {
            if (imgui_impl.IsInternalUiHovered() && !isCursorVisible)
            {
                ShowCursor();
                SuspendGameInput();
            }
            else if (!imgui_impl.IsInternalUiHovered() && isCursorVisible)
            {
                ResumeGameInput();
                HideCursor();
            }
        }

        private void ResumeGameInput()
        {
            Client.ResumeInput();
            HideCursor();
            HasFocus = true;
        }

        private void SuspendGameInput()
        {
            ShowCursor();
            Client.SuspendInput();
            HasFocus = false;
        }

        int cursorHideCount; // ToDo Implement proper, hacky workaround when a single Cursor.Show() doesn't show the Cursor
        private void HideCursor()
        {
            Cursor.Hide();
            cursorHideCount++;
            isCursorVisible = false;
        }

        private void ShowCursor()
        {
            for (int i = 0; i < cursorHideCount; i++)
            {
                Cursor.Show();
            }
            cursorHideCount = 0;
            isCursorVisible = true;
        }

        private void PanelGame_KeyDown(object sender, KeyEventArgs e)
        {
            foreach (IPlugin plugin in pluginLoader.Plugins)
            {
                IEditorPlugin editorPlugin = (IEditorPlugin)plugin;
                if (editorPlugin != null)
                {
                    HotkeyManager hotkeyManager = editorPlugin.GetHotkeyManager();

                    if (hotkeyManager != null && hotkeyManager.OnGameFocusOnly)
                    {
                        hotkeyManager.ProcessInput(e.Modifiers, e.KeyCode);
                    }
                }
            }
        }

    }
}
