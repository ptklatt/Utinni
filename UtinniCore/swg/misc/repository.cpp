#include "repository.h"
#include "tree_file.h"


namespace utinni
{
static std::vector<std::string> filenames;
static std::map<std::string, Repository::DirectoryInfo> directories;

Repository::Repository()
{
    filenames = treefile::getAllFilenames();

    int startIndex = 0;
    int count = 0;
    std::string previousDir;

    for (int i = 0; i < filenames.size(); ++i)
    {
        std::string filename = filenames[i];
        std::string dir = filename.substr(0, filename.find_first_of('/'));

        if (previousDir != dir)
        {
            startIndex = i;
            count = 0;
        }
        previousDir = dir;

        count++;
        directories.insert_or_assign(dir, DirectoryInfo{ startIndex, count });
    }
}

std::vector<std::string>* Repository::getAllFilenames()
{
    return &filenames;
}

int Repository::getFilenameCount()
{
    log::info(std::to_string(filenames.size()).c_str());
    return filenames.size();
}

std::string Repository::getFilenameAt(int index)
{
    return filenames.at(index);
}

std::vector<std::string> Repository::getDirectoryFilenames(const char* directoryName)
{
    const auto dirInfo = directories.find(directoryName);
    return std::vector<std::string>(&filenames[dirInfo->second.startIndex], &filenames[dirInfo->second.startIndex + dirInfo->second.size]);
}

Repository::DirectoryInfo* Repository::getDirectoryInfo(const char* directoryName)
{
    return &directories.find(directoryName)->second;
}
}
