#pragma once

#include <memory>
#include <queue>
#include <regex>
#include <string>

#include "../expression/IExpressionHandler.hpp"
#include "../template/ITemplateLoader.hpp"
#include "Scanner.hpp"
#include "token/Token.hpp"

using namespace std;

namespace pugcpp
{
namespace lexer
{
using namespace token;
using namespace expression;
using namespace tmpl;

class Lexer
{
  private:
    static const regex m_rgCleanRe;
    static const regex m_rgDoubleQuotedRe;
    static const regex m_rgQuotedRe;
    queue<string> options_;
    unique_ptr<Scanner> scanner_;
    queue<shared_ptr<Token>> m_conDeferredTokens_;
    int lastIndents_ = -1;
    int lineno_;
    queue<Token> m_conStash_;
    queue<int> indentStack_;
    string indentRe_;
    bool pipeless_ = false;
    bool attributeMode_;
    string m_sFilename;
    shared_ptr<ITemplateLoader> m_pclTemplateLoader;
    string m_sIndentType;
    // CharacterParser characterParser_;
    shared_ptr<IExpressionHandler> m_pclExpressionHandler;

  public:
    Lexer(const string &filename,
          shared_ptr<ITemplateLoader> templateLoader,
          shared_ptr<IExpressionHandler> expressionHandler);
    Lexer(const string &input,
          const string &filename,
          shared_ptr<ITemplateLoader> templateLoader,
          shared_ptr<IExpressionHandler> expressionHandler);

    shared_ptr<Token> next();
    void consume(int len);
    void defer(shared_ptr<Token> tok);
    shared_ptr<Token> lookahead(int n);
};
} // namespace lexer
} // namespace pugcpp
