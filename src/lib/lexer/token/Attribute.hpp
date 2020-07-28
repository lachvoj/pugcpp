#ifndef Attribute_hpp
#define Attribute_hpp

#include <any>
#include <string>

using namespace std;
namespace pugcpp
{
namespace lexer
{
namespace token
{
class Attribute
{
  private:
    string name_;
    any value_;
    bool escaped_;

  public:
    Attribute(const string &name, const any &value, bool escape);

    const string &getName() const;
    const any &getValue() const;
    const bool isEscaped() const;
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
