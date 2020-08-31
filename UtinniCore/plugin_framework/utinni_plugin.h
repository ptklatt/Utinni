#pragma once

#include "utinni.h"

namespace utinni
{
    struct UTINNI_API UtinniPlugin
    {
        struct UTINNI_API Information
        {
            const char* name;
            const char* description;
            const char* author;
        };

        UtinniPlugin() {};
        virtual ~UtinniPlugin() {}

        virtual void init() {}

        virtual const Information& getInformation() const = 0;
    };
}

#define UTINNI_PLUGIN extern "C" UTINNI_API utinni::UtinniPlugin* createPlugin()