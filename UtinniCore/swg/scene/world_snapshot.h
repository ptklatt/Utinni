#pragma once

#include "utinni.h"
#include "swg/misc/swg_math.h"

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
        DWORD* pSpatialSubdivisionHandle;
        float distanceSquaredTo;
        bool isInWorld;

        void removeNode();
        void removeNodeFull();

        int64_t getNodeNetworkId();
        DWORD getNodeSpatialSubdivisionHandle();
        void setNodeSpatialSubdivisionHandle(DWORD handle);
    };

    std::vector<Node*>* nodeList;
    std::vector<char*>* objectTemplateNameList;
    std::unordered_map<int, int>* objectTemplateCrcMap;
    std::map<int64_t, Node*>* networkIdMap;

    static WorldSnapshotReaderWriter* get();

    void clear();
    static void clearPreloadList(DWORD unk1, DWORD unk2, DWORD unk3);
    void saveFile();

    const char* getObjectTemplateName(int objectTemplateNameIndex);

    int getNodeCount();
    int getNodeCountTotal();

    Node* getNodeByNetworkId(int64_t networkId);
    Node* getNodeByIndex(int nodeId);

    Node* addNode(int nodeId, int parentNodeId, const char* objectFilename, int cellId, const swg::math::Transform& transform, float radius, unsigned int pobCrc);


};
}

namespace utinni
{
class UTINNI_API WorldSnapshot
{
public:
    static void load(const char* name);
    static void unload();
    static void reload();

    static bool getPreloadSnapshot();
    static void setPreloadSnapshot(bool preloadSnapshot);

    static void detailLevelChanged();

    static void createNewNode(const char* objectFilename, swg::math::Transform& transform);
    static void removeNode(WorldSnapshotReaderWriter::Node* pNode);
};
}