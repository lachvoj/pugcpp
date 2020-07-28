#include "./Scanner.hpp"

#include "../util/StringUtils.hpp"

namespace pugcpp
{
namespace lexer
{
using namespace util;

Scanner::Scanner(istream &stream)
{
    initFromStream(stream);
}

Scanner::Scanner(const string &input) : input_(input)
{
}

void Scanner::initFromStream(istream &stream)
{
    string sb = "";
    string s = "";
    bool first = true;
    // TODO: catch io stream exceptions.
    while (stream.peek() != EOF)
    {
        getline(stream, s);
        if (!first)
        {
            sb += "\n";
        }
        else
        {
            s = regex_replace(s, regex("^\\uFEFF"), "");
        }
        first = false;
        if (!s.empty())
        {
            sb += s;
        }
    }

    input_ = sb;
    if (!input_.empty())
    {
        input_ = regex_replace(input_, regex("\\r\\n|\\r"), "\\n");
    }
}

bool Scanner::isEmpty()
{
    return input_.empty();
}

void Scanner::consume(int length)
{
    input_.erase(0, length);
}

string Scanner::findInLine(const string &re)
{
    regex rgx(re);
    smatch sm;
    regex_search(input_, sm, rgx);
    if (regex_search(input_, sm, rgx))
    {
        return input_.substr(sm.position(0) + sm[0].length());
    }
    return nullptr;
}

char Scanner::charAt(int i)
{
    return input_[i];
}

bool Scanner::beginnsWithWhitespace()
{
    return (input_[0] == ' ' || input_[0] == '\t');
}

bool Scanner::isNotEmpty()
{
    return !input_.empty();
}

bool Scanner::isNotLineBreak()
{
    return (isEmpty() || input_[0] != '\n');
}

string Scanner::getPipelessText()
{
    size_t i = input_.find('\n');
    if (i == string::npos)
    {
        i = input_.length();
    }
    string str = input_.substr(i);
    consume(str.length());
    str = StringUtils::trim(str);

    return str;
}

const string &Scanner::getInput() const
{
    return input_;
}

void Scanner::getMatcherForPattern(smatch &matcher, const string &sRegex)
{
    regex re(sRegex);
    regex_search(input_, matcher, re);
}

void Scanner::getMatcherForPattern(smatch &matcher, const regex &regex)
{
    regex_search(input_, matcher, regex);
}

bool Scanner::isIntendantionViolated()
{
    return (input_.length() > 0 && (input_[0] == ' ' || input_[0] == '\t'));
}

bool Scanner::isBlankLine()
{
    return (input_.length() > 0 && input_[0] == '\n');
}

bool Scanner::isAdditionalBlankline()
{
    return (input_.length() > 2 && input_[0] == '\n' && input_[1] == '\n');
}

} // namespace lexer
} // namespace pugcpp
