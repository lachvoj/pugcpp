#ifndef FileSystem_hpp
#define FileSystem_hpp

#include <chrono>
#include <string>

#if __GNUC__ < 8
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#elif
#include <filesystem>
namespace fs = std::filesystem;
#endif
using namespace std;

namespace pugcpp
{
namespace util
{
class FileSystem
{
  public:
    FileSystem() = delete;
    static bool exists(const string &path);
    static bool isRegularFile(const string &path);
    static bool isDirectory(const string &path);
    static string getExtension(const string &path);
    static long lastModified(const string &path);
    static char getPreferedSeparator();
};
} // namespace util
} // namespace pugcpp
#endif
