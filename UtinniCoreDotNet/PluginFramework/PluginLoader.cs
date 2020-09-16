using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.ComponentModel.Composition.Hosting;
using System.Linq;
using UtinniCore.Utinni;
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

            var pluginDir = utinni.GetPath() + "/Plugins/";
            var catalog = new AggregateCatalog(new DirectoryCatalog(pluginDir));

            // Get the plugin configs from UtinniCore
            var pluginManager = utinni.GetPluginManager();
            List<PluginManager.PluginConfig> pluginConfigs = new List<PluginManager.PluginConfig>();
            for (int j = 0; j < pluginManager.PluginConfigCount; j++)
            {
                pluginConfigs.Add(pluginManager.GetPluginConfigAt(j));
            }

            foreach (PluginManager.PluginConfig pluginConfig in pluginConfigs)
            {
                if (pluginConfig.IsEnabled)
                {
                    // if it the plugin is enabled, add it to the Catalog that will be scanned to find IPlugin .DLL entries
                    catalog.Catalogs.Add(new DirectoryCatalog(pluginDir + pluginConfig.DirectoryName + "/"));
                }
            }

            // Loads all found plugins
            var container = new CompositionContainer(catalog);
            container.ComposeParts(this);

            Log.Info(Plugins.Count() +  " .NET Plugin(s) loaded");
        }
    }
}
