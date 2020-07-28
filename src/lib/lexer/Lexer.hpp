#ifndef Lexer_hpp
#define Lexer_hpp

#include <istream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <regex>
#include <stack>
#include <string>

#include "../exceptions/PugLexerException.hpp"
#include "../expression/IExpressionHandler.hpp"
#include "../template/ITemplateLoader.hpp"
#include "../util/CharacterParser.hpp"
#include "../util/FileSystem.hpp"
#include "../util/Options.hpp"

#include "Scanner.hpp"
#include "token/Assignment.hpp"
#include "token/AttributeList.hpp"
#include "token/AttributesBlock.hpp"
#include "token/Block.hpp"
#include "token/BlockCode.hpp"
#include "token/BufferedComment.hpp"
#include "token/Call.hpp"
#include "token/CaseToken.hpp"
#include "token/Colon.hpp"
#include "token/Comment.hpp"
#include "token/CssClass.hpp"
#include "token/CssId.hpp"
#include "token/Default.hpp"
#include "token/Deferred.hpp"
#include "token/Doctype.hpp"
#include "token/Doctypes.hpp"
#include "token/Dot.hpp"
#include "token/Each.hpp"
#include "token/Else.hpp"
#include "token/ElseIf.hpp"
#include "token/Eos.hpp"
#include "token/Expression.hpp"
#include "token/ExtendsToken.hpp"
#include "token/Filter.hpp"
#include "token/ForTag.hpp"
#include "token/If.hpp"
#include "token/Include.hpp"
#include "token/Indent.hpp"
#include "token/Interpolation.hpp"
#include "token/Mixin.hpp"
#include "token/MixinBlock.hpp"
#include "token/Newline.hpp"
#include "token/Outdent.hpp"
#include "token/PipelessText.hpp"
#include "token/Tag.hpp"
#include "token/Text.hpp"
#include "token/Token.hpp"
#include "token/UnbufferedComment.hpp"
#include "token/When.hpp"
#include "token/While.hpp"
#include "token/Yield.hpp"

using namespace std;

namespace pugcpp
{
namespace lexer
{
using namespace token;
using namespace expression;
using namespace tmpl;
using namespace util;

class Lexer
{
  private:
    enum Loc
    {
        KEY,
        KEY_CHAR,
        VALUE,
        STRING
    };

    static const regex cleanRe;
    static const regex doubleQuotedRe;
    static const regex quotedRe;
    static const map<char, char> closingBrackets;

    int lneno_ = 1;
    bool pipeless_ = false;
    string fileName_;
    string indentRe_;
    unique_ptr<Scanner> scanner_;
    shared_ptr<ITemplateLoader> templateLoader_;
    CharacterParser characterParser_;
    shared_ptr<IExpressionHandler> expressionHandler_;
    stack<int> indentStack_;
    queue<shared_ptr<Token>> deferredTokens_;
    deque<shared_ptr<Token>> stash_;

  public:
    Lexer(
        const string &filename,
        shared_ptr<ITemplateLoader> templateLoader,
        shared_ptr<IExpressionHandler> expressionHandler);
    Lexer(
        const string &input,
        const string &filename,
        shared_ptr<ITemplateLoader> templateLoader,
        shared_ptr<IExpressionHandler> expressionHandler);

    const int getLineno() const;
    const bool getPipeless() const;
    void setPipeless(bool pipeless);
    const bool isEndOfAttribute(
        const int i,
        const string &str,
        const string &key,
        const string &val,
        const Loc &loc,
        const CharacterParser::State &state) const;
    void consume(int len);
    void defer(shared_ptr<Token> tok);
    shared_ptr<Token> lookahead(int n);
    shared_ptr<Token> next();
    shared_ptr<Token> advance();
    shared_ptr<list<shared_ptr<Token>>> getTokens();

  private:
    shared_ptr<CharacterParser::Match> bracketExpression();
    shared_ptr<CharacterParser::Match> bracketExpression(int skip);
    string scan(const string &regexp, int group = 1);
    string interpolate(const string &attr, const char quote);
    string ensurePugExtension(const string &templateName, const ITemplateLoader &templateLoader);
    bool assertNestingCorrect(const string &exp);
    void stashed(shared_ptr<Token> &ret);
    void deferred(shared_ptr<Token> &ret);
    void blank(shared_ptr<Token> &ret);
    void eos(shared_ptr<Token> &ret);
    void comment(shared_ptr<Token> &ret);
    void code(shared_ptr<Token> &ret);
    void interpolation(shared_ptr<Token> &ret);
    void tag(shared_ptr<Token> &ret);
    void yield(shared_ptr<Token> &ret);
    void filter(shared_ptr<Token> &ret);
    void each(shared_ptr<Token> &ret);
    void whileToken(shared_ptr<Token> &ret);
    void conditional(shared_ptr<Token> &ret);
    void doctype(shared_ptr<Token> &ret);
    void id(shared_ptr<Token> &ret);
    void className(shared_ptr<Token> &ret);
    void text(shared_ptr<Token> &ret);
    void textFail(shared_ptr<Token> &ret);
    void extendsToken(shared_ptr<Token> &ret);
    void prepend(shared_ptr<Token> &ret);
    void append(shared_ptr<Token> &ret);
    void block(shared_ptr<Token> &ret);
    void mixinBlock(shared_ptr<Token> &ret);
    void blockCode(shared_ptr<Token> &ret);
    void include(shared_ptr<Token> &ret);
    void includeFiltered(shared_ptr<Token> &ret);
    void caseToken(shared_ptr<Token> &ret);
    void when(shared_ptr<Token> &ret);
    void defaultToken(shared_ptr<Token> &ret);
    void assignment(shared_ptr<Token> &ret);
    void dot(shared_ptr<Token> &ret);
    void mixin(shared_ptr<Token> &ret);
    void call(shared_ptr<Token> &ret);
    void attrs(shared_ptr<Token> &ret);
    void attributesBlock(shared_ptr<Token> &ret);
    void indent(shared_ptr<Token> &ret);
    void pipelessText(shared_ptr<Token> &ret);
    void colon(shared_ptr<Token> &ret);
};
} // namespace lexer
} // namespace pugcpp
#endif
