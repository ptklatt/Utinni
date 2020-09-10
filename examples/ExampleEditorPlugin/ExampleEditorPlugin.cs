using System;
using System.Collections.Generic;
using System.Windows.Forms;
using UtinniCoreDotNet.Hotkeys;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.UI.Controls;
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
        private readonly List<SubPanel> subPanels = new List<SubPanel>();

        public ExampleEditorPlugin()
        {
            // The only thing that needs to be set up is the PluginInformation and the plugin is good to go
            Information = new PluginInformation("Example Editor Plugin"
                                                , "This is an editor plugin example"
                                                , "Example Author");

            Log.Info("Created: Example Editor Plugin");

            subPanels.Add(new ExampleEditorSubPanel(this));
        }

        public PluginInformation Information { get; }

        public EventHandler<AddUndoCommandEventArgs> AddUndoCommand { get; set; }

        public HotkeyManager GetHotkeyManager() { return null; }

        public List<Form> GetForms() { return null; }

        public List<SubPanelContainer> GetStandalonePanels() { return null; }

        public List<SubPanel> GetSubPanels()
        {
            return subPanels;
        }
    }
}
