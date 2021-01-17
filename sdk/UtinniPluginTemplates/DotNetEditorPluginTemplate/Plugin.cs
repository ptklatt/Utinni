using System;
using System.Collections.Generic;
using UtinniCore.Utinni;
using UtinniCoreDotNet.Hotkeys;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.UI.Controls;
using UtinniCoreDotNet.UI.Forms;
using UtinniCoreDotNet.Utility;

namespace $projectname$ 
{
public class $projectname$Plugin : IEditorPlugin
{
public $projectname$Plugin()
{
    Information = new PluginInformation("$projectname$"
        , "This is a $projectname$ Plugin"
        , "Plugin Author");

    Log.Info("Created: " + Information.Name);
}

public PluginInformation Information { get; }

public EventHandler<AddUndoCommandEventArgs> AddUndoCommand { get; set; }

public UtINI GetConfig()
{
    return null;
}

public HotkeyManager GetHotkeyManager()
{
    return null;
}

public List<IEditorForm> GetForms()
{
    return null;
}

public List<SubPanelContainer> GetStandalonePanels()
{
    return null;
}

public List<SubPanel> GetSubPanels()
{
    return null;
}
}
}