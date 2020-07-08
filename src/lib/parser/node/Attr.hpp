#ifndef Attr_hpp
#define Attr_hpp

#include <any>
#include <string>

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
class Attr
{
  private:
    string name_;
    any value_;
    bool escaped_;

  public:
    Attr(const string &name, const any &value, bool escaped);

    const string &getName() const;
    any getValue() const;
    bool isEscaped();
};

} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
