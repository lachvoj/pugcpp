#ifndef PugCpp_hpp
#define PugCpp_hpp

#include <any>
#include <map>
#include <string>

using namespace std;

namespace pugcpp
{
class PugCpp
{
  public:
    enum Mode
    {
        HTML,
        XML,
        XHTML
    };

    static string render(const string &filename, map<string, any> *model, bool prettyPrint = true, Mode = HTML);
};
} // namespace pugcpp
#endif
