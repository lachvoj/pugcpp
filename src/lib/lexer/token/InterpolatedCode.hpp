#ifndef InterpolatedCode_hpp
#define InterpolatedCode_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class InterpolatedCode : public Token
{
  public:
    InterpolatedCode(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
