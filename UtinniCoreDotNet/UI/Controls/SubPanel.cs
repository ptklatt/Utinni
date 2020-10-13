using System;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public partial class SubPanel : UserControl
    {
        public readonly string CheckboxPanelText;
        public readonly bool IsOpenByDefault;
        private const int width = 417;

        public SubPanel()
        {
            Width = width;
            base.BackColor = Colors.Primary();
            base.ForeColor = Colors.Font();
        }

        public SubPanel(string name, bool isOpenByDefault = false)
        {
            Width = width;
            CheckboxPanelText = name;
            IsOpenByDefault = isOpenByDefault;
        }
        
        // This is needed because the Visual Studio Designer handles inheritance incorrectly.
        // Overriding this, makes sure the width stays the same, to fit correctly into the plugin control area
        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            Width = width;
        }
    }
}
