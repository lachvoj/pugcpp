#pragma once

#include <fstream>
#include <regex>
#include <string>

using namespace std;

namespace pugcpp
{
namespace lexer
{
class Scanner
{
  private:
    string input_;

    void initFromStream(ifstream &stream);
    bool isEmpty();

  public:
    Scanner(ifstream &stream);
    Scanner(const string &input);

    void consume(int length);
    string findInLine(const string &re);
    char charAt(int i);
    bool beginnsWithWhitespace();
    bool isNotEmpty();
    bool isNotLineBreak();
    string getPipelessText();
    const string &getInput() const;
    regex getRegexForPattern(const string &sRegex);
    bool isIntendantionViolated();
    bool isBlankLine();
    bool isAdditionalBlankline();
};
} // namespace lexer
} // namespace pugcpp
