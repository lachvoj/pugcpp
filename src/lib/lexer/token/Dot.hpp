#ifndef Dot_hpp
#define Dot_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Dot : public Token
{
  public:
    Dot(int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
