#ifndef Assignment_hpp
#define Assignment_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{

class Assignment : public Token
{
  public:
    Assignment(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
