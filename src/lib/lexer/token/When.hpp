#ifndef When_hpp
#define When_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class When : public Token
{
  public:
    When(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
