#include "./PathHelper.hpp"

namespace pugcpp
{
namespace util
{

string PathHelper::resolvePath(const string &parentName, const string &templateName, const string &extension)
{

    string filePath;
    char preferredSeparator = FileSystem::getPreferedSeparator();
    size_t psPos;
    if (StringUtils::startsWith(templateName, string(1, preferredSeparator)))
    {
        filePath = templateName.substr(1);
    }
    else
    {
        psPos = parentName.find_last_of(preferredSeparator);
        if (psPos == string::npos)
        {
            filePath = templateName;
        }
        else
        {
            string currentDir = parentName.substr(0, psPos + 1);
            filePath = currentDir + templateName;
        }
    }
    psPos = filePath.find_last_of(preferredSeparator);
    if (psPos != string::npos && psPos >= filePath.find_last_of('.'))
        filePath += "." + extension;
    if (!FileSystem::exists(filePath))
        throw Exception("File: " + filePath + " doesn't exist.");
    if (!FileSystem::isRegularFile(filePath))
        throw Exception("File: " + filePath + " is not regular file.");

    return filePath;
}
} // namespace util
} // namespace pugcpp