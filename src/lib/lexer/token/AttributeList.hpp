#pragma once

#include <list>

#include "Attribute.hpp"
#include "Token.hpp"

using namespace std;

namespace token
{
class AttributeList : Token
{
  private:
    list<Attribute> attributes_ = {};

  public:
    AttributeList(int lineNumber);
    ~AttributeList();

    const list<Attribute> &attributes() const;
    void addAttribute(const string &name, const string &value, bool escapedAttr);
    void addExpressionAttribute(const string &name, const string &expression, bool escapedAttr);
    void addBoolAttribute(const string &name, bool value);
};

} // namespace token