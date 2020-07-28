#ifndef Newline_hpp
#define Newline_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Newline : public Token
{
  public:
    Newline(int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
