#pragma once

#include "utinni.h"
#include "utinni_plugin.h"

namespace utinni
{
class UTINNI_API PluginManager
{
public:
    UTINNI_API struct PluginConfig
    {
        std::string directoryName;
        bool isEnabled;
    };

    PluginManager();
    ~PluginManager();

    void loadPlugins() const;

    int getPluginConfigCount() const;
    const PluginConfig& getPluginConfigAt(int i);

private:
    struct Impl;
    Impl* pImpl{};
};

};

