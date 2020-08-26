#include "tree_file.h"
#include <set>

namespace swg::treefile
{
using pSearchTree = swgptr(__thiscall*)(swgptr pThis, int priority, const char* treeFilename);

pSearchTree searchTree = (pSearchTree)0xA992E0;
}

namespace utinni::treefile
{
static std::set<std::string> filenames;
std::vector<std::string> getAllFilenames()
{
    std::vector<std::string> result;
    result.reserve(filenames.size());
    for (auto it = filenames.begin(); it != filenames.end(); ) 
    {
        result.push_back(std::move(filenames.extract(it++).value()));
    }
    filenames.clear();
    return result;
}

swgptr __fastcall hkSearchTree(swgptr pThis, DWORD EDX, int priority, const char* treeFilename)
{
    swg::treefile::searchTree(pThis, priority, treeFilename);

    const int fileCount = memory::read<int>(pThis + 0x14);
    char* filenamesBuffer = memory::read<char*>(pThis + 0x18);

    uint32_t offset = 0;
    for (int i = 0; i < fileCount; ++i)
    {
        std::string filename = std::string(filenamesBuffer + offset);
        offset += filename.length() + 1;

        filenames.emplace(filename);
    }
    
    return pThis;
}

void detour()
{
    swg::treefile::searchTree = (swg::treefile::pSearchTree)Detour::Create(swg::treefile::searchTree, hkSearchTree, DETOUR_TYPE_PUSH_RET);
}
}
