#ifndef If_hpp
#define If_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class If : public Token
{
  private:
    bool inverseCondition_;
    bool alternativeCondition_;

  public:
    If(const string &value, int lineNumber, bool inverseCondition = false, bool alternativeCondition = false);

    const bool isInverseCondition() const;
    void setInverseCondition(bool inverseCondition);
    const bool isAlternativeCondition() const;
    void setAlternativeCondition(bool alternativeCondition);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
