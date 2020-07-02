using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using UtinniCore.ImguiImplementation;
using UtinniCore.Utinni;
using UtinniCoreDotNet.Utility;

namespace UtinniCoreDotNet
{
    public class PanelGame : Panel
    {
        [DllImport("user32.dll")]
        static extern IntPtr CallWindowProc(IntPtr lpPrevWndFunc, IntPtr hWnd, int Msg, IntPtr wParam, IntPtr lParam);

        protected override void WndProc(ref Message m)
        {
            IntPtr swgWndProc = new IntPtr(0x00AA0970);

            CallWindowProc(swgWndProc, m.HWnd, m.Msg, m.WParam, m.LParam); // Call and handle SWG's WndProc

            base.WndProc(ref m);
        }

        public bool HasFocus;
        private bool isCursorVisible; 

        public PanelGame()
        {
            Dock = DockStyle.Fill;

            Disposed += PanelGame_Disposed;

            GotFocus += PanelGame_GotFocus;
            LostFocus += PanelGame_LostFocus;

            MouseEnter += PanelGame_MouseEnter;
            MouseLeave += PanelGame_MouseLeave;
            MouseMove += PanelGame_MouseMove;
            MouseHover += PanelGame_MouseHover;
            MouseUp += PanelGame_MouseUp;
            MouseDown += PanelGame_MouseDown;
            
            Client.SetHwnd(Handle);
            Client.SetHInstance(Process.GetCurrentProcess().Handle);
        }

        private void PanelGame_Disposed(object sender, EventArgs e)
        {
            Game.Quit();
        }

        private void PanelGame_GotFocus(object sender, EventArgs e)
        {

        }

        private void PanelGame_LostFocus(object sender, EventArgs e)
        {

        }

        private void PanelGame_MouseEnter(object sender, EventArgs e)
        {
            isCursorVisible = false;
            Client.ResumeInput();
            Cursor.Hide();
            HasFocus = true;
        }

        private void PanelGame_MouseLeave(object sender, EventArgs e)
        {
            isCursorVisible = true;
            Client.SuspendInput();
            Cursor.Show();
            HasFocus = false;
        }

        private void PanelGame_MouseHover(object sender, EventArgs e)
        {
          
        }


        private void PanelGame_MouseMove(object sender, MouseEventArgs e)
        {
            if (imgui_implementation.IsInternalUiHovered() && !isCursorVisible)
            {
                isCursorVisible = true;
                Cursor.Show();
            }
            else if (!imgui_implementation.IsInternalUiHovered() && isCursorVisible)
            {
                isCursorVisible = false;
                Cursor.Hide();
            }
        }


        private void PanelGame_MouseUp(object sender, MouseEventArgs e)
        {

        }

        private void PanelGame_MouseDown(object sender, MouseEventArgs e)
        {

        }

    }
}
