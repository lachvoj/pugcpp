#ifndef Lexer_hpp
#define Lexer_hpp

#include <istream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <regex>
#include <string>

#include "../exceptions/PugLexerException.hpp"
#include "../expression/IExpressionHandler.hpp"
#include "../template/ITemplateLoader.hpp"
#include "../util/CharacterParser.hpp"
#include "../util/FileSystem.hpp"

#include "Scanner.hpp"
#include "token/Colon.hpp"
#include "token/Comment.hpp"
#include "token/Eos.hpp"
#include "token/Outdent.hpp"
#include "token/Text.hpp"
#include "token/Token.hpp"

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

    static const regex m_rgCleanRe;
    static const regex m_rgDoubleQuotedRe;
    static const regex m_rgQuotedRe;
    static const map<char, char> m_conClosingBrackets;

    int m_nLastIndents = 0;
    int m_nLineno = 1;
    bool m_bPipeless = false;
    bool m_bAttributeMode;
    string m_sFilename;
    string m_sIndentType;
    string m_sIndentRe;
    unique_ptr<Scanner> m_pclScanner;
    shared_ptr<ITemplateLoader> m_pclTemplateLoader;
    shared_ptr<CharacterParser> m_pclCharacterParser;
    shared_ptr<IExpressionHandler> m_pclExpressionHandler;
    queue<int> m_conIndentStack;
    queue<string> m_conOptions;
    deque<shared_ptr<Token>> m_conDeferredTokens;
    deque<shared_ptr<Token>> m_conStash;

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
        int i,
        const string &str,
        const string &key,
        const string &val,
        Loc loc,
        CharacterParser::State state) const;
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
    string interpolate(const string &attr, const string &quote);
    string ensurePugExtension(const string &templateName, const ITemplateLoader &templateLoader);
    bool assertNestingCorrect(const string &exp);
    shared_ptr<Token> stashed();
    shared_ptr<Token> deferred();
    shared_ptr<Token> blank();
    shared_ptr<Token> eos();
    shared_ptr<Token> comment();
    shared_ptr<Token> code();
    shared_ptr<Token> interpolation();
    shared_ptr<Token> tag();
    shared_ptr<Token> yield();
    shared_ptr<Token> filter();
    shared_ptr<Token> each();
    shared_ptr<Token> whileToken();
    shared_ptr<Token> conditional();
    shared_ptr<Token> doctype();
    shared_ptr<Token> id();
    shared_ptr<Token> className();
    shared_ptr<Token> text();
    shared_ptr<Token> textFail();
    shared_ptr<Token> fail();
    shared_ptr<Token> extendsToken();
    shared_ptr<Token> prepend();
    shared_ptr<Token> append();
    shared_ptr<Token> block();
    shared_ptr<Token> mixinBlock();
    shared_ptr<Token> blockCode();
    shared_ptr<Token> include();
    shared_ptr<Token> includeFiltered();
    shared_ptr<Token> caseToken();
    shared_ptr<Token> when();
    shared_ptr<Token> defaultToken();
    shared_ptr<Token> assignment();
    shared_ptr<Token> dot();
    shared_ptr<Token> mixin();
    shared_ptr<Token> call();
    shared_ptr<Token> attrs();
    shared_ptr<Token> attributesBlock();
    shared_ptr<Token> indent();
    shared_ptr<Token> pipelessText();
    shared_ptr<Token> colon();
};
} // namespace lexer
} // namespace pugcpp
#endif
