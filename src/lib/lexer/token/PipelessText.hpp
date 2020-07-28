#ifndef PipelessText_hpp
#define PipelessText_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class PipelessText : public Token
{
  public:
    PipelessText(int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
