#ifndef While_hpp
#define While_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class While : public Token
{
  public:
    While(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
