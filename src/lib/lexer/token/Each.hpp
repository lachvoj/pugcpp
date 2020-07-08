#ifndef Each_hpp
#define Each_hpp

#include "Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Each : public Token
{
  private:
    string code_;
    string key_;

  public:
    Each(const string &value, int lineNumber);

    const string &code() const;
    string &code();
    const string &key() const;
    string &key();
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
