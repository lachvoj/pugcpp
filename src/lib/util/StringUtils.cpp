#include "./StringUtils.hpp"

namespace pugcpp
{

namespace util
{
string StringReplacer::replace(const string &input, const regex &rgx, function<string(smatch &)> callback)
{
    string ret = "";
    string in = input;
    smatch matcher;

    while (regex_search(in, matcher, rgx))
    {
        ret += matcher.prefix();
        ret += callback(matcher);
        in = matcher.suffix();
    }
    ret += in;

    return ret;
}

string StringUtils::ltrim(const string &str, const string &chars /*= "\t\n\v\f\r "*/)
{
    string s = str;
    argLtrim(s);

    return s;
}

string StringUtils::rtrim(const string &str, const string &chars /*= "\t\n\v\f\r "*/)
{
    string s = str;
    argRtrim(s);

    return s;
}

string StringUtils::trim(const string &str, const string &chars /*= "\t\n\v\f\r "*/)
{
    string s = str;
    argLtrim(s, chars);
    argRtrim(s, chars);

    return s;
}

void StringUtils::argLtrim(string &str, const string &chars /*= "\t\n\v\f\r "*/)
{
    str.erase(0, str.find_first_not_of(chars));
}

void StringUtils::argRtrim(string &str, const string &chars /*= "\t\n\v\f\r "*/)
{
    str.erase(str.find_last_not_of(chars) + 1);
}

void StringUtils::argTrim(string &str, const string &chars /*= "\t\n\v\f\r "*/)
{
    argLtrim(str, chars);
    argRtrim(str, chars);
}

string StringUtils::repeat(const string &str, int count)
{
    string ret;
    ret.reserve(str.length() * count);

    for (int i = 0; i < count; ++i)
    {
        ret += str;
    }

    return ret;
}

bool StringUtils::startsWith(const string &fullString, const string &starting)
{
    return (fullString.rfind(starting, 0) == 0);
}

bool StringUtils::endsWith(const string &fullString, const string &ending)
{
    if (fullString.length() >= ending.length())
    {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    return false;
}
bool StringUtils::isNotBlank(const string &str)
{
    return !trim(str).empty();
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

void StringUtils::replaceAll(string &str, const string &from, const string &to)
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

// template <typename CON>
// string StringUtils::join(const CON &container, const string &delimiter)
// {
//     static_assert(
//         is_same<CON, vector<string>>::value || is_same<CON, set<string>>::value || is_same<CON,
//         list<string>>::value);

//     string ret = "";
//     for (auto it = container.begin(); it < container.end(); ++it)
//     {
//         ret += *it;
//         if (it != container.end() - 1)
//             ret += delimiter;
//     }
// }

string StringUtils::join(const vector<string> &container, const string &delimiter)
{
    string ret = "";
    for (auto it = container.begin(); it < container.end(); ++it)
    {
        ret += *it;
        if (it != container.end() - 1)
            ret += delimiter;
    }

    return ret;
}

int StringUtils::occurences(const string &fullString, const string &searchFor)
{
    int ret = 0;
    string::size_type pos = 0;

    while ((pos = fullString.find(searchFor, pos)) != string::npos)
    {
        ++ret;
        pos += searchFor.length();
    }

    return ret;
}

} // namespace util
} // namespace pugcpp
