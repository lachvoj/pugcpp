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
    Each(const string &value, int lineNumber, const string &key, const string &code);

    const string &getCode() const;
    void setCode(const string &code);
    const string &getKey() const;
    void setKey(const string &key);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
