#ifndef ElseIf_hpp
#define ElseIf_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class ElseIf : public Token
{
  public:
    ElseIf(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
