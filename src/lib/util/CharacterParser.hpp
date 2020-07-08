#ifndef CharacterParser_hpp
#define CharacterParser_hpp

#include <memory>
#include <regex>
#include <set>
#include <string>

#include "../exceptions/Exception.hpp"

#include "Options.hpp"
#include "StringUtils.hpp"

using namespace std;

namespace pugcpp
{
namespace util
{
class CharacterParser
{
  private:
    static const regex m_clPattern;
    static const set<string> m_conKeywords;

  public:
    class SyntaxError : public exceptions::Exception
    {
      public:
        SyntaxError(const string &message);
    };

    class State
    {
      private:
        bool m_bLineComment = false;
        bool m_bBlockComment = false;
        bool m_bSingleQuote = false;
        bool m_bDoubleQuote = false;
        bool m_bRegexp = false;
        bool m_bRegexpStart = false;
        bool m_bEscaped = false;

        int m_nRoundDepth = 0;
        int m_nCurlyDepth = 0;
        int m_nSquareDepth = 0;
        string m_sHistory = "";
        char m_nLastChar = 0;
        string m_sSrc = "";

      public:
        const bool isString() const;
        const bool isComment() const;
        const bool isNesting() const;
        void setSrc(const string &src);
        const string &getSrc() const;
        void setLineComment(bool lineComment);
        const bool isLineComment() const;
        void setBlockComment(bool blockComment);
        const bool isBlockComment() const;
        void setSingleQuote(bool singleQuote);
        const bool isSingleQuote() const;
        void setDoubleQuote(bool doubleQuote);
        const bool isDoubleQuote() const;
        void setRegexp(bool regexp);
        const bool isRegexp() const;
        void setRegexpStart(bool regexpStart);
        const bool isRegexpStart() const;
        void setEscaped(bool escaped);
        const bool isEscaped() const;
        void setRoundDepth(int roundDepth);
        const int getRoundDepth() const;
        void setCurlyDepth(int curlyDepth);
        const int getCurlyDepth() const;
        void setSquareDepth(int squareDepth);
        const int getSquareDepth() const;
        void setHistory(const string &history);
        const string &getHistory() const;
        void setLastChar(char lastChar);
        const char getLastChar() const;
    };

    class Match
    {
      private:
        int m_nStart;
        int m_nEnd;
        // TODO: check if pointer or reference is sufficient
        string m_sSrc;

      public:
        Match(int start, int end, const string &src);
        const int getStart() const;
        const int getEnd() const;
        const string &getSrc() const;
    };

  private:
    int getStateProp(const State &state, char bracket);
    bool startsWith(const string &str, const string &start, int i);

  public:
    shared_ptr<State> parse(const string &src);
    shared_ptr<State> parse(const string &src, shared_ptr<State> state);
    shared_ptr<State> parse(const string &src, shared_ptr<State> state, shared_ptr<Options> options);
    shared_ptr<Match> parseMax(const string &src);
    shared_ptr<Match> parseMax(const string &src, shared_ptr<Options> options);
    shared_ptr<Match> parseMaxBracket(const string &src, char bracket);
    shared_ptr<Match> parseMaxBracket(const string &src, char bracket, shared_ptr<Options> options);
    shared_ptr<Match> parseUntil(const string &src, const string &delimiter);
    shared_ptr<Match> parseUntil(const string &src, const string &delimiter, shared_ptr<Options> options);
    shared_ptr<State> parseChar(char character, shared_ptr<State> state);
    shared_ptr<State> defaultState();
    bool isPunctuator(char character);
    bool isKeyword(const string &id);
    bool isRegexp(const string &history);
};
} // namespace util
} // namespace pugcpp
#endif
