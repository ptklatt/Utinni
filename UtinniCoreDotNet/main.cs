using System;
using System.Windows.Forms;
using UtinniCoreDotNet.Callbacks;
using UtinniCoreDotNet.PluginFramework;
using UtinniCoreDotNet.Utility;

namespace UtinniCoreDotNet
{
    internal static class Startup
    {
        private static bool initialized;

        [STAThread]
        private static int EntryPoint(string args)
        {
            if (!initialized)
            {
                initialized = true;
                Application.EnableVisualStyles();

                Log.LoadConfig();

                // Load plugins from the /Plugins/ directory
                PluginLoader pluginLoader = new PluginLoader();

                GameCallbacks.Initialize();
                GroundSceneCallbacks.Initialize();

                if (UtinniCore.Utinni.utinni.GetConfig().GetBool("UtinniCore", "isEditorChild"))
                { 
                    Application.Run(new FormMain(pluginLoader));
                }

            }
            return 0;
        }
    }
}
