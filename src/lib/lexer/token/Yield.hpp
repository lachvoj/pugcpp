#ifndef Yield_hpp
#define Yield_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Yield : public Token
{
  public:
    Yield(int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
