using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.ComponentModel.Composition.Hosting;
using System.IO;
using System.Linq;
using UtinniCoreDotNet.Utility;

namespace UtinniCoreDotNet.PluginFramework
{
    public class PluginLoader
    {
        [ImportMany(typeof(IPlugin))] // Import all IPlugin interfaces
        public IEnumerable<IPlugin> Plugins;

        public PluginLoader()
        {
            Load();
        }

        public void Load()
        {
            Plugins = new List<IPlugin>();

            var pluginDir = UtinniCore.Utinni.utinni.GetPath() + "/Plugins/";
            var catalog = new AggregateCatalog(new DirectoryCatalog(pluginDir));

            // Find and load all .dll's that implement IPlugin inside each folder located in the plugin directory
            DirectoryInfo di = Directory.CreateDirectory(pluginDir); // Create if it doesn't exist for whatever reason

            // Need to loop through and create a new DirectoryCatalog for each separate plugin directory,
            // otherwise it doesn't see subfolders in pluginDir
            foreach (var directoryInfo in di.GetDirectories())
            {
                catalog.Catalogs.Add(new DirectoryCatalog(directoryInfo.FullName));
            }
            var container = new CompositionContainer(catalog);

            // Loads all found plugins
            container.ComposeParts(this);

            Log.Info(Plugins.Count() +  " Plugin(s) loaded");
        }
    }
}
