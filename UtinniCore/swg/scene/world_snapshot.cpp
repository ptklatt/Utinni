#include "world_snapshot.h"
#include <filesystem>
#include "ground_scene.h"
#include "swg/appearance/appearance.h"
#include "swg/misc/network.h"
#include "swg/object/object.h"
#include "swg/object/client_object.h"
#include "swg/game/game.h"

namespace swg::worldSnapshotReaderWriter
{
using pOpenFile = bool(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, const char* filename);
using pSaveFile = bool(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, const char* filename);
using pClear = void(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis);

using pGetObjectTemplateName = const char* (__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, int objectTemplateNameIndex);

using pNodeCount = int(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis);
using pNodeCountTotal = int(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis);

using pGetNodeByNetworkId = utinni::WorldSnapshotReaderWriter::Node* (__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, swgptr networkId);
using pGetNodeByIndex = utinni::WorldSnapshotReaderWriter::Node* (__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, int nodeId);
using pAddNode = swgptr(__thiscall*)(utinni::WorldSnapshotReaderWriter* pThis, int nodeId, int parentNodeId, const utinni::CrcString& objectFilenameCrcString, int cellId, const swg::math::Transform& transform, float radius, unsigned int pobCrc);
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
using pSetNodeSpatialSubdivisionHandle = void(__thiscall*)(utinni::WorldSnapshotReaderWriter::Node* pThis, swgptr handle);

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

using pCreateObject = swgptr(__cdecl*)(utinni::WorldSnapshotReaderWriter* pReader, utinni::WorldSnapshotReaderWriter::Node* pNode, swgptr result);
using pAddObject = void(__cdecl*)(swgptr pObject, swgptr pNode);

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

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::getNodeById(int id)
{
    return swg::worldSnapshotReaderWriter::getNodeByNetworkId(this, id);
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::getNodeByNetworkId(int64_t networkId)
{
    return swg::worldSnapshotReaderWriter::getNodeByNetworkId(this, networkId);
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::getNodeAt(int index)
{
    return swg::worldSnapshotReaderWriter::getNodeByIndex(this, index);
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::addNode(int nodeId, int parentNodeId, const char* objectFilename, int cellId, const swg::math::Transform& transform, float radius, unsigned int pobCrc)
{
    // For some reason, the ptr is wrong if parentNodeId is 0 and it's actually 'result - 4' to get the accurate pointer

    swgptr pNode;
    if (parentNodeId == 0)
    {
        pNode = swg::worldSnapshotReaderWriter::addNode(this, nodeId, parentNodeId, *ConstCharCrcString::ctor(objectFilename), cellId, transform, radius, pobCrc) - 4;  // That's why we subtract 4 here
    }
    else
    {
        pNode = swg::worldSnapshotReaderWriter::addNode(this, nodeId, parentNodeId, *ConstCharCrcString::ctor(objectFilename), cellId, transform, radius, pobCrc); // If it's added to a parentNode, it seems fine
    }

    // Upon further testing, the ptr returned isn't reliable, unsure why
    // return memory::read<Node*>(pNode);
    return nullptr;
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
        // ToDo check if removeNodeFull can replace the below remove obj

        Object* nodeObject = Network::getObjectById(id);

        // Need to nullptr check because only loaded objects are non null, ie in range or previously 'seen'
        // and the loop goes through all nodes in the entire .WS
        if (nodeObject != nullptr)
        {
            nodeObject->remove();
        }

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

    swg::worldSnapshotReaderWriter::removeNode(WorldSnapshotReaderWriter::get(), id);
}

void WorldSnapshotReaderWriter::Node::removeNodeFull() // WIP - Messy IDA pseudo code
{
    using Void1 = int(__thiscall*)(swgptr, int);
    using Void2 = int(__thiscall*)(swgptr);
    using Void3 = void(__cdecl*)();

    Void1 void1 = (Void1)0x005A25A0;
    Void1 void2 = (Void1)0x005A08D0;
    Void3 void5 = (Void3)0x005A09C0;
    Void2 call1 = (Void2)0x005A2D90;

    if (getNodeSpatialSubdivisionHandle())
    {
        swgptr nodeSpatialSubdivisionHandle1 = getNodeSpatialSubdivisionHandle();
        swgptr nodeSpatialSubdivisionHandle2 = nodeSpatialSubdivisionHandle1;

        if (nodeSpatialSubdivisionHandle1)
        {
            swgptr nodeSpatialSubdivisionHandle3 = *(swgptr*)(nodeSpatialSubdivisionHandle1 + 4);
            if (nodeSpatialSubdivisionHandle3)
            {
                void1(nodeSpatialSubdivisionHandle3, nodeSpatialSubdivisionHandle1);
                swgptr nodeSpatialSubdivisionHandle4 = nodeSpatialSubdivisionHandle2;

                if (!(*(byte*)(0x19BB7DC) & 1))
                {
                    *(byte*)(0x19BB7DC) |= 1u;

                    call1(memory::read<swgptr>(0x19BB7E0));
                    void5();
                }
                void2(memory::read<swgptr>(0x19BB7E0), (int)&nodeSpatialSubdivisionHandle4);
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

swgptr WorldSnapshotReaderWriter::Node::getNodeSpatialSubdivisionHandle()
{
    return swg::worldSnapshotReaderWriter::node::getNodeSpatialSubdivisionHandle(this);
}

void WorldSnapshotReaderWriter::Node::setNodeSpatialSubdivisionHandle(swgptr handle)
{
    swg::worldSnapshotReaderWriter::node::setNodeSpatialSubdivisionHandle(this, handle);
}

const char* WorldSnapshotReaderWriter::Node::getObjectTemplateName() const
{
    return WorldSnapshotReaderWriter::get()->getObjectTemplateName(objectTemplateNameIndex);
}

int WorldSnapshotReaderWriter::Node::getChildCount() const
{
    return children->size();
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::Node::getChildAt(int index)
{
    return children->at(index);
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
    swgptr v0 = memory::read<swgptr>(0x1913E08);
    swgptr v1 = memory::read<swgptr>(0x1913E04);
    int  i = 0;
    if (((BYTE*)v0 - (BYTE*)v1) >> 2)
    {
        do // Still doesn't do anything
        {
            (*(void(__thiscall**)(swgptr))(**((swgptr**)v1 + i) + 8))(*((swgptr*)v1 + i));
            v0 = memory::read<swgptr>(0x1913E08);
            v1 = memory::read<swgptr>(0x1913E04);
            ++i;
        } while (i < ((BYTE*)v0 - (BYTE*)v1) >> 2);
    }

    auto readerWriter = WorldSnapshotReaderWriter::get();

    WorldSnapshotReaderWriter::clearPreloadList(v0, v0, v1);

    for (i = 0; i < readerWriter->getNodeCount(); ++i)
    {
        readerWriter->getNodeAt(i)->removeNodeFull();
    }

    using pUnkVoid1 = int(__thiscall*)(swgptr);
    pUnkVoid1 unkVoid1 = (pUnkVoid1)0x005A2570;

    for (int j = memory::read<int>(0x1913E4C); j != memory::read<int>(0x1913E50); ++j)
    {
        unkVoid1(j);
    }

    memory::write<swgptr>(0x1913E40, memory::read<swgptr>(0x1913E3C));
    memory::write<swgptr>(0x1913E28, memory::read<swgptr>(0x1913E24));
    memory::write<swgptr>(0x1913E1C, memory::read<swgptr>(0x1913E18));

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

static int highestId = 0;
int getHighestIdFromNode(int currentHighestId, const WorldSnapshotReaderWriter::Node* node)
{
    int result = max(currentHighestId, node->id);
    if (node->children && !node->children->empty())
    {
        for (const WorldSnapshotReaderWriter::Node* childNode : *node->children)
        {
            result = getHighestIdFromNode(result, childNode);
        }
    }

    return result;
}

int WorldSnapshot::generateHighestId()
{
    int newId = 0;
    auto snapshotFilenames = Game::getRepository()->getDirectoryFilenames("snapshot");
    for (const auto& filename : snapshotFilenames)
    {
        swg::worldSnapshotReaderWriter::openFile(WorldSnapshotReaderWriter::get(), std::filesystem::path(filename).filename().replace_extension("").string().c_str());

        const auto reader = WorldSnapshotReaderWriter::get();
        for (int i = 0; i < reader->getNodeCount(); ++i)
        {
            newId = getHighestIdFromNode(newId, reader->nodeList->at(i));
        }
    }

    highestId = newId;
    return newId;
}

Object* createObject(WorldSnapshotReaderWriter::Node* pNode)
{
    DWORD errorCode = 0;
    return (Object*)swg::worldsnapshot::createObject(WorldSnapshotReaderWriter::get(), pNode, errorCode);
}

bool WorldSnapshot::isValidObject(const char* objectFilename)
{
    if (strstr(objectFilename, "/base/"))
        return false;

    ClientObject* cobj = ObjectTemplate::createObject(objectFilename)->getClientObject();

    if (cobj == 0 || cobj->getCreatureObject() != 0 || cobj->getShipObject() != 0 || (cobj != 0 && cobj->getTangibleObject() == 0 && cobj->getStaticObject() == 0))
        return false;

    cobj->remove();
    cobj = nullptr;

    return true;
}

WorldSnapshotReaderWriter::Node* WorldSnapshot::createAddNode(const char* objectFilename, swg::math::Transform& transform)
{
    if (!isValidObject(objectFilename))
        return nullptr;

    const auto reader = WorldSnapshotReaderWriter::get();

    WorldSnapshotReaderWriter::Node* pParentNode = nullptr;

    // Temporary check to get parent, make this better
    int parentNodeId = 0;
    Camera* pCamera = GroundScene::get()->getCurrentCamera(); // If camera is outside of the POB and the new node to be created is inside, it crashes as parentObject is nullptr
    if (pCamera->parentObject != nullptr)
    {
        pParentNode = reader->getNodeByNetworkId(pCamera->parentObject->networkId);
        if (pParentNode == nullptr)
            return nullptr;

        parentNodeId = pParentNode->id;
    }

    if (pCamera->parentObject != nullptr && pParentNode == nullptr)
        return nullptr;

    // Check if the object contains cells
    int pobCrc = 0;
    int pobCellCount = 0;
    const char* pobFilename = ObjectTemplateList::getObjectTemplateByFilename(objectFilename)->getPortalLayoutFilename();
    if (pobFilename != nullptr && pobFilename[0] != '\0')
    {
        PortalPropertyTemplate* pPob = PortalPropertyTemplateList::getPobByCrcString(PersistentCrcString::ctor(pobFilename));
        pobCrc = pPob->getCrc();
        pobCellCount = pPob->getCellCount() - 1;
    }

    highestId++;
    const int id = highestId;
    reader->addNode(id, parentNodeId, objectFilename, 0, transform, 512, pobCrc); // ToDo Make radius a customizable variable

    // If the object contains cells, create them
    for (int i = 0; i < pobCellCount; ++i)
    {
        highestId = id + i + 1;
        reader->addNode(highestId, id, "object/cell/shared_cell.iff", i + 1, swg::math::Transform::getIdentity(), 0, 0);
    }

    // Workaround to the unreliable ptr return of reader->addNode
    WorldSnapshotReaderWriter::Node* pNode;
    if (pParentNode == nullptr)
    {
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

    return pNode;
}

Object* WorldSnapshot::addNode(WorldSnapshotReaderWriter::Node* pNode)
{
    const auto reader = WorldSnapshotReaderWriter::get();

    reader->addNode(pNode->id, pNode->parentId, pNode->getObjectTemplateName(), pNode->cellIndex, pNode->transform, pNode->radius, pNode->pobCRC);

    for (int i = 0; i < pNode->children->size(); ++i)
    {
        auto childNode = pNode->children->at(i);
        reader->addNode(childNode->id, childNode->parentId, childNode->getObjectTemplateName(), childNode->cellIndex, childNode->transform, childNode->radius, childNode->pobCRC);
    }

    Object* obj = createObject(pNode);
    if (obj)
    {
        obj->addToWorld();
    }

    return obj;
}

void WorldSnapshot::removeNode(WorldSnapshotReaderWriter::Node* pNode)
{
    pNode->removeNode();

    detailLevelChanged(); // Hack to update the .WS
}
}
