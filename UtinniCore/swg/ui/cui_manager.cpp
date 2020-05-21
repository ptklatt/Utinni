#include "cui_manager.h"

namespace swg::cuiManager
{
using pSetSize = void(__cdecl*)(int width, int height);

pSetSize setSize = (pSetSize)0x00882410;
    
}

namespace utinni
{
void CuiManager::setSize(int width, int height)
{
    swg::cuiManager::setSize(width, height);
}

}
