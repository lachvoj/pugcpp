#pragma once

#include <string>

using namespace std;

namespace util
{
class StringUtils
{
  public:
    static string &ltrim(string &str, const string &chars = "\t\n\v\f\r ");
    static string &rtrim(string &str, const string &chars = "\t\n\v\f\r ");
    static string &trim(string &str, const string &chars = "\t\n\v\f\r ");
    static string repeat(const string &str, int count);
};
} // namespace util