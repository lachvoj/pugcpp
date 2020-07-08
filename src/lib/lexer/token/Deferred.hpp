#ifndef Deferred_hpp
#define Deferred_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Deferred : public Token
{
  public:
    Deferred(const string &value, int lineNumber);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
