#ifndef BlockCode_hpp
#define BlockCode_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class BlockCode : public Token
{
  public:
    BlockCode(int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
