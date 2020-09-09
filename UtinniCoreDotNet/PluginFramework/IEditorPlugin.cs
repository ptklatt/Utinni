using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Windows.Forms;
using UtinniCoreDotNet.Hotkeys;
using UtinniCoreDotNet.UI.Controls;
using UtinniCoreDotNet.UndoRedo;

namespace UtinniCoreDotNet.PluginFramework
{
    public class AddUndoCommandEventArgs : EventArgs
    {
        public IUndoCommand UndoCommand;
        public AddUndoCommandEventArgs(IUndoCommand cmd) { UndoCommand = cmd; }
    }

    [InheritedExport(typeof(IEditorPlugin))]
    public interface IEditorPlugin : IPlugin
    {
        EventHandler<AddUndoCommandEventArgs> AddUndoCommand { get; set; }

        HotkeyManager GetHotkeyManager();

        List<Form> GetForms();
        List<SubPanelContainer> GetStandalonePanels();
        List<SubPanel> GetSubPanels();
    }
}
