/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

using System;
using System.Collections.Generic;
using UtinniCore.Utinni;
using UtinniCoreDotNet.Hotkeys;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.UI.Controls;
using UtinniCoreDotNet.UI.Forms;
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

        public UtINI GetConfig()
        {
            return null;
        }

        public EventHandler<AddUndoCommandEventArgs> AddUndoCommand { get; set; }

        public HotkeyManager GetHotkeyManager() { return null; }

        public List<IEditorForm> GetForms() { return null; }

        public List<SubPanelContainer> GetStandalonePanels() { return null; }

        public List<SubPanel> GetSubPanels()
        {
            return subPanels;
        }
    }
}
