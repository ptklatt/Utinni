using System.Drawing;
using System.Windows.Forms;

namespace UtinniCoreDotNet.UI.Forms
{
    public partial class UtinniForm : Form
    {
        public UtinniForm()
        {
            Name = "UtinniForm";
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw | ControlStyles.UserPaint, true);
            FormBorderStyle = FormBorderStyle.None;
            StartPosition = FormStartPosition.CenterScreen;
        }


        protected override void OnPaint(PaintEventArgs e)
        {
            e.Graphics.Clear(Colors.Primary());

        }

    }
}
