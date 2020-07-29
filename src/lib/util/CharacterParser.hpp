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
    static const regex pattern;
    static const set<string> keywords;

  public:
    class SyntaxError : public exceptions::Exception
    {
      public:
        SyntaxError(const string &message);
    };

    class State
    {
      private:
        bool lineComment_ = false;
        bool blockComment_ = false;
        bool singleQuote_ = false;
        bool doubleQuote_ = false;
        bool regexp_ = false;
        bool regexpStart_ = false;
        bool escaped_ = false;

        int roundDepth_ = 0;
        int curlyDepth_ = 0;
        int squareDepth_ = 0;
        string history_ = "";
        char lastChar_ = 0;
        string src_ = "";

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
        size_t start_;
        size_t end_;
        // TODO: check if pointer or reference is sufficient
        string src_;

      public:
        Match(size_t start, size_t end, const string &src);
        const size_t getStart() const;
        const size_t getEnd() const;
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
    shared_ptr<Match> parseMax(const string &src, Options *options);
    shared_ptr<Match> parseMaxBracket(const string &src, char bracket);
    shared_ptr<Match> parseMaxBracket(const string &src, char bracket, Options *options);
    shared_ptr<Match> parseUntil(const string &src, const string &delimiter);
    shared_ptr<Match> parseUntil(const string &src, const string &delimiter, Options *options);
    void parseChar(char character, shared_ptr<State> &state);
    shared_ptr<State> defaultState();
    static bool isPunctuator(char character);
    static bool isKeyword(const string &id);
    static bool isRegexp(const string &history);
};
} // namespace util
} // namespace pugcpp
#endif
