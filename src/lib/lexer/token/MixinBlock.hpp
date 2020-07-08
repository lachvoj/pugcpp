#ifndef MixinBlock_hpp
#define MixinBlock_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class MixinBlock : public Token
{
  public:
    MixinBlock(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
