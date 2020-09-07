using System.Windows.Forms;

namespace UtinniCoreDotNet.UI.Controls
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
