#include "plugin_manager.h"
#include <filesystem>

namespace utinni
{
    using pCreatePlugin = UtinniPlugin * (*)();

    PluginManager::PluginManager() : plugins()
    {
    }

    PluginManager::~PluginManager()
    {
        for (const auto& plugin : plugins)
        {
            delete plugin;
        }
    }

    void PluginManager::loadPlugins()
    {
        const std::string pluginDir = getPath() + "/Plugins/";

        std::vector<std::string> directories;
        for (const auto& dir : std::filesystem::recursive_directory_iterator(pluginDir))
        {
            if (dir.is_directory())
            {
                for (const auto& file : std::filesystem::recursive_directory_iterator(dir))
                {
                    if (file.path().extension() == ".dll")
                    {
                        // Try to load the found .dll so that it that the createPlugin function can be looked up
                        HINSTANCE hDllInstance = LoadLibrary(file.path().string().c_str());

                        if (hDllInstance != nullptr)
                        {
                            // Check if it is a valid UtinniPlugin, which contains the createPlugin function
                            const pCreatePlugin createPlugin = (pCreatePlugin)GetProcAddress(hDllInstance, "createPlugin");

                            if (createPlugin != nullptr)
                            {
                                // If the function exists in the dll, call the createPlugin function and emplace it in the plugin manager plugin list
                                UtinniPlugin* plugin = createPlugin();
                                if (plugin != nullptr)
                                {
                                    plugins.emplace_back(plugin);
                                }
                            }
                        }
                    }
                }
            }
        }

    }
}
