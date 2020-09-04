#include "render_world.h"

namespace swg::renderWorld
{
using pAddObjectNotifications = void(__cdecl*)(utinni::Object* obj);
pAddObjectNotifications addObjectNotifications = (pAddObjectNotifications)0x007664F0;
}

namespace utinni::renderWorld
{
void addObjectNotifications(Object* obj)
{
    swg::renderWorld::addObjectNotifications(obj);
}

}
