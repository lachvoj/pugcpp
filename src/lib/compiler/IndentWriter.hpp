#pragma once

#include <memory>
#include <sstream>
#include <string>

using namespace std;

namespace pugcpp
{
namespace compiler
{
class IndentWriter
{
  private:
    int m_nIndent = 0;
    int m_nParentIndents = 0;
    bool m_bUseIndent = false;
    bool m_bEmpty = true;
    stringstream &m_pWriter;
    string m_sPp = "  ";
    bool m_bEscape;
    bool m_bCompiledTag;
    bool m_bCompiledDoctype;

    void write(const string &string);

  public:
    IndentWriter(stringstream &writer);

    IndentWriter &add(const string &string);
    IndentWriter &append(const string &string);
    void increment();
    void decrement();
    string toString();
    void newline();
    void prettyIndent(int offset, bool newline);
    void setUseIndent(bool useIndent);
    void setEscape(bool escape);
    bool isEscape();
    bool isPp();
    void setCompiledTag(bool compiledTag);
    bool isCompiledTag();
    void setCompiledDoctype(bool compiledDoctype);
    bool isCompiledDoctype();
};

} // namespace compiler
} // namespace pugcpp
