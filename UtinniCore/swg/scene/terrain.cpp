#include "terrain.h"

namespace swg::terrain
{
using pReloadTerrain = int(__thiscall*)(utinni::Terrain* pThis);
using pSetTimeOfDay = int(__thiscall*)(utinni::Terrain* pThis, float, bool);
using pGetTimeOfDay = float(__thiscall*)(utinni::Terrain* pThis);
using pSetWeatherIndex = int(__cdecl*)(int);

pReloadTerrain reloadTerrain = (pReloadTerrain)0x0051A4F0;
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

int Terrain::getTimeOfDayHours()
{
	 int result = 6 + (int)(getTimeOfDay() * 24.f * 60.f) / 60;
	 if (result >= 24)
	 {
		  result -= 24;
	 }
	 return result;
}

int Terrain::getTimeOfDayMinutes()
{
	 return (int)fmodf(getTimeOfDay() * 24.f * 60.f, 60.f);
}

int Terrain::getWeatherIndex()
{
	 return memory::read<int>(0x01924B6C); // Current terrain weatherIndex static pointer
}

void Terrain::setWeatherIndex(int weatherIndex)
{
	 swg::terrain::setWeatherIndex(weatherIndex);
}

const char* Terrain::getFilename()
{
	 return (const char*)0x019113C1; // Current terrain filename static pointer
}
}
