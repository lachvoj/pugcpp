#ifndef Outdent_hpp
#define Outdent_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Outdent : public Token
{
  public:
    Outdent(int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
