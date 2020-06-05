using System;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using UtinniCoreDotNet.PluginFramework;

namespace UtinniCoreDotNet
{
    internal static class Startup
    {
        private static bool initialized;
        public static string CurrentDirectory;

        [STAThread]
        private static int EntryPoint(string args)
        {
            if (!initialized)
            {
                initialized = true;
                Application.EnableVisualStyles();

                CurrentDirectory = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

                // Load plugins from the /Plugins/ directory
                PluginLoader pluginLoader = new PluginLoader();

                if (UtinniCore.Utinni.utinni.GetConfig().GetBool("UtinniCore", "isEditorChild"))
                { 
                    Application.Run(new FormMain(pluginLoader));
                }
            }
            return 0;
        }
    }
}
