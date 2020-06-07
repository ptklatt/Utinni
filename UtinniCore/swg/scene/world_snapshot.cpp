#include "world_snapshot.h"
#include "ground_scene.h"
#include "swg/appearance/appearance.h"
#include "swg/game/game.h"
#include "swg/misc/network.h"
#include "swg/object/object.h"
#include "swg/object/client_object.h"

namespace swg::worldSnapshotReaderWriter
{
using pOpenFile = bool(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, const char* filename);
using pSaveFile = bool(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, const char* filename);
using pClear = void(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis);

using pGetObjectTemplateName = const char* (__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, int objectTemplateNameIndex);

using pNodeCount = int(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis);
using pNodeCountTotal = int(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis);

using pGetNodeByNetworkId = utinni::WorldSnapshotReaderWriter::Node* (__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, DWORD networkId);
using pGetNodeByIndex = utinni::WorldSnapshotReaderWriter::Node* (__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, int nodeId);
using pAddNode = utinni::WorldSnapshotReaderWriter::Node* (__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, int nodeId, int parentNodeId, const utinni::CrcString& objectFilenameCrcString, int cellId, const swg::math::Transform& transform, float radius, unsigned int pobCrc);
using pRemoveNode = void(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, int nodeId);

pOpenFile openFile = (pOpenFile)0x00B97D90;
pSaveFile saveFile = (pSaveFile)0x00B98120;
pClear clear = (pClear)0x00B98290;

pGetObjectTemplateName getObjectTemplateName = (pGetObjectTemplateName)0x00B98720;

pNodeCount nodeCount = (pNodeCount)0x00B986A0;
pNodeCountTotal nodeCountTotal = (pNodeCountTotal)0x00B986D0;

pGetNodeByNetworkId getNodeByNetworkId = (pGetNodeByNetworkId)0x00B98740;
pGetNodeByIndex getNodeByIndex = (pGetNodeByIndex)0x00B986B0;
pAddNode addNode = (pAddNode)0x00B98410;
pRemoveNode removeNode = (pRemoveNode)0x00B98780;

namespace node
{
using pGetNodeNetworkId = int(__thiscall*)(utinni::WorldSnapshotReaderWriter::Node* pThis);
using pGetNodeSpatialSubdivisionHandle = DWORD(__thiscall*)(utinni::WorldSnapshotReaderWriter::Node* pThis);
using pSetNodeSpatialSubdivisionHandle = void(__thiscall*)(utinni::WorldSnapshotReaderWriter::Node* pThis, DWORD handle);

using pNodeRemoveFromWorld = void(__thiscall*)(utinni::WorldSnapshotReaderWriter::Node* pThis);

pGetNodeNetworkId getNodeNetworkId = (pGetNodeNetworkId)0x00B971D0;
pGetNodeSpatialSubdivisionHandle getNodeSpatialSubdivisionHandle = (pGetNodeSpatialSubdivisionHandle)0x00B97390;
pSetNodeSpatialSubdivisionHandle setNodeSpatialSubdivisionHandle = (pSetNodeSpatialSubdivisionHandle)0x00B973A0;

pNodeRemoveFromWorld nodeRemoveFromWorld = (pNodeRemoveFromWorld)0x00B97440;

}
}

namespace swg::worldsnapshot
{
using pLoad = void(__cdecl*)(const char* name);
using pUnload = void(__cdecl*)();

using pClearPreloadList = char(__cdecl*)(DWORD, DWORD, DWORD);

using pCreateObject = DWORD(__cdecl*)(utinni::WorldSnapshotReaderWriter* pReader, utinni::WorldSnapshotReaderWriter::Node* pNode, DWORD result);
using pAddObject = void(__cdecl*)(DWORD object, DWORD node);

using pDetailLevelChanged = void(__cdecl*)();

pLoad load = (pLoad)0x0059C380;
pUnload unload = (pUnload)0x0059C1D0;

pClearPreloadList clearPreloadList = (pClearPreloadList)0x00404D50;

pCreateObject createObject = (pCreateObject)0x0059BBA0;
pAddObject addObject = (pAddObject)0x0059BF20;

pDetailLevelChanged detailLevelChanged = (pDetailLevelChanged)0x0059DC30;
}

