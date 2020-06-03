using System;
using System.Windows.Forms;
using UtinniCoreDotNet.PluginFramework;

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

                // Load plugins from the /Plugins/ directory
                PluginLoader pluginLoader = new PluginLoader();

				// Test Form
                Application.Run(new FormMain(pluginLoader));
            }
            return 0;
        }
    }
}
