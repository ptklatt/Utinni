#pragma once

#include "utinni.h"
#include "swg/misc/swg_math.h"
#include "swg/object/object.h"

namespace utinni
{
class UTINNI_API WorldSnapshotReaderWriter
{
public:
    class UTINNI_API Node
    {
    public:
        bool isDeleted;
        int id;
        int parentId;
        int objectTemplateNameIndex;
        int cellIndex;
        swg::math::Transform transform;
        float radius;
        int pobCRC;
        Node* parentNode;
        std::vector<Node*>* children;
        swgptr pSpatialSubdivisionHandle;
        float distanceSquaredTo;
        bool isInWorld;

        void removeNode();
        void removeNodeFull();

        int64_t getNodeNetworkId();
        swgptr getNodeSpatialSubdivisionHandle();
        void setNodeSpatialSubdivisionHandle(swgptr handle);

        const char* getObjectTemplateName() const;

        int getChildCount() const;
        Node* getChildById(int id);
        Node* getChildAt(int index);
        Node* getLastChild();
    };

    std::vector<Node*>* nodeList;
    std::vector<char*>* objectTemplateNameList;
    std::unordered_map<int, int>* objectTemplateCrcMap;
    std::map<int, Node*>* networkIdMap;

    static WorldSnapshotReaderWriter* get();

    void clear();
    static void clearPreloadList(swgptr unk1, swgptr unk2, swgptr unk3);
    void saveFile(const char* snapshotName = "");

    const char* getObjectTemplateName(int objectTemplateNameIndex);

    int getNodeCount();
    int getNodeCountTotal();

    Node* getNodeById(int id);
    Node* getNodeById(int id, Object* parentObject);
    Node* findChildNode(Node* parentNode, int id);
    Node* getNodeByIdWithParent(Object* parentObject, int id);
    Node* getNodeByNetworkId(int networkId);
    Node* getNodeAt(int index);
    Node* getLastNode();

    Node* addNode(int nodeId, int parentNodeId, const char* objectFilename, int cellId, const swg::math::Transform& transform, float radius, unsigned int pobCrc);
};

}

namespace utinni
{
class UTINNI_API WorldSnapshot
{
public:
    static void load(const std::string& name);
    static void unload();
    static void reload();

    static bool getPreloadSnapshot();
    static void setPreloadSnapshot(bool preloadSnapshot);

    static void detailLevelChanged();

    static int generateHighestId();

    static bool isValidObject(const char* objectFilename);
    static WorldSnapshotReaderWriter::Node* createAddNode(const char* objectFilename, swg::math::Transform& transform);
    static WorldSnapshotReaderWriter::Node* createNodeCopy(WorldSnapshotReaderWriter::Node* originalNode, swg::math::Transform& transform);

    static Object* addNode(WorldSnapshotReaderWriter::Node* node);
    static void removeNode(WorldSnapshotReaderWriter::Node* node);
};
}
