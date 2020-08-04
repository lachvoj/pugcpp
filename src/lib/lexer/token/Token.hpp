#ifndef Token_hpp
#define Token_hpp

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
    e_Default = 0,
    e_AttributeList,
    e_AttributesBlock,
    e_Block,
    e_BlockCode,
    e_BufferedComment,
    e_Call,
    e_CaseToken,
    e_Colon,
    e_Comment,
    e_CssClass,
    e_CssId,
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
    static const vector<string> tokenTypeNames;
    const TokenType type_;
    string value_;
    vector<string> values_;
    int lineNumber_;
    bool buffer_ = false;
    string name_;
    int indents_;
    bool selfClosing_ = false;

  public:
    Token(int lineNumber = 0, TokenType type = e_Default);
    Token(const string &value, int lineNumber, TokenType type = e_Default);
    Token(const string &value, int lineNumber, bool buffer, TokenType type = e_Default);

    const TokenType getType() const;
    const string &getValue() const;
    void setValue(const string &value);
    const int getLineNumber() const;
    const bool isBuffer() const;
    void setBuffer(bool buffer);
    const string &toString() const;
    const string &getName() const;
    void setName(const string &name);
    const int getIndents() const;
    void setIndents(int indents);
    const bool isSelfClosing() const;
    void setSelfClosing(bool selfClosing);
    const vector<string> &getValues() const;
    void setValues(vector<string> &values);
    const string &getTypeName() const;
    static const string &getTypeNameFromTokenType(const TokenType tokenType);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
