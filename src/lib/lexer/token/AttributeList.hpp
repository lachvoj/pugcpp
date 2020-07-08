#ifndef AttributeList_hpp
#define AttributeList_hpp

#include <list>

#include "Attribute.hpp"
#include "Token.hpp"

using namespace std;

namespace pugcpp
{
namespace lexer
{
namespace token
{
class AttributeList : public Token
{
  private:
    list<Attribute> attributes_ = {};

  public:
    AttributeList(int lineNumber);

    const list<Attribute> &attributes() const;
    void addAttribute(const string &name, const string &value, bool escapedAttr);
    void addExpressionAttribute(const string &name, const string &expression, bool escapedAttr);
    void addBoolAttribute(const string &name, bool value);
};

} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
