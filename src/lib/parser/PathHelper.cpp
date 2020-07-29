#include "./PathHelper.hpp"

namespace pugcpp
{
namespace parser
{
using namespace util;

string PathHelper::resolvePath(const string &parentName, const string &templateName, const string &extension)
{

    string filePath;
    if (StringUtils::startsWith(templateName, string(1, fs::path::preferred_separator)))
    {
        filePath = templateName.substr(1);
    }
    else
    {
        if (parentName.find(fs::path::preferred_separator) == string::npos)
        {
            filePath = templateName;
        }
        else
        {
            // TODO:: check path
            string currentDir = parentName.substr(0, parentName.find_last_of(fs::path::preferred_separator) + 1);
            filePath = currentDir + templateName;
        }
        if (filePath.find_last_of(fs::path::preferred_separator) >= filePath.find_last_of("."))
            filePath += "." + extension;

        return filePath;
    }
}
} // namespace parser
} // namespace pugcpp