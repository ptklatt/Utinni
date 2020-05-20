#pragma once

#include "utinni.h"
#include "crc_string.h"
#include "swg_math.h"
#include "swg/object/object.h"

namespace utinni
{
struct DataResource
{
    DWORD* vtbl;
    PersistentCrcString name;
    int referenceCount;
};

struct Controller
{
    DWORD* vtbl;
    uint32_t unk01;
    uint32_t unk02;
    Object* ownerObject;
};

struct StringId
{
    std::string stringTable;
    std::string text;
    unsigned int textIndex;
};

struct CollisionInfo
{
    Object* object;
    swg::math::Vector point;
    swg::math::Vector normal;
    float time;
};

}
