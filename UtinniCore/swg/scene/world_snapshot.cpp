#include "world_snapshot.h"
#include <filesystem>
#include "ground_scene.h"
#include "swg/appearance/appearance.h"
#include "swg/misc/network.h"
#include "swg/object/object.h"
#include "swg/object/client_object.h"
#include "swg/game/game.h"
#include "swg/appearance/portal.h"
#include "utility/string_utility.h"

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
using pGetNodeSpatialSubdivisionHandle = swgptr(__thiscall*)(utinni::WorldSnapshotReaderWriter::Node* pThis);
using pSetNodeSpatialSubdivisionHandle = void(__thiscall*)(utinni::WorldSnapshotReaderWriter::Node* pThis, swgptr handle);

using pRemoveFromWorld = void(__thiscall*)(utinni::WorldSnapshotReaderWriter::Node* pThis);

pGetNodeNetworkId getNodeNetworkId = (pGetNodeNetworkId)0x00B971D0;
pGetNodeSpatialSubdivisionHandle getNodeSpatialSubdivisionHandle = (pGetNodeSpatialSubdivisionHandle)0x00B97390;
pSetNodeSpatialSubdivisionHandle setNodeSpatialSubdivisionHandle = (pSetNodeSpatialSubdivisionHandle)0x00B973A0;

pRemoveFromWorld removeFromWorld = (pRemoveFromWorld)0x00B97440;

}
}

