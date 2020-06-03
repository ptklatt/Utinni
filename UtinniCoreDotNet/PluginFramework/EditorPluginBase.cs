using System;
using System.Windows.Forms;

namespace UtinniCoreDotNet.PluginFramework
{
    public partial class EditorPluginBase : UserControl, IEditorPlugin
    {
        public PluginInformation Information { get; set; }

        public UserControl GetControl()
        {
            return this;
        }

        private const int width = 434;

        public EditorPluginBase()
        {
            Width = width;
        }

        // This is needed because the Visual Studio Designer handles inheritence incorrectly.
        // Overriding this, makes sure the width stays the same, to fit correctly into the plugin control area
        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            Width = width;
        }

    }
}