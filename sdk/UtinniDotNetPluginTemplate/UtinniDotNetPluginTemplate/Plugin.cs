using UtinniCore.Utinni;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.Utility;

namespace UtinniDotNetPluginTemplate
{
    public class Plugin : IPlugin
    {
        public Plugin()
        {
            Information = new PluginInformation("Example Plugin"
                , "This is an Example Plugin"
                , "ExampleAuthor");

            Log.Info("Created: " + Information.Name);
        }

        public PluginInformation Information { get; }

        public UtINI GetConfig()        
        {
            return null;
        }
    }
}
