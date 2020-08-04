#include "./FileTemplateLoader.hpp"

using namespace std;

namespace pugcpp
{
namespace tmpl
{

using namespace util;

FileTemplateLoader::FileTemplateLoader(const string &folderPath, const string &encoding)
: encoding_(encoding), folderPath_(folderPath)
{
    validateFolderPath(folderPath);
}

FileTemplateLoader::FileTemplateLoader(const string &folderPath, const string &encoding, const string &extension)
: encoding_(encoding), folderPath_(folderPath), extension_(extension)
{
    validateFolderPath(folderPath);
}

void FileTemplateLoader::validateFolderPath(const string &folderPath)
{
    if (!FileSystem::exists(folderPath) || !FileSystem::isDirectory(folderPath))
        throw invalid_argument("The folder path '" + folderPath + "' does not exist");
}

long FileTemplateLoader::getLastModified(const string &name)
{
    return FileSystem::lastModified(name);
}

unique_ptr<istream> FileTemplateLoader::getReader(const string &name)
{
    unique_ptr<ifstream> rd = make_unique<ifstream>();
    rd->open(name);

    return rd;
}

const string &FileTemplateLoader::getExtension() const
{
    return extension_;
}

} // namespace tmpl
} // namespace pugcpp
