#ifndef StartPugInterpolation_hpp
#define StartPugInterpolation_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class StartPugInterpolation : public Token
{
  public:
    StartPugInterpolation(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
