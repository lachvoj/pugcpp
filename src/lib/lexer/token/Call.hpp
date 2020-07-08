#ifndef Call_hpp
#define Call_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Call : public Token
{
  private:
    string arguments_;

  public:
    Call(const string &value, int lineNumber);

    string &arguments();
    const string &arguments() const;
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
