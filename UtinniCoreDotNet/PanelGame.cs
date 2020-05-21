using System;
using System.Diagnostics;
using System.Windows.Forms;
using UtinniCore.Utinni;

namespace UtinniCoreDotNet
{
    public class PanelGame : Panel
    {

        public PanelGame()
        {
            Dock = DockStyle.Fill;

            Disposed += PanelGame_Disposed;
            Enter += PanelGame_Enter;
            Leave += PanelGame_Leave;
            SizeChanged += PanelGame_SizeChanged;

            MouseEnter += PanelGame_MouseEnter;
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

        private void PanelGame_MouseEnter(object sender, EventArgs e)
        {

        }

        private void PanelGame_MouseHover(object sender, EventArgs e)
        {

        }

        private void PanelGame_MouseUp(object sender, MouseEventArgs e)
        {

        }

        private void PanelGame_MouseDown(object sender, MouseEventArgs e)
        {

        }

        private void PanelGame_Enter(object sender, EventArgs e)
        {

        }

        private void PanelGame_Leave(object sender, EventArgs e)
        {

        }

        private void PanelGame_SizeChanged(object sender, EventArgs e)
        {
        }
    }
}
