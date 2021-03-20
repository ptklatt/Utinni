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
                        hotkeyManager.ProcessInput(e.Modifiers, e.KeyCode, HasFocus);
                    }
                }
            }
        }

    }
}
