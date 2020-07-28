#ifndef Scanner_hpp
#define Scanner_hpp

#include <fstream>
#include <memory>
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

    void initFromStream(istream &stream);
    bool isEmpty();

  public:
    Scanner(istream &stream);
    Scanner(const string &input);

    void consume(int length);
    string findInLine(const string &re);
    char charAt(int i);
    bool beginnsWithWhitespace();
    bool isNotEmpty();
    bool isNotLineBreak();
    string getPipelessText();
    const string &getInput() const;
    void getMatcherForPattern(smatch &matcher, const string &sRegex);
    void getMatcherForPattern(smatch &matcher, const regex &regex);
    bool isIntendantionViolated();
    bool isBlankLine();
    bool isAdditionalBlankline();
};
} // namespace lexer
} // namespace pugcpp
#endif
