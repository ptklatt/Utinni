using System;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.Utility;

namespace ExampleEditorPlugin
{
    // For an Editor, either inherit EditorPluginBase or IEditorPlugin.
    // As all plugins with the IEditorPlugin interface get automatically
    // added to the main Editor windows flowlayoutpanel as an CollapsiblePanel,
    // it's preferred to inherit EditorPluginBase, as it sets up the the correct size
    // automatically.
    public partial class ExampleEditorPlugin : EditorPluginBase
    {
        public ExampleEditorPlugin()
        {
            InitializeComponent();

            // The only thing that needs to be set up is the PluginInformation and the plugin is good to go
            Information = new PluginInformation("Example Editor Plugin"
                                                , "This is an editor plugin example"
                                                , "Example Author"
                                                , new Version(1, 0));


            Log.Info("Example Editor Plugin created");
        }

        private void btnTest_Click(object sender, EventArgs e)
        {
            Log.Info("Test");
            UtinniCore.Utinni.Game.Quit();
        }
    }
}
