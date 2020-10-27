#include "debug_camera.h"
#include "camera.h"
#include "swg/scene/ground_scene.h"
#include "swg/object/player_object.h"
#include "swg/game/game.h"

namespace swg::debugCamera
{
using pAlter = float(__thiscall*)(utinni::GameCamera* pThis, float time);

pAlter alter = (pAlter)0x006DA1B0;
}

static const swg::math::Vector dirX(1, 0, 0);
static const swg::math::Vector dirY(0, 1, 0);
static const swg::math::Vector dirZ(0, 0, 1);

static const swg::math::Vector dirNegX(-1, 0, 0);
static const swg::math::Vector dirNegY(0, -1, 0);
static const swg::math::Vector dirNegZ(0, 0, -1);

namespace utinni::debugCamera
{

// ToDo make these settings
static float normalSpeed = 7;
static float fastSpeedMulti = 5;
static float wheelSpeed = 120;

static bool dragPlayer;

void setSpeed(float value)
{
    normalSpeed = value;
}

float getSpeed()
{
    return normalSpeed;
}

void setFastSpeedMulti(float value)
{
    fastSpeedMulti = value;
}

void setMouseWheelSpeed(float value)
{
    wheelSpeed = value;
}

void enableDragPlayer(bool value)
{
    dragPlayer = value;
}

void processIoEvent(IoEvent* ioEvent)
{
    const auto groundScene = GroundScene::get();
    if (groundScene == nullptr)
    {
        return;
    }

    MessageQueue* messageQueue = memory::read<MessageQueue*>((swgptr)groundScene->debugPortalCameraInputMap + 0xC);

    switch (ioEvent->type)
    {
    case IoEvent::Type::t_Character: 
        break;

    case IoEvent::Type::t_KeyDown:
        switch(ioEvent->arg2)
        {
        case IoEvent::Keys::kc_W:
            messageQueue->appendMessage(cmd_forward, 1);
            break;

        case IoEvent::Keys::kc_S:
            messageQueue->appendMessage(cmd_backward, 1);
            break;

        case IoEvent::Keys::kc_A:
            messageQueue->appendMessage(cmd_left, 1);
            break;

        case IoEvent::Keys::kc_D:
            messageQueue->appendMessage(cmd_right, 1);
            break;

        case IoEvent::Keys::kc_Space:
            messageQueue->appendMessage(cmd_up, 1);
            break;

        case IoEvent::Keys::kc_C:
            messageQueue->appendMessage(cmd_down, 1);
            break;

        case IoEvent::Keys::kc_LShift:
            messageQueue->appendMessage(cmd_speedBoost, 1);
            break;
        }
        break;

    case IoEvent::Type::t_KeyUp:
        switch (ioEvent->arg2)
        {
        case IoEvent::Keys::kc_W:
            messageQueue->appendMessage(cmd_forward, 0);
            break;

        case IoEvent::Keys::kc_S:
            messageQueue->appendMessage(cmd_backward, 0);
            break;

        case IoEvent::Keys::kc_A:
            messageQueue->appendMessage(cmd_left, 0);
            break;

        case IoEvent::Keys::kc_D:
            messageQueue->appendMessage(cmd_right, 0);
            break;

        case IoEvent::Keys::kc_Space:
            messageQueue->appendMessage(cmd_up, 0);
            break;

        case IoEvent::Keys::kc_C:
            messageQueue->appendMessage(cmd_down, 0);
            break;

        case IoEvent::Keys::kc_LShift:
            messageQueue->appendMessage(cmd_speedBoost, 0);
            break;

        }
        break;

    case IoEvent::Type::t_MouseButtonDown: 
        break;

    case IoEvent::Type::t_MouseButtonUp:
        break;
    }
}

static bool forward;
static bool backward;
static bool right;
static bool left;
static bool up;
static bool down;
static bool speedBoost;

float __fastcall hkAlter(GameCamera* pThis, swgptr EDX, float time)
{
    if (!pThis->isActive())
    {
        return 0;
    }

    float result = 0;
    result = swg::debugCamera::alter(pThis, time);

    float speedMulti;
    float wheelSpeedMulti;
    if (speedBoost)
    {
        speedMulti = time * (normalSpeed * fastSpeedMulti);
        wheelSpeedMulti = time * (wheelSpeed * fastSpeedMulti);
    }
    else
    {
        speedMulti = time * normalSpeed;
        wheelSpeedMulti = time * wheelSpeed;
    }

    swg::math::Vector direction;

    MessageQueue* messageQueue = memory::read<MessageQueue*>((swgptr)pThis + 0x248);
    if (messageQueue == nullptr)
    {
        return 0;
    }

    for (int i = 0; i < messageQueue->getCount(); ++i)
    {
        int msg;
        float value;
        messageQueue->getMessage(i, &msg, &value);

        switch (msg)
        {
        case 167: // cui mouseWheel
            if (value > 0)
            {
                direction = direction + (dirZ * wheelSpeedMulti);
            }
            else
            {
                direction = direction + (dirNegZ * wheelSpeedMulti);
            }
            break;

        case cmd_forward:
            forward = value == 1;
            break;

        case cmd_backward:
            backward = value == 1;
            break;

        case cmd_right:
            right = value == 1;
            break;

        case cmd_left:
            left = value == 1;
            break;

        case cmd_up:
            up = value == 1;
            break;

        case cmd_down:
            down = value == 1;
            break;

        case cmd_speedBoost:
            speedBoost = value == 1;
            break;

        }
    }

    if (forward)
    {
        direction = direction + (dirZ * speedMulti);
    }

    if (backward)
    {
        direction = direction + (dirNegZ * speedMulti);
    }

    if (right)
    {
        direction = direction + (dirX * speedMulti);
    }

    if (left)
    {
        direction = direction + (dirNegX * speedMulti);
    }

    if (up)
    {
        direction = direction + (dirY * speedMulti);
    }

    if (down)
    {
        direction = direction + (dirNegY * speedMulti);
    }

    pThis->move(pThis->objectToParent.rotate_l2p(direction));

    if (Game::isSafeToUse() && dragPlayer && (direction.X != 0 || direction.Y != 0 || direction.Z != 0))
    {
        const auto pos = pThis->getTransform()->getPosition();
        playerObject::teleport(pos.X, 0, pos.Z);
    }

    return result;
}

void detour()
{
    swg::debugCamera::alter = (swg::debugCamera::pAlter)Detour::Create((LPVOID)swg::debugCamera::alter, hkAlter, DETOUR_TYPE_PUSH_RET);
}

void patch()
{
    // Enable mouse wheel to be sent to debugCamera::alter
    memory::nopAddress(0x0051AA8D, 2);
}
};
