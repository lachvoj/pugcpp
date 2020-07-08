#include "./FileTemplateLoader.hpp"

using namespace std;

namespace pugcpp
{
namespace tmpl
{

using namespace util;

FileTemplateLoader::FileTemplateLoader(const string &folderPath, const string &encoding)
: folderPath_(folderPath), encoding_(encoding)
{
    validateFolderPath(folderPath);
}

FileTemplateLoader::FileTemplateLoader(const string &folderPath, const string &encoding, const string &extension)
: folderPath_(folderPath), encoding_(encoding), extension_(extension)
{
    validateFolderPath(folderPath);
}

void FileTemplateLoader::validateFolderPath(const string &folderPath)
{
    FileSystem::exists(folderPath);
    FileSystem::isRegularFile(folderPath);
}

long FileTemplateLoader::getLastModified(const string &name)
{
    return FileSystem::lastModified(name);
}

istream &FileTemplateLoader::getReader(const string &name)
{
    reader_.open(name);

    return (istream &)reader_;
}

const string &FileTemplateLoader::getExtension() const
{
    return extension_;
}

} // namespace tmpl
} // namespace pugcpp