namespace utinni
{
WorldSnapshotReaderWriter* WorldSnapshotReaderWriter::get() { return (WorldSnapshotReaderWriter*) 0x1913E94; } // Static WorldSnapshotReaderWriter ptr

void WorldSnapshotReaderWriter::clear()
{
    swg::worldSnapshotReaderWriter::clear(this);
}

const char* WorldSnapshotReaderWriter::getObjectTemplateName(int objectTemplateNameIndex)
{
    return swg::worldSnapshotReaderWriter::getObjectTemplateName(this, objectTemplateNameIndex);
}

int WorldSnapshotReaderWriter::getNodeCount()
{
    return swg::worldSnapshotReaderWriter::nodeCount(this);
}

int WorldSnapshotReaderWriter::getNodeCountTotal()
{
    return swg::worldSnapshotReaderWriter::nodeCountTotal(this);
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::getNodeByNetworkId(int64_t networkId)
{
    return swg::worldSnapshotReaderWriter::getNodeByNetworkId(this, networkId);
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::getNodeByIndex(int nodeId)
{
    return swg::worldSnapshotReaderWriter::getNodeByIndex(this, nodeId);
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::addNode(int nodeId, int parentNodeId, const char* objectFilename, int cellId, const swg::math::Transform& transform, float radius, unsigned int pobCrc)
{
    return swg::worldSnapshotReaderWriter::addNode(this, nodeId, parentNodeId, *ConstCharCrcString::ctor(objectFilename), cellId, transform, radius, pobCrc);
}

void WorldSnapshotReaderWriter::Node::removeNode()
{
    if (parentId == 0)
    {
        removeNodeFull();

        const auto reader = get();
        for (int i = 0; i < get()->getNodeCount(); ++i)
        {
            if (reader->nodeList->at(i)->id == id)
            {
                reader->nodeList->erase(reader->nodeList->begin() + i);
                break;
            }
        }
    }
    else
    {
        Node* pParentNode = get()->getNodeByNetworkId(parentId);
        for (int i = 0; i < pParentNode->children->size(); ++i)
        {
            if (pParentNode->children->at(i)->id == id)
            {
                pParentNode->children->erase(pParentNode->children->begin() + i);
                break;
            }
        }

    }

    Network::getObjectById(id)->remove();

    swg::worldSnapshotReaderWriter::removeNode(get(), id);
}

void WorldSnapshotReaderWriter::Node::removeNodeFull() // WIP - Messy IDA pseudo code
{
    using Void1 = int(__thiscall*)(DWORD, int);
    using Void2 = int(__thiscall*)(DWORD);
    using Void3 = void(__cdecl*)();

    Void1 void1 = (Void1)0x005A25A0;
    Void1 void2 = (Void1)0x005A08D0;
    Void3 void5 = (Void3)0x005A09C0;
    Void2 call1 = (Void2)0x005A2D90;

    if (getNodeSpatialSubdivisionHandle())
    {
        DWORD nodeSpatialSubdivisionHandle1 = getNodeSpatialSubdivisionHandle();
        DWORD nodeSpatialSubdivisionHandle2 = nodeSpatialSubdivisionHandle1;

        if (nodeSpatialSubdivisionHandle1)
        {
            DWORD nodeSpatialSubdivisionHandle3 = *(DWORD*)(nodeSpatialSubdivisionHandle1 + 4);
            if (nodeSpatialSubdivisionHandle3)
            {
                void1(nodeSpatialSubdivisionHandle3, nodeSpatialSubdivisionHandle1);
                DWORD nodeSpatialSubdivisionHandle4 = nodeSpatialSubdivisionHandle2;

                if (!(*(byte*)(0x19BB7DC) & 1))
                {
                    *(byte*)(0x19BB7DC) |= 1u;

                    call1(memory::read<DWORD>(0x19BB7E0));
                    void5();
                }
                void2(memory::read<DWORD>(0x19BB7E0), (int)&nodeSpatialSubdivisionHandle4);
            }
        }
        setNodeSpatialSubdivisionHandle(0);

        Object* nodeObject = Network::getObjectById(id);

        // Need to nullptr check because only loaded objects are non null, ie in range or previously 'seen'
        // and the loop goes through all nodes in the entire .WS
        if (nodeObject != nullptr)
        {
            nodeObject->remove(); 
        }
    }
}

int64_t WorldSnapshotReaderWriter::Node::getNodeNetworkId()
{
    return Network::cast(id);
}

DWORD WorldSnapshotReaderWriter::Node::getNodeSpatialSubdivisionHandle()
{
    return swg::worldSnapshotReaderWriter::node::getNodeSpatialSubdivisionHandle(this);
}

void WorldSnapshotReaderWriter::Node::setNodeSpatialSubdivisionHandle(DWORD handle)
{
    swg::worldSnapshotReaderWriter::node::setNodeSpatialSubdivisionHandle(this, handle);
}

void WorldSnapshot::load(const std::string& name)
{
    if (name.empty())
        return;

    memory::nopAddress(0x0059C3F3, 6); // Removes the grabbing of current .trn name to allow the loading of any .ws

    swg::worldsnapshot::load(name.c_str());
}

void WorldSnapshot::unload() // WIP - Messy IDA pseudo code
{
    DWORD  v0 = memory::read<DWORD>(0x1913E08);
    DWORD  v1 = memory::read<DWORD>(0x1913E04);
    int  i = 0;
    if (((BYTE*)v0 - (BYTE*)v1) >> 2)
    {
        do // Still doesn't do anything
        {
            (*(void(__thiscall**)(DWORD))(**((DWORD**)v1 + i) + 8))(*((DWORD*)v1 + i));
            v0 = memory::read<DWORD>(0x1913E08);
            v1 = memory::read<DWORD>(0x1913E04);
            ++i;
        } while (i < ((BYTE*)v0 - (BYTE*)v1) >> 2);
    }

    auto readerWriter = WorldSnapshotReaderWriter::get();

    WorldSnapshotReaderWriter::clearPreloadList(v0, v0, v1);

    for (i = 0; i < readerWriter->getNodeCount(); ++i)
    {
        readerWriter->getNodeByIndex(i)->removeNodeFull();
    }

    using pUnkVoid1 = int(__thiscall*)(DWORD);
    pUnkVoid1 unkVoid1 = (pUnkVoid1)0x005A2570;

    for (int j = memory::read<int>(0x1913E4C); j != memory::read<int>(0x1913E50); ++j)
    {
        unkVoid1(j);
    }

    memory::write<DWORD>(0x1913E40, memory::read<DWORD>(0x1913E3C));
    memory::write<DWORD>(0x1913E28, memory::read<DWORD>(0x1913E24));
    memory::write<DWORD>(0x1913E1C, memory::read<DWORD>(0x1913E18));

    readerWriter->clear();
}

void WorldSnapshot::reload()
{
    unload();

    load(GroundScene::get()->getName());
}

void WorldSnapshotReaderWriter::clearPreloadList(DWORD unk1, DWORD unk2, DWORD unk3)
{
    swg::worldsnapshot::clearPreloadList(unk1, unk2, unk3);
}

void WorldSnapshotReaderWriter::saveFile()
{
    CreateDirectory((utility::getWorkingDirectory() + "/snapshot/").c_str(), nullptr);
    swg::worldSnapshotReaderWriter::saveFile(this, ("snapshot/" + GroundScene::get()->getName() + ".ws").c_str());
}

bool WorldSnapshot::getPreloadSnapshot()
{
    return memory::read<bool>(0x191113C);
}

void WorldSnapshot::setPreloadSnapshot(bool preloadSnapshot)
{
    memory::write<bool>(0x191113C, preloadSnapshot);
}

void WorldSnapshot::detailLevelChanged()
{
    swg::worldsnapshot::detailLevelChanged();
}

Object* createObject(WorldSnapshotReaderWriter::Node* pNode)
{
    DWORD errorCode = 0;
    return (Object*)swg::worldsnapshot::createObject(WorldSnapshotReaderWriter::get(), pNode, errorCode);
}

int highestId = 0;
void WorldSnapshot::createNewNode(const char* objectFilename, swg::math::Transform& transform)
{
    if (strstr(objectFilename, "/base/"))
        return;

    ClientObject* cobj = ObjectTemplate::createObject(objectFilename)->getClientObject();

    if (cobj == 0 || cobj->getCreatureObject() != 0 || cobj->getShipObject() != 0 || (cobj != 0 && cobj->getTangibleObject() == 0 && cobj->getStaticObject() == 0))
        return;

    highestId++;
    const int id = highestId;

    int pobCrc = 0;
    int pobCellCount = 0;
    int parentNodeId = 0;

    WorldSnapshotReaderWriter::Node* pParentNode = nullptr;

    Camera* pCamera = GroundScene::get()->getCurrentCamera();
    if (pCamera->parentObject != nullptr)
    {
        pParentNode = WorldSnapshotReaderWriter::get()->getNodeByNetworkId(pCamera->parentObject->networkId);
        if (pParentNode == nullptr)
            return;

        parentNodeId = pParentNode->id;
    }

    if (pCamera->parentObject != nullptr && pParentNode == nullptr)
        return;

    const char* pobFilename = ObjectTemplateList::getObjectTemplateByFilename(objectFilename)->getPortalLayoutFilename();
    if (pobFilename != nullptr)
    {
        PortalPropertyTemplate* pPob = PortalPropertyTemplateList::getPobByCrcString(PersistentCrcString::ctor(pobFilename));
        pobCrc = pPob->getCrc();
        pobCellCount = pPob->getCellCount() - 1;
    }

    WorldSnapshotReaderWriter::get()->addNode(id, parentNodeId, objectFilename, 0, transform, 512, pobCrc); // ToDo Make radius a customizable variable

    for (int i = 0; i < pobCellCount; ++i)
    {
        highestId = id + i + 1;
        WorldSnapshotReaderWriter::get()->addNode(highestId, id, "object/cell/shared_cell.iff", i + 1, swg::math::Transform::getIdentity(), 0, 0);
    }

    WorldSnapshotReaderWriter::Node* pNode = nullptr;
    if (pParentNode == nullptr)
    {
        auto reader = WorldSnapshotReaderWriter::get();
        pNode = reader->nodeList->back();
    }
    else
    {
        pNode = pParentNode->children->back();
    }

    Object* obj = createObject(pNode);
    if (obj)
    {
        obj->addToWorld();
    }
}

void WorldSnapshot::removeNode(WorldSnapshotReaderWriter::Node* pNode)
{
    pNode->removeNode();

    detailLevelChanged(); // Hack to update the .WS
}
}
