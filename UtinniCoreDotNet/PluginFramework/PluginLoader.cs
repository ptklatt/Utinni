/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

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
