using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniContextMenuStripRenderer : ToolStripProfessionalRenderer
    {
        public UtinniContextMenuStripRenderer() : base(new UtinniContextMenuStripColorTable()) { }
        public UtinniContextMenuStripRenderer(Color hoverColor) : base(new UtinniContextMenuStripColorTable(hoverColor)) { }

        protected override void OnRenderToolStripBorder(ToolStripRenderEventArgs e)
        {
            // Override to remove the border -- ToDo Potentially add sides + bottom border with Colors.Secondary()
        }
    }

    public class UtinniContextMenuStripColorTable : ProfessionalColorTable
    {
        private readonly Color hoverBackColor;

        public UtinniContextMenuStripColorTable()
        {
            hoverBackColor = ThemeUtility.ScaleColor(Colors.Secondary(), Colors.HighlightScalar);
        }

        public UtinniContextMenuStripColorTable(Color hoverColor)
        {
            hoverBackColor = hoverColor;
        }

        public override Color MenuItemSelected
        {
            get { return hoverBackColor; }
        }
        public override Color MenuItemSelectedGradientBegin
        {
            get { return hoverBackColor; }
        }
        public override Color MenuItemSelectedGradientEnd
        {
            get { return hoverBackColor; }
        }

        public override Color MenuItemBorder
        {
            get { return hoverBackColor; }
        }
    }
}
