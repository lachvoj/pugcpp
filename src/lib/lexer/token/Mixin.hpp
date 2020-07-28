#ifndef Mixin_hpp
#define Mixin_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Mixin : public Token
{
  private:
    string arguments_;

  public:
    Mixin(const string &value, int lineNumber);

    const string &getArguments() const;
    void setArguments(const string &arguments);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
