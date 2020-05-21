#include "terrain.h"

namespace swg::terrain
{
using pSetTimeOfDay = int(__thiscall*)(utinni::Terrain* pThis, float, bool);
using pGetTimeOfDay = float(__thiscall*)(utinni::Terrain* pThis);
using pSetWeatherIndex = int(__cdecl*)(int);

pSetTimeOfDay setTimeOfDay = (pSetTimeOfDay)0x00B5CBD0;
pGetTimeOfDay getTimeOfDay = (pGetTimeOfDay)0x00B5CBC0;
pSetWeatherIndex setWeatherIndex = (pSetWeatherIndex)0x00845C90;
}

namespace utinni
{
Terrain* Terrain::get()
{
	 return memory::read<Terrain*>(0x01947194); // TerrainObject static pointer
}

void Terrain::setTimeOfDay(float time)
{
	 swg::terrain::setTimeOfDay(this, time, true);
}

float Terrain::getTimeOfDay()
{
	 return swg::terrain::getTimeOfDay(this);
}

int Terrain::getWeatherIndex()
{
	 return memory::read<int>(0x01924B6C); // Current terrain weatherIndex static pointer
}

void Terrain::setWeatherIndex(int weatherIndex)
{
	 swg::terrain::setWeatherIndex(weatherIndex);
}

const char* Terrain::getPath()
{
	 return (const char*)0x019113C1; // Current terrain filename static pointer
}
}
