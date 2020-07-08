#ifndef Colon_hpp
#define Colon_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Colon : public Token
{
  public:
    Colon(int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
