#pragma once

#include "utinni.h"
#include "crc_string.h"
#include "swg_math.h"

namespace utinni
{
class Object;

struct CollisionInfo
{
    Object* object;
    swg::math::Vector point;
    swg::math::Vector normal;
    float time;
};

struct Controller
{
    DWORD* vtbl;
    uint32_t unk01;
    uint32_t unk02;
    Object* ownerObject;
};

struct DataResource
{
    DWORD* vtbl;
    PersistentCrcString name;
    int referenceCount;
};

struct StringId
{
    std::string stringTable;
    std::string text;
    unsigned int textIndex;
};


}
