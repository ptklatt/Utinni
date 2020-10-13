using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;
using UtinniCoreDotNet.UndoRedo;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UndoRedoToolStripDropDown : ToolStripDropDown
    {
        private readonly Action<int> undoRedoCallback;

        private readonly string cmdTypeText;

        private readonly Form parentForm;
        private readonly UndoRedoTitlebarButton parent;
        private readonly Panel pnl;
        private readonly Label lblUndoRedoCount;
        private readonly ListBox lbCommands;

        private const int width = 300;
        private const int lbHeight = 200;
        private const int bottomHeight = 30;

        private int count = 1;
        private int lastIndex = 1;

        public UndoRedoToolStripDropDown(UndoRedoTitlebarButton parent, Form parentForm, string cmdTypeText, Action<int> undoRedoCallback)
        {
            this.parentForm = parentForm;
            this.cmdTypeText = cmdTypeText;
            this.parent = parent;
            this.undoRedoCallback = undoRedoCallback;

            BackColor = Colors.Primary();
            ForeColor = Colors.Font();

            pnl = new Panel
            {
                Size = new Size(width, bottomHeight + lbHeight),
                Location = new Point(0, 0),
                BorderStyle = BorderStyle.FixedSingle,
                BackColor = Colors.Primary(),
                ForeColor = Colors.Font(),
            };

            lblUndoRedoCount = new Label
            {
                Size = new Size(width, bottomHeight),
                Location = new Point(1, lbHeight - 2),
                TextAlign = ContentAlignment.MiddleCenter,
                Text = cmdTypeText + " 1 command(s)",
                ForeColor = Colors.Font(),
            };

            lbCommands = new ListBox
            {
                Size = new Size(width, lbHeight),
                Location = new Point(0, 1),
                SelectionMode = SelectionMode.MultiSimple,
                ScrollAlwaysVisible = true,
                BorderStyle = BorderStyle.None,
                Font = new Font(pnl.Font.FontFamily, 9),
                BackColor = Colors.Primary(),
                ForeColor = Colors.Font(),
            };

            lbCommands.Click += LbCommands_Click;
            lbCommands.MouseMove += LbCommands_MouseMove;

            ToolStripControlHost tsch = new ToolStripControlHost(pnl)
            {
                Size = new Size(width, pnl.Height),
                Margin = Padding.Empty,
                
            };

            pnl.Controls.Add(lbCommands);
            pnl.Controls.Add(lblUndoRedoCount);

            base.Items.Add(tsch);
        }

        public void Display(Stack<IUndoCommand> commandStack)
        {
            lbCommands.Items.Clear();
            foreach (IUndoCommand undoCommand in commandStack)
            {
                lbCommands.Items.Add(undoCommand.GetText());
            }
            lbCommands.SelectedIndex = 0;

            Show(parentForm, new Point(parent.Bounds.Left, parent.Bounds.Bottom));
            lbCommands.Focus();
        }   

        private void LbCommands_Click(object sender, EventArgs e)
        {
            Close();
            undoRedoCallback(count);
        }

        private void LbCommands_MouseMove(object sender, MouseEventArgs e)
        {
            count = Math.Max(1, lbCommands.IndexFromPoint(e.Location) + 1);
            if (lastIndex != count)
            {
                int topIndex = Math.Max(0, Math.Min(lbCommands.TopIndex + e.Delta, lbCommands.Items.Count - 1));
                lbCommands.BeginUpdate();
                lbCommands.ClearSelected();

                for (int i = 0; i < count; ++i)
                {
                    lbCommands.SelectedIndex = i;
                }

                lblUndoRedoCount.Text = cmdTypeText + " " + count + " command(s)";
                lastIndex = count;
                lbCommands.EndUpdate();
                lbCommands.TopIndex = topIndex;
            }
        }
    }
}
