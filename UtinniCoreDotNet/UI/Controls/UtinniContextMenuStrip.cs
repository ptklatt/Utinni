using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniContextMenuStrip : ContextMenuStrip
    {
        public UtinniContextMenuStrip()
        {
            ShowImageMargin = false;
            UpdateColors();
        }

        public void UpdateColors()
        {
            BackColor = Colors.Primary();
            ForeColor = Colors.Font();
            Renderer = new UtinniContextMenuStripRenderer(Colors.Secondary());

        }
    }
}
