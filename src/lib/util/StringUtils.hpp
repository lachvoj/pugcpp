#ifndef StringUtils_hpp
#define StringUtils_hpp

#include <algorithm>
#include <string>

using namespace std;

namespace pugcpp
{
namespace util
{
class StringUtils
{
  private:
    StringUtils();

  public:
    static string &ltrim(string &str, const string &chars = "\t\n\v\f\r ");
    static string &rtrim(string &str, const string &chars = "\t\n\v\f\r ");
    static string &trim(string &str, const string &chars = "\t\n\v\f\r ");
    static string repeat(const string &str, int count);
    static bool startsWith(string const &fullString, string const &starting);
    static bool endsWith(string const &fullString, string const &ending);
    static string toLowerCase(const string &str);
    static string toUpperCase(const string &str);
    static void replace(string &str, const string &from, const string &to);
};
} // namespace util
} // namespace pugcpp
#endif
