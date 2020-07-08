#include "./StringUtils.hpp"

namespace pugcpp
{

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

bool StringUtils::startsWith(string const &fullString, string const &starting)
{
    return (fullString.rfind(starting, 0) == 0);
}

bool endsWith(string const &fullString, string const &ending)
{
    if (fullString.length() >= ending.length())
    {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    return false;
}

string StringUtils::toLowerCase(const string &str)
{
    string ret = str;
    for_each(ret.begin(), ret.end(), [](char &c) { c = ::tolower(c); });

    return ret;
}

string StringUtils::toUpperCase(const string &str)
{
    string ret = str;
    for_each(ret.begin(), ret.end(), [](char &c) { c = ::toupper(c); });

    return ret;
}

void StringUtils::replace(string &str, const string &from, const string &to)
{
    if (from.empty())
        return;

    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

} // namespace util
} // namespace pugcpp
