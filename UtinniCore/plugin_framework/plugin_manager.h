#pragma once

#include "utinni.h"
#include "utinni_plugin.h"

namespace utinni
{
class UTINNI_API PluginManager
{
public:
    PluginManager();
    ~PluginManager();

    void loadPlugins();

private:
    std::vector<UtinniPlugin*> plugins;
};

};

