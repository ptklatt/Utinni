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
