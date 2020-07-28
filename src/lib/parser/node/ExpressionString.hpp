#ifndef ExpressionString_hpp
#define ExpressionString_hpp

#include <string>

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
class ExpressionString
{
  private:
    string value_ = "";
    bool escape_ = false;

  public:
    ExpressionString(const string &value);
    const string &getValue() const;
    void setValue(const string &value);
    const bool isEscape() const;
    void setEscape(bool escape);
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
