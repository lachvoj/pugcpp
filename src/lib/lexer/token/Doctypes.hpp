#ifndef Doctypes_hpp
#define Doctypes_hpp

#include <map>
#include <string>

using namespace std;

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Doctypes
{

  private:
    static const map<string, string> s_conTypeMap;
    static const string s_sEmpty;

  public:
    Doctypes() = delete;
    static const string &get(const string &pugDocType);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
