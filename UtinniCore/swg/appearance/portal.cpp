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

#include "portal.h"

namespace swg::portalPropertyTemplate
{
using pGetCrc = int(__thiscall*)(utinni::PortalPropertyTemplate* pThis);
using pGetCellCount = int(__thiscall*)(utinni::PortalPropertyTemplate* pThis);
using pGetExteriorAppearanceName = const char* (__thiscall*)(utinni::PortalPropertyTemplate* pThis);

pGetCrc getCrc = (pGetCrc)0x00B47BD0;
pGetCellCount getCellCount = (pGetCellCount)0x00B47BE0;
pGetExteriorAppearanceName getExteriorAppearanceName = (pGetExteriorAppearanceName)0x00B47C90;
}

namespace swg::portalPropertyTemplateList
{
using pGetPobByCrcString = utinni::PortalPropertyTemplate* (__cdecl*)(utinni::PersistentCrcString* pobCrcString);
pGetPobByCrcString getPobByCrcString = (pGetPobByCrcString)0x00B497E0;
}

namespace swg::cellProperty
{
using pGetParentCell = swgptr(__thiscall*)(utinni::CellProperty* pThis);
using pSetPortalTransitions = void(__cdecl*)(bool enabled);

pGetParentCell getParentCell = (pGetParentCell)0x00B22C00;
pSetPortalTransitions setPortalTransitions = (pSetPortalTransitions)0x00B2A990;
}

namespace utinni
{

int PortalPropertyTemplate::getCrc()
{
    return swg::portalPropertyTemplate::getCrc(this);
}

int PortalPropertyTemplate::getCellCount()
{
    return swg::portalPropertyTemplate::getCellCount(this);
}

const char* PortalPropertyTemplate::getExteriorAppearanceName()
{
    return swg::portalPropertyTemplate::getExteriorAppearanceName(this);
}

PortalPropertyTemplate* PortalPropertyTemplateList::getPobByCrcString(PersistentCrcString* pobCrcString)
{
    return swg::portalPropertyTemplateList::getPobByCrcString(pobCrcString);
}


ClientObject* CellProperty::getParentObject() const
{
    return parentObject;
}

Object* CellProperty::getAppearanceObject() const
{
    return appearanceObject;
}

int CellProperty::getIndex() const
{
    return index;
}

const char* CellProperty::getName() const
{
    return name;
}

swgptr CellProperty::getParentCell()
{
    return swg::cellProperty::getParentCell(this);
}

void CellProperty::setPortalTransitions(bool enabled)
{
    swg::cellProperty::setPortalTransitions(enabled);
}

}