#include <mscoree.h>

#include "UtinniCore/utinni.h"
#include "UtinniCore/plugin_framework/utinni_plugin.h"

class ExampleUtinniPlugin : public utinni::UtinniPlugin
{
private:
    Information information =
    {
        "Example Utinni Plugin",
        "An Example Utinni Plugin",
        "Example Author"
    };

public:
    ExampleUtinniPlugin()
    {
		
    }

    ~ExampleUtinniPlugin()
    {

    }

    virtual void init() override
    {
    }

    virtual const Information& getInformation() const override
    {
        return information;
    }
};

extern "C"
{
    UTINNI_PLUGIN
    {
        return new ExampleUtinniPlugin();
    }
}