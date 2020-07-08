#ifndef PathHelper_hpp
#define PathHelper_hpp

#include <string>
#if __GNUC__ < 8
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#elif
#include <filesystem>
namespace fs = std::filesystem;
#endif
#include "../util/StringUtils.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
class PathHelper
{
  public:
    string resolvePath(const string &parentName, const string &templateName, const string &extension);
};
} // namespace parser
} // namespace pugcpp
#endif
