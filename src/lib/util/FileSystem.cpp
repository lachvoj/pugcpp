#include "./FileSystem.hpp"

namespace pugcpp
{
namespace util
{
bool FileSystem::exists(const string &path)
{
    return fs::exists(path);
}

bool FileSystem::isRegularFile(const string &path)
{
    return fs::is_regular_file(path);
}

bool FileSystem::isDirectory(const string &path)
{
    return fs::is_directory(path);
}

string FileSystem::getExtension(const string &path)
{
    return fs::path(path).extension();
}

long FileSystem::lastModified(const string &path)
{
    auto tp_ms = chrono::time_point_cast<chrono::milliseconds>(fs::last_write_time(path));
    auto epoch = tp_ms.time_since_epoch();
    auto value = chrono::duration_cast<chrono::milliseconds>(epoch);

    return value.count();
}

char FileSystem::getPreferedSeparator()
{
    return fs::path::preferred_separator;
}

} // namespace util
} // namespace pugcpp