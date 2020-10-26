#pragma once
#include "utinni.h"
#include "swg/misc/io_win.h"

namespace utinni::debugCamera
{
enum Commands
{
    cmd_up = 3332,
    cmd_down,
    cmd_forward,
    cmd_backward,
    cmd_right,
    cmd_left,
    cmd_speedBoost,
    cmd_mouseMovePosition,

};

UTINNI_API extern void setSpeed(float value);
UTINNI_API extern float getSpeed();
UTINNI_API extern void setFastSpeedMulti(float value);
UTINNI_API extern void setMouseWheelSpeed(float value);
UTINNI_API extern void enableDragPlayer(bool value);

void processIoEvent(IoEvent* ioEvent);

void detour();
void patch();
};
