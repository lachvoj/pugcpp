#pragma once

#include <string>
#include <vector>

using namespace std;

namespace pugcpp
{
namespace lexer
{
namespace token
{
enum TokenType
{
    e_AttributeList = 0,
    e_AttributeBlock,
    e_Block,
    e_BlockCode,
    e_BufferedComment,
    e_Call,
    e_CaseToken,
    e_Colon,
    e_Comment,
    e_CssClass,
    e_CssId,
    e_Default,
    e_Deferred,
    e_Doctype,
    e_Dot,
    e_Else,
    e_ElseIf,
    e_Eos,
    e_Expression,
    e_ExtendsToken,
    e_Filter,
    e_ForTag,
    e_If,
    e_Include,
    e_Indent,
    e_Interpolation,
    e_Mixin,
    e_MixinBlock,
    e_Newline,
    e_Outdent,
    e_PipelessText,
    e_Tag,
    e_Text,
    e_UnbufferedComment,
    e_When,
    e_While,
    e_Yield,
    e_Assignment,
    e_Each
};

class Token
{
  private:
    TokenType type_;
    string value_;
    vector<string> values_;
    int lineNumber_;
    bool buffer_ = false;
    string mode_;
    string name_;
    int indents_;
    bool selfClosing_ = false;

  public:
    Token(int lineNumber = 0, TokenType type = e_Default);
    Token(const string &value, int lineNumber, TokenType type = e_Default);
    Token(const string &value, int lineNumber, bool buffer, TokenType type = e_Default);
    ~Token();

    string &value();
    const string &value() const;
    const int lineNumber() const;
    bool &buffer();
    const bool buffer() const;
    string &mode();
    const string &mode() const;
    const string &toString() const;
    string &name();
    const string &name() const;
    int &indents();
    const int indents() const;
    bool &selfClosing();
    const bool selfClosing() const;
    vector<string> &values();
    const vector<string> &values() const;
};
} // namespace token
} // namespace lexer
} // namespace pugcpp