#pragma once

#include <string>

using namespace std;

namespace pugcpp
{
namespace util
{
class StringUtils
{
  public:
    static string &ltrim(string &str, const string &chars = "\t\n\v\f\r ");
    static string &rtrim(string &str, const string &chars = "\t\n\v\f\r ");
    static string &trim(string &str, const string &chars = "\t\n\v\f\r ");
    static string repeat(const string &str, int count);
    static bool startsWith(string const &fullString, string const &starting);
    static bool endsWith(string const &fullString, string const &ending);
    static string toLowerCase(const string &str);
    static string toUpperCase(const string &str);
};
} // namespace util
} // namespace pugcpp
