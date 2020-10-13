using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;
using UtinniCoreDotNet.Utility;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniNumericUpDown : NumericUpDown
    {
        [Description("Draw Outline"), Category("Data")]
        public bool DrawOutline { get; set; } = false;
        private Pen outlinePen;

        private bool isPressed;

        public UtinniNumericUpDown()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw |
                     ControlStyles.UserPaint | ControlStyles.SupportsTransparentBackColor, true);

            base.AutoSize = false;

            Controls.RemoveAt(0);
            this.Padding = new Padding(0);
            this.Margin = new Padding(0);

            this.BorderStyle = BorderStyle.FixedSingle;

            Control txtbox = Controls[0];
            txtbox.AutoSize = false;
            txtbox.ForeColor = Colors.Font();
            txtbox.BackColor = Colors.PrimaryHighlight();
            txtbox.MouseMove += Txtbox_MouseMove;

            Controls.Add(new UtinniUpButton(this));
            Controls.Add(new UtinniDownButton(this));

            outlinePen = new Pen(Colors.ControlBorder(), 1);
        }

        private decimal originalValue;
        private Point originalMouseDownPos;
        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);

            isPressed = true;
            originalMouseDownPos = e.Location;
            originalValue = Value;
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            base.OnMouseUp(e);

            isPressed = false;
        }

        private void Txtbox_MouseMove(object sender, MouseEventArgs e)
        {
            if (isPressed && e.Button == MouseButtons.Left && Native.GetAsyncKeyState(Keys.ShiftKey) < 0)
            {
                var deltaX = (originalMouseDownPos.X - e.X) * Increment;
                Value = Math.Min(Math.Max(originalValue - deltaX, Minimum), Maximum);

                TextBox txtbox = (TextBox) sender;
                txtbox.SelectionLength = 0;
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            OnPaintBackground(e);
            OnPaintForeground(e);

            if (DrawOutline)
            {
                e.Graphics.DrawRectangle(outlinePen, 0, 0, Width - 1, Height - 1);
            }
        }

        protected virtual void OnPaintForeground(PaintEventArgs e)
        {
            e.Graphics.FillRectangle(new SolidBrush(Colors.PrimaryHighlight()), 0, 0, Width, Height);
        }

        internal class UtinniUpButton : UtinniButtonBase
        {
            private readonly UtinniNumericUpDown parent;

            private SolidBrush fontBrush;
            private Pen fontPen;

            public UtinniUpButton(UtinniNumericUpDown parent) : base(Colors.Secondary(), Colors.Secondary())
            {
                SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw |
                         ControlStyles.UserPaint | ControlStyles.SupportsTransparentBackColor, true);

                this.parent = parent;

                Width = 13;
                Height = 8;
                Location = new Point(parent.Width - 15, 2);

                base.Anchor = AnchorStyles.Right;

                UpdateColors();
            }

            private void UpdateColors()
            {
                fontBrush = new SolidBrush(Colors.Font());
                fontPen = new Pen(Colors.Font(), 1);
            }

            protected override void OnPaint(PaintEventArgs e)
            {
                base.OnPaint(e);

                // Draw the upward arrow
                e.Graphics.FillRectangle(fontBrush, 6, 2, 1, 1);
                e.Graphics.DrawLine(fontPen, 5, 3, 7, 3);
                e.Graphics.DrawLine(fontPen, 4, 4, 8, 4);
            }

            protected override void OnMouseDown(MouseEventArgs e)
            {
                base.OnMouseDown(e);

                if (e.Button == MouseButtons.Left && !parent.ReadOnly)
                {
                    if (parent.Value == parent.Maximum)
                    {
                        return;
                    }

                    parent.Value += parent.Increment;
                }
            }

            protected override void OnEnabledChanged(EventArgs e)
            {
                base.OnEnabledChanged(e);

                fontPen = new Pen(ForeColor, 1);
                fontBrush = new SolidBrush(ForeColor);
            }
        }

        internal class UtinniDownButton : UtinniButtonBase
        {
            private readonly UtinniNumericUpDown parent;

            private SolidBrush fontBrush;
            private Pen fontPen;

            public UtinniDownButton(UtinniNumericUpDown parent) : base(Colors.Secondary(), Colors.Secondary())
            {
                SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw |
                         ControlStyles.UserPaint | ControlStyles.SupportsTransparentBackColor, true);

                this.parent = parent;

                Width = 13;
                Height = 8;
                Location = new Point(parent.Width - 15, 10);

                base.Anchor = AnchorStyles.Right;

                UpdateColors();
            }

            private void UpdateColors()
            {
                fontBrush = new SolidBrush(Colors.Font());
                fontPen = new Pen(Colors.Font(), 1);
            }

            protected override void OnPaint(PaintEventArgs e)
            {
                base.OnPaint(e);
                
                // Draw the downward arrow
                e.Graphics.DrawLine(fontPen, 4, 2, 8, 2);
                e.Graphics.DrawLine(fontPen, 5, 3, 7, 3);
                e.Graphics.FillRectangle(fontBrush, 6, 4, 1, 1);
            }

            protected override void OnMouseDown(MouseEventArgs e)
            {
                base.OnMouseDown(e);

                if (e.Button == MouseButtons.Left && !parent.ReadOnly)
                {
                    if (parent.Value == parent.Minimum)
                    {
                        return;
                    }

                    parent.Value -= parent.Increment;
                }
            }

            protected override void OnEnabledChanged(EventArgs e)
            {
                base.OnEnabledChanged(e);

                fontPen = new Pen(ForeColor, 1);
                fontBrush = new SolidBrush(ForeColor);
            }
        }
    }

}
