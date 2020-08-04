#ifndef ArgumentSplitter_hpp
#define ArgumentSplitter_hpp

#include <list>
#include <string>

#include "StringUtils.hpp"

using namespace std;

namespace pugcpp
{
namespace util
{
class ArgumentSplitter
{
  private:
    static const char ARGUMENT_DELIMITER = ',';

    static const bool isClosingBraces(const char ch);
    static const bool isOpeningBraces(const char ch);
    static const bool isQuoted(const char ch);
    static void addArgument(vector<string> &ret, string &argument);

  public:
    ArgumentSplitter() = delete;

    static void split(vector<string> &ret, const string &arguments);
};
} // namespace util
} // namespace pugcpp

#endif // ArgumentSplitter_hpp
