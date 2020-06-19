#pragma once

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

    const string &name() const;
    const any &value() const;
    const bool escaped() const;
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
