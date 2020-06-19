#pragma once

#include <string>

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
