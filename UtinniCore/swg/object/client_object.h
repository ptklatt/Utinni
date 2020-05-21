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
	 AutoDeltaVariableCallback<std::wstring> name;
	 AutoDeltaVariable<StringId> nameStringID;
	 AutoDeltaVariable<StringId> descriptionStringID;
	 AutoDeltaVariableCallback<float> complexity;
	 AutoDeltaVariable<int> unk20;
	 AutoDeltaVariableCallback<int> cashBalance;
	 AutoDeltaVariableCallback<int> bankBalance;
	 bool isClientcached;
	 int uniqueID;
	 std::vector<Object*> nearbyObjects; // unsure if correct
	 float unk21;
	 bool unk22;

	 void setParentCell(DWORD pCell);
	 void beginBaselines();
	 void endBaselines();
	 int getGameObjectType();
	 const char* getGameObjectTypeStringIdKey();
	 const char* getGameObjectTypeName();

	 DWORD getCreatureObject();
	 DWORD getShipObject();
	 DWORD getStaticObject();
	 DWORD getTangibleObject();
};

}

