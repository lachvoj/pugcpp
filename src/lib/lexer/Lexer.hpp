#pragma once

#include <memory>
#include <queue>
#include <regex>
#include <string>

#include "Scanner.hpp"
#include "token/Token.hpp"

using namespace std;
using namespace token;

namespace lexer
{
class Lexer
{
  private:
    static const regex cleanRe;
    static const regex doubleQuotedRe;
    static const regex quotedRe;
    queue<string> options_;
    unique_ptr<Scanner> scanner_;
    queue<Token> deferredTokens_;
    int lastIndents_ = -1;
    int lineno_;
    queue<Token> stash_;
    queue<int> indentStack_;
    string indentRe_;
    bool pipeless_ = false;
    bool attributeMode_;
    const string filename_;
    // const TemplateLoader templateLoader_;
    string indentType_;
    // CharacterParser characterParser_;
    // ExpressionHandler expressionHandler;

  public:
    Lexer(/* args */);
    ~Lexer();
};
} // namespace lexer