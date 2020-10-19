#pragma once

#include "utinni.h"
#include "swg/misc/crc_string.h"
#include "swg/misc/swg_math.h"
#include "swg/misc/swg_misc.h"
#include "swg/appearance/appearance.h"
#include "swg/appearance/portal.h"

namespace utinni
{
class Appearance;
class Object;
class ClientObject;
struct Controller;
struct CellProperty;
struct ConstCharCrcString;

class UTINNI_API ObjectTemplate : DataResource
{
public:
    ObjectTemplate* baseData;
    static Object* createObject(const char* filename);
};

class UTINNI_API SharedObjectTemplate
{
public:
    const char* getAppearanceFilename();
    const char* getPortalLayoutFilename();
    const char* getClientDataFilename();
    int getGameObjectType();
};

class UTINNI_API SharedBuildingObjectTemplate
{
public:
    const char* getTerrainLayerFilename();
    const char* getInteriorLayoutFilename();
};

class UTINNI_API ObjectTemplateList
{
public:
    static SharedObjectTemplate* getObjectTemplateByFilename(const char* filename);
    static SharedObjectTemplate* getObjectTemplateByIff(swgptr iff);
    static const ConstCharCrcString getCrcStringByCrc(unsigned int crc);
    static ConstCharCrcString getCrcStringByName(const char* name);
    static swgptr getCrcStringByNameAsPtr(const char* name);
};

class UTINNI_API Object
{
public:
    swgptr vtbl;
    uint32_t unk01;
    uint32_t unk02;
    uint32_t unk03;
    ObjectTemplate* objectTemplate;
    uint32_t unk04;
    char* name;
    int64_t networkId;
    Appearance* appearance;
    Controller* controller;
    uint32_t unk07;
    Object* parentObject;
    uint32_t unk08;
    swgptr dpvsObjects;
    int rotations;
    swg::math::Vector scale;
    swg::math::Transform objectToParent;
    swg::math::Transform* objectToWorld;
    uint32_t unk09;
    swgptr container;
    swgptr CollisionProperty;
    swgptr SpatialSubdivisionHandle;
    uint8_t unk10; // might not need
    uint8_t unk11; // might not need
    uint8_t unk12; // might not need
    uint8_t unk13;
    uint32_t unk14;
    swgptr containedBy;

    static Object* ctor();
    static Object* getObjectById(swgptr networkIdPointer);

    void remove();

    swg::math::Transform* getTransform();
    swg::math::Transform* getTransform_o2w();
    void setTransform_o2w(swg::math::Transform& object2world);
    const swg::math::Vector rotate_o2w(const swg::math::Vector* o2w, const swg::math::Vector* pointInSpace);

    void addToWorld();
    void removeFromWorld();
    void setAppearance(Appearance* appearance);

    CellProperty* getParentCell();
    void addNotification(swgptr notification, bool allowWhenInWorld);

    void setObjectToWorldDirty(bool isDirty);

    void positionAndRotationChanged(bool dueToParentChange, swg::math::Vector& oldPosition);

    ClientObject* getClientObject();

    const char* getTemplateFilename();
    const char* getAppearanceFilename();
};

struct AutoVariableBase
{
    swgptr vtbl;
};

struct AutoDeltaVariableBase : AutoVariableBase
{
    unsigned short index;
    swgptr parent;
};

template <typename T>
struct AutoDeltaVariable : AutoDeltaVariableBase
{
    T value;
    T previousValue;
};

template <typename T>
struct AutoDeltaVariableCallback : AutoDeltaVariable<T>
{
    swgptr callback;
    Object* sourceObject;
};

struct AutoDeltaByteStream
{
    uint32_t unk01;
    uint32_t unk02;
    uint32_t unk03;
    uint32_t unk04;
    uint32_t unk05;
    uint32_t unk06;
    uint32_t unk07;
    uint32_t unk08;
};

}