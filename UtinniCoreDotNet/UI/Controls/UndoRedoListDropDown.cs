using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UndoRedo;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UndoRedoToolStripDropDown : ToolStripDropDown
    {
        private readonly Action<int> undoRedoCallback;

        private readonly string cmdTypeText;

        private readonly Form parentForm;
        private readonly ToolStripSplitButton parentTssbtn;
        private readonly Panel pnl;
        private readonly Label lblUndoRedoCount;
        private readonly ListBox lbCommands;

        private const int width = 300;
        private const int lbHeight = 200;
        private const int bottomHeight = 30;

        private int count = 1;
        private int lastIndex = 1;

        public UndoRedoToolStripDropDown(Form parentForm, string cmdTypeText, ToolStripSplitButton tssbtn, Action<int> undoRedoCallback)
        {
            this.parentForm = parentForm;
            this.cmdTypeText = cmdTypeText;
            parentTssbtn = tssbtn;
            this.undoRedoCallback = undoRedoCallback;

            pnl = new Panel
            {
                Size = new Size(width, bottomHeight + lbHeight),
                Location = new Point(0, 0),
                BorderStyle = BorderStyle.FixedSingle,
            };

            lblUndoRedoCount = new Label
            {
                Size = new Size(width, bottomHeight),
                Location = new Point(1, lbHeight - 2),
                TextAlign = ContentAlignment.MiddleCenter,
                Text = cmdTypeText + " 1 command(s)",
            };

            lbCommands = new ListBox
            {
                Size = new Size(width, lbHeight),
                Location = new Point(0, 1),
                SelectionMode = SelectionMode.MultiSimple,
                ScrollAlwaysVisible = true,
                BorderStyle = BorderStyle.None,
                Font = new Font(pnl.Font.FontFamily, 9),
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

            Show(parentForm, new Point(parentTssbtn.Bounds.Left + parentTssbtn.Owner.Left, parentTssbtn.Bounds.Bottom + parentTssbtn.Owner.Top));
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
