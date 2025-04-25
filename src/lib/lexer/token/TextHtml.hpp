#ifndef TextHtml_hpp
#define TextHtml_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class TextHtml : public Token
{
  public:
    TextHtml(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
