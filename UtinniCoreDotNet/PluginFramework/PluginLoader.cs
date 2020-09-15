using System;
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
            var cfg = UtinniCore.Utinni.utinni.GetConfig();

            List<Tuple<string, bool>> pluginLoadOrder = new List<Tuple<string, bool>>();

            // Get the [Plugins] load order list from ut.ini
            int i = 0;
            while (true)
            {
                string curStr = cfg.GetString("Plugins", "plugin_" + i.ToString("00"));
                if (!String.IsNullOrEmpty(curStr))
                {
                    i++;
                    int splitterPos = curStr.IndexOf(',');

                    if (splitterPos == -1)
                    {
                        Log.Error("Failed to parse [Plugins] priority list value due to missing separator: " + curStr);
                        continue;
                    }

                    Boolean.TryParse(curStr.Substring(0, splitterPos), out var isEnabled);
                    pluginLoadOrder.Add(new Tuple<string, bool>(curStr.Substring(splitterPos + 1).Trim(), isEnabled));
                }
                else
                {
                    break;
                }
            }

            // Find all plugin directories inside the Plugin folder
            DirectoryInfo di = Directory.CreateDirectory(pluginDir); // Create if it doesn't exist for whatever reason

            // Check if each found plugin directory exists in the [Plugins] load order, if not, add it at the back
            foreach (var directoryInfo in di.GetDirectories())
            {
                if (!pluginLoadOrder.Exists(plugin => plugin.Item1 == directoryInfo.Name))
                {
                    pluginLoadOrder.Add(new Tuple<string, bool>(directoryInfo.Name, true)); 
                    // ToDo potentially add a cfg setting to not automatically enable the plugin if it didn't exist in the list
                }
            }

            // Update the [Plugins] section in ut.ini & load the plugins in the correct load order set in the cfg
            cfg.DeleteSection("Plugins");
            for (int j = 0; j < pluginLoadOrder.Count; j++)
            {
                var pluginCfg = pluginLoadOrder[j]; // Item1 = Name, Item2 = isEnabled
                cfg.SetString("Plugins", "plugin_" + j.ToString("00"), pluginCfg.Item2.ToString().ToLower() + ", " + pluginCfg.Item1);

                // if it the plugin is enabled, add it to the Catalog that will be scanned to find IPlugin .DLL entries
                if (pluginCfg.Item2)
                {
                    catalog.Catalogs.Add(new DirectoryCatalog(pluginDir + pluginCfg.Item1 + "/"));
                }
            }
            cfg.Save();

            // Loads all found plugins
            var container = new CompositionContainer(catalog);
            container.ComposeParts(this);

            Log.Info(Plugins.Count() +  " .NET Plugin(s) loaded");
        }
    }
}
