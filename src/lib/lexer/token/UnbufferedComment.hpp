#ifndef UnbufferedComment_hpp
#define UnbufferedComment_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class UnbufferedComment : public Token
{
  public:
    UnbufferedComment(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
