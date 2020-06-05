#include "StringUtils.hpp"

namespace util
{
string &StringUtils::ltrim(string &str, const string &chars /*= "\t\n\v\f\r "*/)
{
    str.erase(0, str.find_first_not_of(chars));

    return str;
}

string &StringUtils::rtrim(string &str, const string &chars /*= "\t\n\v\f\r "*/)
{
    str.erase(str.find_last_not_of(chars) + 1);

    return str;
}

string &StringUtils::trim(string &str, const string &chars /*= "\t\n\v\f\r "*/)
{
    return ltrim(rtrim(str, chars), chars);
}

string StringUtils::repeat(const string &str, int count)
{
    string ret = "";
    for (int i = 0; i < count; ++i)
    {
        ret += str;
    }

    return ret;
}
} // namespace util
