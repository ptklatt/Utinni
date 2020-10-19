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
