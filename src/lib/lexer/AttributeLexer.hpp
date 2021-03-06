#ifndef AttributeLexer_hpp
#define AttributeLexer_hpp

#include <memory>
#include <queue>
#include <regex>
#include <string>

#include "../util/StringUtils.hpp"

#include "token/AttributeList.hpp"

using namespace std;

namespace pugcpp
{
namespace lexer
{
using namespace token;

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

    const AttributeList &getToken(const string &input, int lineno);
};
} // namespace lexer
} // namespace pugcpp
#endif
