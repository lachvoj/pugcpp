#ifndef StringUtils_hpp
#define StringUtils_hpp

#include <algorithm>
#include <functional>
#include <list>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace pugcpp
{
namespace util
{
class StringReplacer
{
  public:
    StringReplacer() = delete;
    static string replace(const string &input, const regex &rgx, function<string(smatch &)> callback);
};

class StringUtils
{
  public:
    StringUtils() = delete;
    static string ltrim(const string &str, const string &chars = "\t\n\v\f\r ");
    static string rtrim(const string &str, const string &chars = "\t\n\v\f\r ");
    static string trim(const string &str, const string &chars = "\t\n\v\f\r ");
    static void argLtrim(string &str, const string &chars = "\t\n\v\f\r ");
    static void argRtrim(string &str, const string &chars = "\t\n\v\f\r ");
    static void argTrim(string &str, const string &chars = "\t\n\v\f\r ");
    static string repeat(const string &str, int count);
    static bool startsWith(const string &fullString, const string &starting);
    static bool endsWith(const string &fullString, const string &ending);
    static bool isNotBlank(const string &str);
    static string toLowerCase(const string &str);
    static string toUpperCase(const string &str);
    static void replaceAll(string &str, const string &fromRegex, const string &to);
    // template <typename CON>
    // static string join(const CON &container, const string &delimiter = " ");
    static string join(const vector<string> &container, const string &delimiter = " ");
    static int occurences(const string &fullString, const string &searchFor);
};
} // namespace util
} // namespace pugcpp
#endif
