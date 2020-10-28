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

#pragma once

#include "utinni.h"
#include "swg/misc/crc_string.h"
#include "swg/misc/swg_math.h"
#include "swg/object/object.h"

namespace utinni
{
class Object;
class ClientObject;

class UTINNI_API PortalPropertyTemplate
{
public:
    int getCrc();
    int getCellCount();
    const char* getExteriorAppearanceName();
};

class UTINNI_API PortalPropertyTemplateList
{
public:
    static PortalPropertyTemplate* getPobByCrcString(PersistentCrcString* pobCrcString);
};

class UTINNI_API CellProperty
{
public:
    swgptr vtbl;
    ClientObject* parentObject;
    swgptr unk_08;
    swgptr unk_0C;
    swgptr unk_10;
    swgptr unk_14;
    swgptr unk_18;
    swgptr unk_1C;
    swgptr portalProperty;
    int index;
    Object* appearanceObject;
    swgptr unk_2C;
    swgptr unk_30;
    swgptr floor;
    const char* name;
    swgptr dpvsObject;
    swgptr unk_40;
    swgptr unk_44;
    swgptr unk_48;
    swgptr unk_4C;
    swgptr unk_50;
    swgptr unk_54;
    swgptr unk_58;
    swgptr unk_5C;
    swgptr unk_60;

    ClientObject* getParentObject() const;
    Object* getAppearanceObject() const;
    int getIndex() const;
    const char* getName() const;
    swgptr getParentCell();
    static void setPortalTransitions(bool enabled);
};

}
