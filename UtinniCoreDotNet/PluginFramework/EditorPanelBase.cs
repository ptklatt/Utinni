using System;using System.Windows.Forms;

namespace UtinniCoreDotNet.PluginFramework
{
    public partial class EditorPanelBase : UserControl
    {
        public readonly string CheckboxPanelText;
        private const int width = 417;

        public EditorPanelBase()
        {
            Width = width;
        }

        public EditorPanelBase(string name)
        {
            Width = width;
            CheckboxPanelText = name;
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
