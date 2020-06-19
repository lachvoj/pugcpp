#include "FileTemplateLoader.hpp"

#if __GNUC__ < 8
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#elif
#include <filesystem>
namespace fs = std::filesystem;
#endif

#include <chrono>

using namespace std;

namespace pugcpp
{
namespace tmpl
{

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
    fs::exists(folderPath);
    fs::is_regular_file(folderPath);
}

long FileTemplateLoader::getLastModified(const string &name)
{
    auto tp_ms = chrono::time_point_cast<chrono::milliseconds>(fs::last_write_time(name));
    auto epoch = tp_ms.time_since_epoch();
    auto value = chrono::duration_cast<chrono::milliseconds>(epoch);

    return value.count();
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
