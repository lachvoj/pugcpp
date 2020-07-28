#ifndef IndentWriter_hpp
#define IndentWriter_hpp

#include <memory>
#include <sstream>
#include <string>

#include "../util/StringUtils.hpp"

using namespace std;

namespace pugcpp
{
namespace compiler
{
class IndentWriter
{
  private:
    int indent_ = 0;
    bool useIndent_ = false;
    bool empty_ = true;
    ostringstream &writer_;
    string pp_ = "  ";
    bool escape_ = false;
    bool compiledTag_ = false;
    bool compiledDoctype_ = false;

    void write(const string &string);

  public:
    IndentWriter(ostringstream &writer);

    void add(const string &string);
    void append(const string &string);
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
#endif
