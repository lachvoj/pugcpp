#pragma once

#include <memory>
#include <queue>
#include <string>

#include "token/AttributeList.hpp"

using namespace std;
using namespace token;

namespace lexer
{
class AttributeLexer
{
  public:
    enum State
    {
        KEY = 0,
        KEY_CHAR,
        VALUE,
        EXPRESSION,
        ARRAY,
        STRING,
        OBJECT
    };

  private:
    string key_;
    string value_;
    shared_ptr<AttributeList> token_;
    queue<State> states_;
    char quote_ = ' ';

    const State state();
    void parse(const char c);
    void parseAssign(const char real);
    void parseExpressionStart(const char c);
    void parseExpressionEnd(const char c);
    void parseObjectStart(const char c);
    void parseObjectEnd(const char c);
    void parseArrayStart(const char c);
    void parseArrayEnd(const char c);
    void parseQuotes(const char c);
    void parseDefaults(const char c);

  public:
    AttributeLexer();
    ~AttributeLexer();

    const AttributeList &getToken(const string &input, int lineno);
};
} // namespace lexer