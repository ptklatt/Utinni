#pragma once

#include "utinni.h"
#include "swg/misc/io_win.h"
#include "swg/object/object.h"

namespace utinni
{
class UTINNI_API Scene : public IoWin
{
public:
	 uint32_t unk01;
	 uint32_t unk02;
	 uint32_t unk03;
	 uint32_t unk04;
};

class UTINNI_API NetworkScene : public Scene
{
public:
	 Object* playerObject;
	 uint32_t unk01;
	 uint32_t unk02;
	 uint32_t unk03;
	 uint32_t unk04;
	 uint32_t unk05;
	 uint32_t unk06;
	 uint32_t unk07;
	 uint32_t unk08;
	 uint32_t unk09;
	 uint32_t unk10;
	 uint32_t unk11;
};

}

