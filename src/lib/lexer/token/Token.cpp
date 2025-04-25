#include "./Token.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
const vector<string> Token::tokenTypeNames(
    {"Default",
     "Assignment",
     "AttributeList",
     "AttributesBlock",
     "Block",
     "BlockCode",
     "BufferedComment",
     "Call",
     "Case",
     "Colon",
     "Comment",
     "CssClass",
     "CssId",
     "Deferred",
     "Doctype",
     "Dot",
     "Each",
     "Else",
     "ElseIf",
     "EndPugInterpolation",
     "Eos",
     "Expression",
     "Extends",
     "Filter",
     "ForTag",
     "If",
     "Include",
     "Indent",
     "InterpolatedCode",
     "Interpolation",
     "Mixin",
     "MixinBlock",
     "Newline",
     "Outdent",
     "PipelessText",
     "StartPugInterpolation",
     "Tag",
     "Text",
     "TextHtml",
     "UnbufferedComment",
     "When",
     "While",
     "Yield"});

Token::Token(int lineNumber /*= 0*/, TokenType type /*= e_Default*/) : type_(type), lineNumber_(lineNumber)
{
}

Token::Token(const string &value, int lineNumber, TokenType type /*= e_Default*/)
: type_(type), value_(value), lineNumber_(lineNumber)
{
}

Token::Token(const string &value, int lineNumber, bool buffer, TokenType type /*= e_Default*/)
: type_(type), value_(value), lineNumber_(lineNumber), buffer_(buffer)
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
