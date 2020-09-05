using System.Windows.Forms;

namespace UtinniUiDotNet.Controls
{
    public class UtinniButton : Button
    {
        public UtinniButton()
        {
            FlatStyle = FlatStyle.Popup;

            base.ForeColor = Colors.Font();
            base.BackColor = Colors.Secondary();
        }
    }
}
