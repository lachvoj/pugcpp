#include "Each.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Each::Each(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Each)
{
}

Each::Each(const string &value, int lineNumber, const string &key, const string &code)
: Token::Token(value, lineNumber, e_Each), code_(code), key_(key)
{
}

const string &Each::getCode() const
{
    return code_;
}

void Each::setCode(const string &code)
{
    code_ = code;
}

const string &Each::getKey() const
{
    return key_;
}

void Each::setKey(const string &key)
{
    key_ = key;
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
