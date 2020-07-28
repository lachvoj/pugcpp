#ifndef AttributeList_hpp
#define AttributeList_hpp

#include <any>
#include <vector>

#include "../../parser/node/ExpressionString.hpp"

#include "Attribute.hpp"
#include "Token.hpp"

using namespace std;

namespace pugcpp
{
namespace lexer
{
namespace token
{
using namespace parser::node;

class AttributeList : public Token
{
  private:
    vector<Attribute> attributes_;

  public:
    AttributeList(int lineNumber);

    const vector<Attribute> &getAttributes() const;
    void addAttribute(const string &name, const string &value, bool escapedAttr);
    void addExpressionAttribute(const string &name, const string &expression, bool escapedAttr);
    void addBoolAttribute(const string &name, bool value);
};

} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
