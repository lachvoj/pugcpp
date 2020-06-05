#include "Token.hpp"

namespace token
{
Token::Token(int lineNumber /*= 0*/, TokenType type /*= e_Default*/) : lineNumber_(lineNumber), type_(type)
{
}

Token::Token(const string &value, int lineNumber, TokenType type /*= e_Default*/)
    : value_(value), lineNumber_(lineNumber), type_(type)
{
}

Token::Token(const string &value, int lineNumber, bool buffer, TokenType type /*= e_Default*/)
    : value_(value), lineNumber_(lineNumber), buffer_(buffer), type_(type)
{
}

Token::~Token()
{
}

string &Token::value()
{
    return value_;
}

const string &Token::value() const
{
    return value_;
}

const int Token::lineNumber() const
{
    return lineNumber_;
}

bool &Token::buffer()
{
    return buffer_;
}

const bool Token::buffer() const
{
    return buffer_;
}

string &Token::mode()
{
    return mode_;
}

const string &Token::mode() const
{
    return mode_;
}

const string &Token::toString() const
{
    return value_;
}

string &Token::name()
{
    return name_;
}

const string &Token::name() const
{
    return name_;
}

int &Token::indents()
{
    return indents_;
}

const int Token::indents() const
{
    return indents_;
}

bool &Token::selfClosing()
{
    return selfClosing_;
}

const bool Token::selfClosing() const
{
    return selfClosing_;
}

vector<string> &Token::values()
{
    return values_;
}

const vector<string> &Token::values() const
{
    return values_;
}

} // namespace token