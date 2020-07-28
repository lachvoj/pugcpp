#include "./CharacterParser.hpp"

namespace pugcpp
{
namespace util
{
const regex CharacterParser::pattern("^\\w+\\b");
const set<string> CharacterParser::keywords{
    "if",        "in",         "do",         "var",       "for",      "new",      "try",      "let",     "this",
    "else",      "case",       "void",       "with",      "enum",     "while",    "break",    "catch",   "throw",
    "const",     "yield",      "class",      "super",     "return",   "typeof",   "delete",   "switch",  "export",
    "import",    "default",    "finally",    "extends",   "function", "continue", "debugger", "package", "private",
    "interface", "instanceof", "implements", "protected", "public",   "static"};

CharacterParser::SyntaxError::SyntaxError(const string &message) : exceptions::Exception(message)
{
}

const bool CharacterParser::State::isString() const
{
    return singleQuote_ || doubleQuote_;
}

const bool CharacterParser::State::isComment() const
{
    return lineComment_ || blockComment_;
}

const bool CharacterParser::State::isNesting() const
{
    return isString() || isComment() || regexp_ || roundDepth_ > 0 || curlyDepth_ > 0 || squareDepth_ > 0;
}

void CharacterParser::State::setSrc(const string &src)
{
    src_ = src;
}

const string &CharacterParser::State::getSrc() const
{
    return src_;
}

void CharacterParser::State::setLineComment(bool lineComment)
{
    lineComment_ = lineComment;
}

const bool CharacterParser::State::isLineComment() const
{
    return lineComment_;
}

void CharacterParser::State::setBlockComment(bool blockComment)
{
    blockComment_ = blockComment;
}

const bool CharacterParser::State::isBlockComment() const
{
    return blockComment_;
}

void CharacterParser::State::setSingleQuote(bool singleQuote)
{
    singleQuote_ = singleQuote;
}

const bool CharacterParser::State::isSingleQuote() const
{
    return singleQuote_;
}

void CharacterParser::State::setDoubleQuote(bool doubleQuote)
{
    doubleQuote_ = doubleQuote;
}

const bool CharacterParser::State::isDoubleQuote() const
{
    return doubleQuote_;
}

void CharacterParser::State::setRegexp(bool regexp)
{
    regexp_ = regexp;
}

const bool CharacterParser::State::isRegexp() const
{
    return regexp_;
}

void CharacterParser::State::setRegexpStart(bool regexpStart)
{
    regexpStart_ = regexpStart;
}

const bool CharacterParser::State::isRegexpStart() const
{
    return regexpStart_;
}

void CharacterParser::State::setEscaped(bool escaped)
{
    escaped_ = escaped;
}

const bool CharacterParser::State::isEscaped() const
{
    return escaped_;
}

void CharacterParser::State::setRoundDepth(int roundDepth)
{
    roundDepth_ = roundDepth;
}

const int CharacterParser::State::getRoundDepth() const
{
    return roundDepth_;
}

void CharacterParser::State::setCurlyDepth(int curlyDepth)
{
    curlyDepth_ = curlyDepth;
}

const int CharacterParser::State::getCurlyDepth() const
{
    return curlyDepth_;
}

void CharacterParser::State::setSquareDepth(int squareDepth)
{
    squareDepth_ = squareDepth;
}

const int CharacterParser::State::getSquareDepth() const
{
    return squareDepth_;
}

void CharacterParser::State::setHistory(const string &history)
{
    history_ = history;
}

const string &CharacterParser::State::getHistory() const
{
    return history_;
}

void CharacterParser::State::setLastChar(char lastChar)
{
    lastChar_ = lastChar;
}

const char CharacterParser::State::getLastChar() const
{
    return lastChar_;
}

CharacterParser::Match::Match(int start, int end, const string &src) : start_(start), end_(end), src_(src)
{
}

const int CharacterParser::Match::getStart() const
{
    return start_;
}

const int CharacterParser::Match::getEnd() const
{
    return end_;
}

const string &CharacterParser::Match::getSrc() const
{
    return src_;
}

int CharacterParser::getStateProp(const CharacterParser::State &state, char bracket)
{
    if (')' == bracket)
        return state.getRoundDepth();
    if ('}' == bracket)
        return state.getCurlyDepth();
    if (']' == bracket)
        return state.getSquareDepth();

    return -1;
}

bool CharacterParser::startsWith(const string &str, const string &start, int i)
{
    return (start == str.substr(i, start.length()));
}

shared_ptr<CharacterParser::State> CharacterParser::parse(const string &src)
{
    shared_ptr<Options> options = make_shared<Options>();
    options->setEnd(src.length());

    return parse(src, defaultState(), options);
}

shared_ptr<CharacterParser::State> CharacterParser::parse(const string &src, shared_ptr<CharacterParser::State> state)
{
    shared_ptr<Options> options = make_shared<Options>();
    options->setEnd(src.length());

    return parse(src, state, options);
}

shared_ptr<CharacterParser::State> CharacterParser::parse(
    const string &src,
    shared_ptr<CharacterParser::State> state,
    shared_ptr<Options> options)
{
    if (options == nullptr)
    {
        options = make_shared<Options>();
        options->setEnd(src.length());
    }
    if (state == nullptr)
    {
        state = defaultState();
    }

    int start = options->getStart();
    int end = options->getEnd();
    int index = start;

    while (index < end)
    {
        if (state->getRoundDepth() < 0 || state->getCurlyDepth() < 0 || state->getSquareDepth() < 0)
        {
            throw SyntaxError("Mismatched Bracket: " + src[index - 1]);
        }
        parseChar(src[index++], state);
    }
    return state;
}

shared_ptr<CharacterParser::Match> CharacterParser::parseMax(const string &src)
{
    Options options;

    return parseMax(src, &options);
}

shared_ptr<CharacterParser::Match> CharacterParser::parseMax(const string &src, Options *options)
{
    Options opt;
    if (options == nullptr)
        options = &opt;

    int start = options->getStart();
    int index = start;
    shared_ptr<CharacterParser::State> state = defaultState();

    while (state->getRoundDepth() >= 0 && state->getCurlyDepth() >= 0 && state->getSquareDepth() >= 0)
    {
        if (index >= src.length())
        {
            throw SyntaxError("The end of the string was reached with no closing bracket found.");
        }
        parseChar(src[index], state);
        ++index;
    }
    int end = index - 1;

    return make_shared<CharacterParser::Match>(start, end, src.substr(start, end - start));
}

shared_ptr<CharacterParser::Match> CharacterParser::parseMaxBracket(const string &src, char bracket)
{
    Options options;

    return parseMaxBracket(src, bracket, &options);
}

shared_ptr<CharacterParser::Match> CharacterParser::parseMaxBracket(const string &src, char bracket, Options *options)
{
    if (bracket != ')' && bracket != '}' && bracket != ']')
    {
        string brckt(1, bracket);
        throw SyntaxError("Bracket specified (" + brckt + ") is not one of \")\", \"]\", or \"}\"");
    }
    Options opt;
    if (options == nullptr)
        options = &opt;

    int start = options->getStart();
    int index = start;
    shared_ptr<CharacterParser::State> state = defaultState();

    while (getStateProp(*state, bracket) >= 0)
    {
        if (index >= src.length())
        {
            string brckt(1, bracket);
            throw SyntaxError("The end of the string was reached with no closing bracket \"" + brckt + "\" found.");
        }
        parseChar(src[index++], state);
    }
    int end = index - 1;

    return make_shared<CharacterParser::Match>(start, end, src.substr(start, end - start));
}

shared_ptr<CharacterParser::Match> CharacterParser::parseUntil(const string &src, const string &delimiter)
{
    Options options;

    return parseUntil(src, delimiter, &options);
}

shared_ptr<CharacterParser::Match> CharacterParser::parseUntil(
    const string &src,
    const string &delimiter,
    Options *options)
{
    Options opt;
    if (options == nullptr)
        options = &opt;

    bool includeLineComment = options->isIncludeLineComment();
    int start = options->getStart();
    int index = start;
    shared_ptr<CharacterParser::State> state = defaultState();

    while (state->isString() || state->isRegexp() || state->isBlockComment() ||
           (!includeLineComment && state->isLineComment()) || !startsWith(src, delimiter, index))
    {
        parseChar(src[++index], state);
    }
    int end = index - 1;

    return make_shared<CharacterParser::Match>(start, end, src.substr(start, end - start));
}

void CharacterParser::parseChar(char character, shared_ptr<CharacterParser::State> &state)
{
    if (!state)
        state = defaultState();

    state->setSrc(state->getSrc() + character);
    bool wasComment = state->isBlockComment() || state->isLineComment();
    const char *lastChar = !state->getHistory().empty() ? &state->getHistory()[0] : nullptr;

    if (state->isRegexpStart())
    {
        if ('/' == character || '*' == character)
        {
            state->setRegexp(false);
        }
        state->setRegexpStart(false);
    }
    if (state->isLineComment())
    {
        if ('\n' == character)
        {
            state->setLineComment(false);
        }
    }
    else if (state->isBlockComment())
    {
        if ('*' == state->getLastChar() && '/' == character)
        {
            state->setBlockComment(false);
        }
    }
    else if (state->isSingleQuote())
    {
        if ('\'' == character && !state->isEscaped())
        {
            state->setSingleQuote(false);
        }
        else if ('\\' == character && !state->isEscaped())
        {
            state->setEscaped(true);
        }
        else
        {
            state->setEscaped(false);
        }
    }
    else if (state->isDoubleQuote())
    {
        if ('"' == character && !state->isEscaped())
        {
            state->setDoubleQuote(false);
        }
        else if ('\\' == character && !state->isEscaped())
        {
            state->setEscaped(true);
        }
        else
        {
            state->setEscaped(false);
        }
    }
    else if (state->isRegexp())
    {
        if ('/' == character && !state->isEscaped())
        {
            state->setRegexp(false);
        }
        else if ('\\' == character && !state->isEscaped())
        {
            state->setRegexp(true);
        }
        else
        {
            state->setEscaped(false);
        }
    }
    else if (lastChar != nullptr && '/' == *lastChar && '/' == character)
    {
        state->setHistory(state->getHistory().substr(1));
        state->setLineComment(true);
    }
    else if (lastChar != nullptr && '/' == *lastChar && '*' == character)
    {
        state->setHistory(state->getHistory().substr(1));
        state->setBlockComment(true);
    }
    else if ('/' == character && !state->getHistory().empty() && isRegexp(state->getHistory()))
    {
        state->setRegexp(true);
        state->setRegexpStart(true);
    }
    else if ('\'' == character)
    {
        state->setSingleQuote(true);
    }
    else if (character == '"')
    {
        state->setDoubleQuote(true);
    }
    else if (character == '(')
    {
        state->setRoundDepth(state->getRoundDepth() + 1);
    }
    else if (character == ')')
    {
        state->setRoundDepth(state->getRoundDepth() - 1);
    }
    else if (character == '{')
    {
        state->setCurlyDepth(state->getCurlyDepth() + 1);
    }
    else if (character == '}')
    {
        state->setCurlyDepth(state->getCurlyDepth() - 1);
    }
    else if (character == '[')
    {
        state->setSquareDepth(state->getSquareDepth() + 1);
    }
    else if (character == ']')
    {
        state->setSquareDepth(state->getSquareDepth() - 1);
    }
    if (!state->isBlockComment() && !state->isLineComment() && !wasComment)
        state->setHistory(character + state->getHistory());
    state->setLastChar(character); // store last character for ending block comments
}

shared_ptr<CharacterParser::State> CharacterParser::defaultState()
{
    return make_shared<CharacterParser::State>();
}

bool CharacterParser::isPunctuator(char character)
{
    switch (character)
    {
    case '.':
    case '(':
    case ')':
    case ';':
    case ',':
    case '{':
    case '}':
    case '[':
    case ']':
    case ':':
    case '?':
    case '~':
    case '%':
    case '&':
    case '*':
    case '+':
    case '-':
    case '/':
    case '<':
    case '>':
    case '^':
    case '|':
    case '!':
    case '=': return true;
    default: return false;
    }
}

bool CharacterParser::isKeyword(const string &id)
{
    if (keywords.find(id) != keywords.end())
        return true;
    return false;
}

bool CharacterParser::isRegexp(const string &history)
{
    string hist = history;
    StringUtils::replaceAll(hist, "^\\s*", "");

    // unless its an `if`, `while`, `for` or `with` it's a divide, so we assume it's a divide
    if (hist[0] == ')')
        return false;
    // unless it's a function expression, it's a regexp, so we assume it's a regexp
    if (hist[0] == '}')
        return true;
    // any punctuation means it's a regexp
    if (isPunctuator(hist[0]))
        return true;
    //if the last thing was a keyword then it must be a regexp (e.g. `typeof /foo/`)

    smatch matches;
    if (!regex_search(hist, matches, pattern))
        return false;
    // TODO: check why in java there is reversed string
    if (isKeyword(matches[0].str()))
        return true;

    return false;
}

} // namespace util
} // namespace pugcpp