using System;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UndoRedoTitlebarButton : UtinniTitlebarButton
    {
        public readonly UndoRedoToolStripDropDown DropDown;

        public bool IsDropDownClickAreaPressed;
        private const int dropDownClickArea = 15;

        private SolidBrush fontBrush;
        private Pen fontPen;

        public UndoRedoTitlebarButton(Form parentForm, string cmdTypeText, Bitmap image, Action<int> undoRedoCallback) : base(image)
        {
            UpdateColors();
            DropDown = new UndoRedoToolStripDropDown(this, parentForm, cmdTypeText, undoRedoCallback);
            Enabled = false;
        }

        private void UpdateColors()
        {
            fontBrush = new SolidBrush(Colors.Font());
            fontPen = new Pen(Colors.Font(), 1);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            // Draw the arrow
            e.Graphics.DrawLine(fontPen, Width - 11, 15, Width - 7, 15);
            e.Graphics.DrawLine(fontPen, Width - 10, 16, Width - 8, 16);
            e.Graphics.FillRectangle(fontBrush, Width - 9, 17, 1, 1);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            IsDropDownClickAreaPressed = e.Button == MouseButtons.Left && e.X >= Width - dropDownClickArea;

            base.OnMouseDown(e);
        }

        protected override void OnForeColorChanged(EventArgs e)
        {
            base.OnForeColorChanged(e);
            fontPen = new Pen(ForeColor, 1);
            fontBrush = new SolidBrush(ForeColor);
        }
    }
}
