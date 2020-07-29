#include "AttributeLexer.hpp"

namespace pugcpp
{
namespace lexer
{
using namespace util;

AttributeLexer::AttributeLexer()
{
    states_.push(KEY);
}

const AttributeList &AttributeLexer::getToken(const string &input, int lineno)
{
    token_ = make_shared<AttributeList>(lineno);

    for (auto i = 0; i < input.length(); ++i)
    {
        parse(input[i]);
    }
    parse(',');

    return *token_;
}

// string key_;
// string value_;
// AttributeList token_;
// queue<State> states_;

const AttributeLexer::State AttributeLexer::state()
{
    return states_.front();
}

void AttributeLexer::parse(const char c)
{
    char real = c;
    switch (c)
    {
    case ',':
    case '\n':
        switch (state())
        {
        case EXPRESSION:
        case ARRAY:
        case STRING:
        case OBJECT: value_ += c; break;

        default:
            states_.push(KEY);
            StringUtils::argTrim(value_);
            StringUtils::argTrim(key_);
            if ("" == key_)
            {
                return;
            }
            regex reg("^['\"]|['\"]$");
            string name = regex_replace(key_, reg, "");
            string cleanValue = regex_replace(value_, reg, "");

            if (cleanValue == "" && quote_ == ' ')
            {
                token_->addBoolAttribute(name, true);
            }
            else if (regex_match(value_, regex("^\"[^\"]*\"$")) || regex_match(value_, regex("^'[^']*'$")))
            {
                token_->addAttribute(name, cleanValue, false);
            }
            else
            {
                token_->addExpressionAttribute(name, value_, false);
            }
            key_ = "";
            value_ = "";
            quote_ = ' ';
            break;
        }
        break;

    case '=': parseAssign(real); break;
    case '(': parseExpressionStart(c); break;
    case ')': parseExpressionEnd(c); break;
    case '{': parseObjectStart(c); break;
    case '}': parseObjectEnd(c); break;
    case '[': parseArrayStart(c); break;
    case ']': parseArrayEnd(c); break;
    case '"':
    case '\'': parseQuotes(c); break;
    default: parseDefaults(c); break;
    }
}

void AttributeLexer::parseAssign(const char real)
{
    switch (state())
    {
    case KEY_CHAR: key_ += real; break;
    case VALUE:
    case EXPRESSION:
    case ARRAY:
    case STRING:
    case OBJECT: value_ += real; break;
    default: states_.push(VALUE); break;
    }
}

void AttributeLexer::parseExpressionStart(const char c)
{
    if (state() == VALUE || state() == EXPRESSION)
    {
        states_.push(EXPRESSION);
    }
    value_ += c;
}

void AttributeLexer::parseExpressionEnd(const char c)
{
    if (state() == VALUE || state() == EXPRESSION)
    {
        states_.pop();
    }
    value_ += c;
}

void AttributeLexer::parseObjectStart(const char c)
{
    if (state() == VALUE)
    {
        states_.push(OBJECT);
    }
    value_ += c;
}

void AttributeLexer::parseObjectEnd(const char c)
{
    if (state() == OBJECT)
    {
        states_.pop();
    }
    value_ += c;
}

void AttributeLexer::parseArrayStart(const char c)
{
    if (state() == VALUE)
    {
        states_.push(ARRAY);
    }
    value_ += c;
}

void AttributeLexer::parseArrayEnd(const char c)
{
    if (state() == ARRAY)
    {
        states_.pop();
    }
    value_ += c;
}

void AttributeLexer::parseQuotes(const char c)
{
    switch (state())
    {
    case KEY: states_.push(KEY_CHAR); break;
    case KEY_CHAR: states_.pop(); break;
    case STRING:
        if (c == quote_)
        {
            states_.pop();
        }
        value_ += c;
        break;
    default:
        states_.push(STRING);
        value_ += c;
        quote_ = c;
        break;
    }
}

void AttributeLexer::parseDefaults(const char c)
{
    switch (state())
    {
    case KEY:
    case KEY_CHAR: key_ += c; break;
    default: value_ += c; break;
    }
}

} // namespace lexer
} // namespace pugcpp