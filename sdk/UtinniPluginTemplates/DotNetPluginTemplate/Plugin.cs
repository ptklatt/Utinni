using UtinniCore.Utinni;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.Utility;

namespace $projectname$ 
{
public class $projectname$Plugin : IPlugin
{
public $projectname$Plugin()
{
    Information = new PluginInformation("$projectname$"
        , "This is a $projectname$ Plugin"
        , "Plugin Author");

    Log.Info("Created: " + Information.Name);
}

public PluginInformation Information { get; }

public UtINI GetConfig()
{
    return null;
}
}
}