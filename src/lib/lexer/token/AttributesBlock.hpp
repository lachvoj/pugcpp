#ifndef AttributesBlock_hpp
#define AttributesBlock_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class AttributesBlock : public Token
{
  public:
    AttributesBlock(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
