#ifndef Block_hpp
#define Block_hpp

#include "../../util/StringUtils.hpp"

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
using namespace util;

class Block : public Token
{
  public:
    enum E_MODE
    {
        REPLACE = 0,
        PREPEND,
        APPEND
    };

  private:
    E_MODE mode_ = REPLACE;

  public:
    Block(const string &value, int lineNumber);
    E_MODE getMode() const;
    void setMode(const string &mode);
    void setMode(E_MODE mode);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
