/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

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
