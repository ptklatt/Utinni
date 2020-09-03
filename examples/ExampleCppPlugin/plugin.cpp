#include <mscoree.h>

#include "UtinniCore/utinni.h"
#include "UtinniCore/plugin_framework/utinni_plugin.h"
#include "UtinniCore/swg/ui/cui_chat_window.h"

#include "example_command_parser.h"


class ExampleCppPlugin : public utinni::UtinniPlugin
{
private:
     Information information =
    {
        "Example Cpp Plugin",
        "This is a Cpp Example Plugin",
        "Example Author"
    };

public:
    ExampleCppPlugin()
    {
        utinni::log::info("Example Cpp Plugin loaded"); // ToDo not being added to the log

        utinni::CuiChatWindow::addCreateCommandParserCallback(&example::ExampleCommandParser::create);
    }

    ~ExampleCppPlugin()
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
        return new ExampleCppPlugin();
    }
}
