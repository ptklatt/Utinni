using System;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.Utility;

namespace ExampleEditorPlugin
{
    // For an Editor inherit IEditorPlugin.
    // As all plugins with the IEditorPlugin interface that don't return null on GetSubPanel
    // get automatically added to the main Editor windows main FlowLayoutPanel as an CollapsiblePanel.
    // All IEditorPlugins that don't return null on GetStandalonePanel, get added as a ComboBox option
    // above the main Editor windows main FlowLayoutPanel, which when selected, replaces the main 
    // FlowLayoutPanel
    public partial class ExampleEditorPlugin : IEditorPlugin
    {
        private readonly ExampleEditorSubPanel subPanel;

        public ExampleEditorPlugin()
        {
            // The only thing that needs to be set up is the PluginInformation and the plugin is good to go
            Information = new PluginInformation("Example Editor Plugin"
                                                , "This is an editor plugin example"
                                                , "Example Author");

            Log.Info("Created: Example Editor Plugin");

            subPanel = new ExampleEditorSubPanel(AddUndoCommand);
        }

        public PluginInformation Information { get; }
        public EventHandler<AddUndoCommandEventArgs> AddUndoCommand { get; set; }
        public EditorPanelBase GetStandalonePanel() { return null; }

        public EditorPanelBase GetSubPanel()
        {
            return subPanel;
        }
    }
}
