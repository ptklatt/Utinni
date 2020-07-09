#pragma once

#include "utinni.h"

namespace utinni
{

class UTINNI_API Repository
{
public:

    struct DirectoryInfo
    {
        int startIndex;
        int size;
    };

    Repository();

    std::vector<std::string>* getAllFilenames();
    int getFilenameCount();
    std::string getFilenameAt(int index);

    std::vector<std::string> getDirectoryFilenames(const char* directoryName);
    DirectoryInfo* getDirectoryInfo(const char* directoryName);
};

}
