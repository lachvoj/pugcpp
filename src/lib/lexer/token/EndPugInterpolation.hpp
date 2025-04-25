#ifndef EndPugInterpolation_hpp
#define EndPugInterpolation_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class EndPugInterpolation : public Token
{
  public:
    EndPugInterpolation(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
