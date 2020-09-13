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

                Log.Setup();

                // Load plugins from the /Plugins/ directory
                PluginLoader pluginLoader = new PluginLoader();
                
                // Initialize callbacks that aren't purely editor related
                GameCallbacks.Initialize();
                GroundSceneCallbacks.Initialize();
                ObjectCallbacks.Initialize();

                if (UtinniCore.Utinni.utinni.GetConfig().GetBool("UtinniCore", "enableEditorMode"))
                { 
                    Application.Run(new FormMain(pluginLoader));
                }

            }
            return 0;
        }
    }
}