namespace swg::worldsnapshot
{
using pLoad = void(__cdecl*)(const char* name);
using pUnload = void(__cdecl*)();

using pClearPreloadList = char(__cdecl*)(swgptr, swgptr, swgptr);

using pCreateObject = swgptr(__cdecl*)(utinni::WorldSnapshotReaderWriter* reader, utinni::WorldSnapshotReaderWriter::Node* node, swgptr result);
using pAddObject = void(__cdecl*)(swgptr object, swgptr node);

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
    Node* result = nullptr;
    for (int i = 0; i < nodeList->size(); ++i)
    {
        Node* node = nodeList->at(i);
        if (node->id == id)
        {
            result = node;
            break;
        }
    }
    return result;
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::getNodeById(int id, Object* parentObject)
{
    if (parentObject == nullptr)
    {
        return getNodeById(id);
    }
    else
    {
        return getNodeByIdWithParent(parentObject, id);
    }
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::findChildNode(Node* parentNode, int id)
{
    Node* result = nullptr;

    for (int i = 0; i < parentNode->children->size(); ++i)
    {
        Node* child = parentNode->children->at(i);
        if (child->id == id)
        {
            result = child;
            break;
        }
    }

    if (result == nullptr)
    {
        for (int i = 0; i < parentNode->children->size(); ++i)
        {
            Node* child = parentNode->children->at(i);

            if (child->children != nullptr && !child->children->empty())
            {
                Node* childResult = findChildNode(child, id);
                if (childResult != nullptr && childResult->id == id)
                {
                    result = childResult;
                    break;
                }
            }
        }
    }

    return result;
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::getNodeByIdWithParent(Object* parentObject, int id)
{
    Node* result = nullptr;

    Object* topParent = parentObject;

    while (true)
    {
        if (topParent->parentObject == nullptr)
        {
            break;
        }

        topParent = topParent->parentObject;
    }

    Node* parentNode = getNodeById(topParent->networkId);

    result = findChildNode(parentNode, id);

    return result;
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::getNodeByNetworkId(int networkId)
{
    return swg::worldSnapshotReaderWriter::getNodeByNetworkId(this, networkId);
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::getNodeAt(int index)
{
    return swg::worldSnapshotReaderWriter::getNodeByIndex(this, index);
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::getLastNode()
{
    return nodeList->back();
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::addNode(int nodeId, int parentNodeId, const char* objectFilename, int cellId, const swg::math::Transform& transform, float radius, unsigned int pobCrc)
{
    // For some reason, the ptr is wrong if parentNodeId is 0 and it's actually 'result - 4' to get the accurate pointer

    swgptr node;
    if (parentNodeId == 0)
    {
        node = swg::worldSnapshotReaderWriter::addNode(this, nodeId, parentNodeId, *ConstCharCrcString::ctor(objectFilename), cellId, transform, radius, pobCrc) - 4;  // That's why we subtract 4 here
    }
    else
    {
        node = swg::worldSnapshotReaderWriter::addNode(this, nodeId, parentNodeId, *ConstCharCrcString::ctor(objectFilename), cellId, transform, radius, pobCrc); // If it's added to a parentNode, it seems fine
    }

    // Upon further testing, the ptr returned isn't reliable, unsure why
    // return memory::read<Node*>(node);
    return nullptr;
}

void WorldSnapshotReaderWriter::Node::removeNode()
{
    if (!Game::isSafeToUse())
    {
        return;
    }

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

        for (int i = 0; i < parentNode->children->size(); ++i)
        {
            if (parentNode->children->at(i)->id == id)
            {
                parentNode->children->erase(parentNode->children->begin() + i);
                break;
            }
        }
    }

    Object* nodeObject = Network::getObjectById(id);

    // Need to nullptr check because only loaded objects are non null, ie in range or previously 'seen'
    // and the loop goes through all nodes in the entire .WS
    if (nodeObject != nullptr)
    {
        nodeObject->remove();
    }

    swg::worldSnapshotReaderWriter::removeNode(WorldSnapshotReaderWriter::get(), id);
}

void WorldSnapshotReaderWriter::Node::removeNodeFull() // WIP - Messy IDA pseudo code
{
    if (!Game::isSafeToUse())
    {
        return;
    }

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

    }

    Object* nodeObject = Network::getObjectById(id);

    // Need to nullptr check because only loaded objects are non null, ie in range or previously 'seen'
    // and the loop goes through all nodes in the entire .WS
    if (nodeObject != nullptr)
    {
        nodeObject->remove();
    }
    swg::worldSnapshotReaderWriter::node::removeFromWorld(this);
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

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::Node::getChildById(int id)
{
    Node* result = nullptr;

    for (int i = 0; i < children->size(); ++i)
    {
        Node* node = children->at(i);
        if (node->id == id)
        {
            result = node;
            break;
        }
    }

    return result;
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::Node::getChildAt(int index)
{
    return children->at(index);
}

WorldSnapshotReaderWriter::Node* WorldSnapshotReaderWriter::Node::getLastChild()
{
    return children->back();
}

void WorldSnapshot::load(const std::string& name)
{
    if (name.empty())
    {
        return;
    }

    memory::nopAddress(0x0059C3F3, 6); // Removes the grabbing of current .trn name to allow the loading of any .ws

    swg::worldsnapshot::load(name.c_str());
}

void WorldSnapshot::unload() 
{
    if (!Game::isSafeToUse())
    {
        return;
    }

    auto readerWriter = WorldSnapshotReaderWriter::get();
    for (int i = 0; i < readerWriter->getNodeCount(); ++i)
    {
        readerWriter->getNodeAt(i)->removeNodeFull();
    }

    swg::worldsnapshot::unload();
}

void WorldSnapshot::reload()
{
    unload();

    load(GroundScene::get()->getName());
}

void WorldSnapshotReaderWriter::clearPreloadList(swgptr unk1, swgptr unk2, swgptr unk3)
{
    swg::worldsnapshot::clearPreloadList(unk1, unk2, unk3);
}

void WorldSnapshotReaderWriter::saveFile(const char* snapshotName)
{
    CreateDirectory((utility::getWorkingDirectory() + "/snapshot/").c_str(), nullptr);

    if (constCharUtility::isEmpty(snapshotName))
    {
        swg::worldSnapshotReaderWriter::saveFile(this, ("snapshot/" + GroundScene::get()->getName() + ".ws").c_str());
    }
    else
    {

        swg::worldSnapshotReaderWriter::saveFile(this, ("snapshot/" + std::string(snapshotName) + ".ws").c_str());
    }
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

Object* createObject(WorldSnapshotReaderWriter::Node* node)
{
    DWORD errorCode = 0;
    return (Object*)swg::worldsnapshot::createObject(WorldSnapshotReaderWriter::get(), node, errorCode);
}

bool WorldSnapshot::isValidObject(const char* objectFilename)
{
    if (strstr(objectFilename, "/base/"))
    {
        return false;
    }

    ClientObject* cobj = ObjectTemplate::createObject(objectFilename)->getClientObject();

    if (cobj == 0 || cobj->getCreatureObject() != 0 || cobj->getShipObject() != 0 || (cobj != 0 && cobj->getTangibleObject() == 0 && cobj->getStaticObject() == 0))
    {
        return false;
    }

    cobj->remove();
    cobj = nullptr; // ToDo does this need to be dealloc instead?

    return true;
}

// ToDo move duplicated code in the following functions to shared function

WorldSnapshotReaderWriter::Node* WorldSnapshot::createAddNode(const char* objectFilename, swg::math::Transform& transform)
{
   /* if (!isValidObject(objectFilename))
    {
        return nullptr;
    }*/

    const auto reader = WorldSnapshotReaderWriter::get();


    WorldSnapshotReaderWriter::Node* parentNode = nullptr;


    // Temporary check to get parent, make this better
    int parentNodeId = 0;
    Camera* camera = GroundScene::get()->getCurrentCamera(); // If camera is outside of the POB and the new node to be created is inside, it crashes as parentObject is nullptr
    if (camera->parentObject != nullptr)
    {
        parentNode = reader->getNodeById(camera->parentObject->networkId, camera->parentObject->parentObject);
        if (parentNode == nullptr)
        {
            return nullptr;
        }

        parentNodeId = parentNode->id;
    }

    if (camera->parentObject != nullptr && parentNode == nullptr)
    {
        return nullptr;
    }

    auto objectTemplate = ObjectTemplateList::getObjectTemplateByFilename(objectFilename);

    const char* pobFilename = ObjectTemplateList::getObjectTemplateByFilename(objectFilename)->getPortalLayoutFilename();
    if (!objectTemplate->getAppearanceFilename() && !objectTemplate->getClientDataFilename() && !pobFilename)
    {
        return nullptr;
    }

    // Check if the object contains cells
    int pobCrc = 0;
    int pobCellCount = 0;
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
    WorldSnapshotReaderWriter::Node* node;
    if (parentNode == nullptr)
    {
        node = reader->nodeList->back();
    }
    else
    {
        node = parentNode->children->back();
    }

    Object* obj = createObject(node);
    if (obj)
    {
        obj->addToWorld();
    }

    return node;
}

WorldSnapshotReaderWriter::Node* WorldSnapshot::createNodeCopy(WorldSnapshotReaderWriter::Node* originalNode, swg::math::Transform& transform)
{
    const auto reader = WorldSnapshotReaderWriter::get();

    highestId++;
    const int id = highestId;
    reader->addNode(id, originalNode->parentId, originalNode->getObjectTemplateName(), originalNode->cellIndex, transform, originalNode->radius, originalNode->pobCRC);

    if (originalNode->children != nullptr)
    {
        for (int i = 0; i < originalNode->children->size(); ++i)
        {
            highestId = id + i + 1;
            const auto childNode = originalNode->children->at(i);
            reader->addNode(highestId, id, childNode->getObjectTemplateName(), childNode->cellIndex, swg::math::Transform(childNode->transform), childNode->radius, childNode->pobCRC);
        }
    }

    // Workaround to the unreliable ptr return of reader->addNode
    WorldSnapshotReaderWriter::Node* node;
    if (originalNode->parentNode == nullptr)
    {
        node = reader->nodeList->back();
    }
    else
    {
        node = originalNode->parentNode->children->back();
    }

    Object* obj = createObject(node);
    if (obj)
    {
        obj->addToWorld();
    }

    return node;
}

Object* WorldSnapshot::addNode(WorldSnapshotReaderWriter::Node* node)
{
    const auto reader = WorldSnapshotReaderWriter::get();

    reader->addNode(node->id, node->parentId, node->getObjectTemplateName(), node->cellIndex, node->transform, node->radius, node->pobCRC);

    if (node->children != nullptr)
    {
        for (int i = 0; i < node->children->size(); ++i)
        {
            const auto childNode = node->children->at(i);
            reader->addNode(childNode->id, childNode->parentId, childNode->getObjectTemplateName(), childNode->cellIndex, childNode->transform, childNode->radius, childNode->pobCRC);
        }
    }

    Object* obj = createObject(node);
    if (obj)
    {
        obj->addToWorld();
    }

    return obj;
}

void WorldSnapshot::removeNode(WorldSnapshotReaderWriter::Node* node)
{
    node->removeNode();

    detailLevelChanged(); // Hack to update the .WS
}
}
