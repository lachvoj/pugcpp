#include "./Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
const vector<string> Token::tokenTypeNames({"Default",
                                            "AttributeList",
                                            "AttributesBlock",
                                            "Block",
                                            "BlockCode",
                                            "BufferedComment",
                                            "Call",
                                            "CaseToken",
                                            "Colon",
                                            "Comment",
                                            "CssClass",
                                            "CssId",
                                            "Deferred",
                                            "Doctype",
                                            "Dot",
                                            "Else",
                                            "ElseIf",
                                            "Eos",
                                            "Expression",
                                            "ExtendsToken",
                                            "Filter",
                                            "ForTag",
                                            "If",
                                            "Include",
                                            "Indent",
                                            "Interpolation",
                                            "Mixin",
                                            "MixinBlock",
                                            "Newline",
                                            "Outdent",
                                            "PipelessText",
                                            "Tag",
                                            "Text",
                                            "UnbufferedComment",
                                            "When",
                                            "While",
                                            "Yield",
                                            "Assignment",
                                            "Each"});

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

const TokenType Token::getType() const
{
    return type_;
}

const string &Token::getValue() const
{
    return value_;
}

void Token::setValue(const string &value)
{
    value_ = value;
}

const int Token::getLineNumber() const
{
    return lineNumber_;
}

const bool Token::isBuffer() const
{
    return buffer_;
}

void Token::setBuffer(bool buffer)
{
    buffer_ = buffer;
}

const string &Token::getMode() const
{
    return mode_;
}

void Token::setMode(const string &mode)
{
    mode_ = mode;
}

const string &Token::toString() const
{
    return value_;
}

const string &Token::getName() const
{
    return name_;
}

void Token::setName(const string &name)
{
    name_ = name;
}

const int Token::getIndents() const
{
    return indents_;
}

void Token::setIndents(int indents)
{
    indents_ = indents;
}

const bool Token::isSelfClosing() const
{
    return selfClosing_;
}

void Token::setSelfClosing(bool selfClosing)
{
    selfClosing_ = selfClosing;
}

const vector<string> &Token::getValues() const
{
    return values_;
}

void Token::setValues(vector<string> &values)
{
    values_ = values;
}

const string &Token::getTypeName() const
{
    return getTypeNameFromTokenType(type_);
}

const string &Token::getTypeNameFromTokenType(const TokenType tokenType)
{
    return tokenTypeNames.at(tokenType);
}

} // namespace token
} // namespace lexer
} // namespace pugcpp
