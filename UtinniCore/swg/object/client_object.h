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
#include "object.h"

namespace utinni
{
class UTINNI_API ClientObject : public Object
{
public:
	 uint32_t pArrangementDescriptor;
	 AutoDeltaByteStream unk01;
	 AutoDeltaByteStream unk02;
	 AutoDeltaByteStream unk03;
	 AutoDeltaByteStream unk04;
	 AutoDeltaByteStream unk05;
	 AutoDeltaByteStream unk06;
	 uint32_t unk07;
	 bool unk08;
	 bool unk09;
	 uint32_t unk10;
	 uint32_t unk11;
	 uint32_t unk12;
	 uint32_t unk13;
	 uint32_t unk14;
	 uint32_t unk15;
	 uint32_t unk16;
	 uint32_t unk17;
	 AutoDeltaVariable<int> volume;
	 //uint32_t unk18;
	 //uint32_t unk19;
	 AutoDeltaVariableCallback<const char*> name;
	 AutoDeltaVariable<StringId> nameStringID;
	 AutoDeltaVariable<StringId> descriptionStringID;
	 AutoDeltaVariableCallback<float> complexity;
	 AutoDeltaVariable<int> unk20;
	 AutoDeltaVariableCallback<int> cashBalance;
	 AutoDeltaVariableCallback<int> bankBalance;
	 bool isClientcached;
	 int uniqueID;
	 //std::vector<Object*> nearbyObjects; // unsure if correct ToDo implement proper
	 float unk21;
	 bool unk22;

	 void setParentCell(CellProperty* pCell);
	 void beginBaselines();
	 void endBaselines();
	 int getGameObjectType();
	 const char* getGameObjectTypeStringIdKey();
	 std::string getGameObjectTypeName();

	 swgptr getCreatureObject();
	 swgptr getShipObject();
	 swgptr getStaticObject();
	 swgptr getTangibleObject();
};

}

