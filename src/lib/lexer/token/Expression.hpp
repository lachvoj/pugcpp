#ifndef Expression_hpp
#define Expression_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Expression : public Token
{
  private:
    bool escape_;

  public:
    Expression(const string &value, int lineNumber, bool escape = false);

    const bool isEscape() const;
    void setEscape(bool escape);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
