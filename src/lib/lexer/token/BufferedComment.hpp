#ifndef BufferedComment_hpp
#define BufferedComment_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class BufferedComment : public Token
{
  public:
    BufferedComment(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
