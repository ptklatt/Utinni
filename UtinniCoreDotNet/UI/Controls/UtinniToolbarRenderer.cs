using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class ToolbarRenderer : ToolStripProfessionalRenderer
    {
        public ToolbarRenderer()
        {
            this.RoundedEdges = false;
        }

        protected override void OnRenderArrow(ToolStripArrowRenderEventArgs e)
        {
            e.ArrowColor = Colors.Font();
            base.OnRenderArrow(e);
        }
    }
}
