using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI;
using UtinniCoreDotNet.UI.Controls;
using UtinniCoreDotNet.UI.Theme;
using UtinniCoreDotNet.Utility;

namespace UtinniCoreDotNet.UI.Forms
{
    public partial class UtinniForm : Form
    {
        [Description("Resizable"), Category("Data")]
        public bool Resizable { get; set; } = true;

        [Description("Enable Shadow"), Category("Data")]
        public bool EnableShadow { get; set; } = true;

        [Description("Draw Name"), Category("Data")]
        public bool DrawName { get; set; } = false;

        [Description("Icon Image"), Category("Data")]
        public Image IconImage { get; set; } = null;

        [Browsable(false)]
        public new FormBorderStyle FormBorderStyle
        {
            get { return base.FormBorderStyle; }
            set { base.FormBorderStyle = value; }
        }

        private const int titleBarHeight = 22;

        private readonly Font nameFont = new Font("Arcon", 12);

        public List<UtinniTitlebarButton> LeftTitleBarButtons = new List<UtinniTitlebarButton>();
        public List<UtinniTitlebarButton> RightTitleBarButtons = new List<UtinniTitlebarButton>();

        private SolidBrush foreColorBrush;

        public UtinniForm()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw | ControlStyles.UserPaint, true);

            FormBorderStyle = FormBorderStyle.None;

            UtinniTitlebarButton closeButton = new UtinniTitlebarButton(new Bitmap(Properties.Resources.close), Color.Red);
            closeButton.Click += CloseButton_Click;
            RightTitleBarButtons.Add(closeButton);

            if (MaximizeBox)
            {
                UtinniTitlebarButton maximizeButton = new UtinniTitlebarButton(new Bitmap(Properties.Resources.maximize));
                maximizeButton.Click += MaximizeButton_Click;
                RightTitleBarButtons.Add(maximizeButton);
            }

            if (MinimizeBox)
            {
                UtinniTitlebarButton minimizeButton = new UtinniTitlebarButton(new Bitmap(Properties.Resources.min));
                minimizeButton.Click += MinimizeButton_Click;
                RightTitleBarButtons.Add(minimizeButton);
            }

            UpdateForeColor();
        }

        private void UpdateForeColor()
        {
            foreColorBrush = new SolidBrush(Colors.Font());
            ForeColor = Colors.Font();
        }

        protected override void OnLoad(EventArgs e)
        {
            int rightButtonEdge = 0;
            foreach (UtinniTitlebarButton btn in RightTitleBarButtons)
            {
                btn.Anchor = AnchorStyles.Top | AnchorStyles.Right;
                Controls.Add(btn);

                btn.Location = new Point(Width - rightButtonEdge - btn.Width, 2);
                rightButtonEdge += btn.Width;
            }

            int leftButtonEdge = 0;
            foreach (UtinniTitlebarButton btn in LeftTitleBarButtons)
            {
                btn.Anchor = AnchorStyles.Top | AnchorStyles.Left;
                Controls.Add(btn);
                btn.Location = new Point(32 + leftButtonEdge, 2);
                leftButtonEdge += btn.Width;
            }

            if (IconImage != null)
            {
                IconImage = new Bitmap(IconImage, 24, 24);
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Color backColor = Colors.Primary();

            e.Graphics.Clear(backColor);

            using (SolidBrush b = new SolidBrush(backColor))
            {
                Rectangle topRect = new Rectangle(0, 0, Width, 5);
                e.Graphics.FillRectangle(b, topRect);
            }

            if (IconImage != null)
            {
                e.Graphics.DrawImage(IconImage, 5, 5);
            }

            e.Graphics.DrawLine(new Pen(Colors.Secondary(), 2), 0, 0, Width, 0);

            if (DrawName)
            {
                e.Graphics.DrawString(Text, nameFont, foreColorBrush, 48, 7, new StringFormat());
            }
        }

        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)
            {
                case Native.WM_NCHITTEST:
                    Native.WM_HitTests ht = HitTest(m.HWnd, m.WParam, m.LParam);
                    if (ht != Native.WM_HitTests.HTCLIENT)
                    {
                        m.Result = (IntPtr)ht;
                        return;
                    }

                    break;
            }

            base.WndProc(ref m);
        }

        private Native.WM_HitTests HitTest(IntPtr hwnd, IntPtr wparam, IntPtr lparam)
        {
            Point mousePos = this.PointToClient(new Point((short)lparam, (short)((int)lparam >> 16)));

            if (Resizable)
            {
                if (new Rectangle(Width - 15, Height - 15, 15, 15).Contains(mousePos))
                {
                    return Native.WM_HitTests.HTBOTTOMRIGHT;
                }
            }

            return Native.WM_HitTests.HTCLIENT;
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            if ((e.Button & MouseButtons.Left) != 0)
            {
                if (WindowState != FormWindowState.Maximized && e.Y <= titleBarHeight)
                {
                    Native.ReleaseCapture();
                    Native.SendMessage(this.Handle, Native.WM_SYSCOMMAND, Native.SC_DRAGMOVE, 0);
                }
            }

            base.OnMouseDown(e);
        }

        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;

                if (EnableShadow)
                {
                    cp.ClassStyle |= Native.CS_DROPSHADOW;
                }

                return cp;
            }
        }

        private void MinimizeButton_Click(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Minimized;
        }

        private void MaximizeButton_Click(object sender, EventArgs e)
        {
            UtinniTitlebarButton btn = (UtinniTitlebarButton)sender;
            if (WindowState == FormWindowState.Normal)
            {
                WindowState = FormWindowState.Maximized;
                btn.SetImage(new Bitmap(Properties.Resources.maximized));
            }
            else
            {
                WindowState = FormWindowState.Normal;
                btn.SetImage(new Bitmap(Properties.Resources.maximize));
            }
        }

        private void CloseButton_Click(object sender, EventArgs e)
        {
            Close();
        }

    }
}