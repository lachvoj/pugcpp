#ifndef PathHelper_hpp
#define PathHelper_hpp

#include <string>

#include "../exceptions/Exception.hpp"

#include "FileSystem.hpp"
#include "StringUtils.hpp"

using namespace std;

namespace pugcpp
{
namespace util
{
using namespace exceptions;

class PathHelper
{
  public:
    PathHelper() = delete;
    static string resolvePath(const string &parentName, const string &templateName, const string &extension);
};
} // namespace util
} // namespace pugcpp
#endif
