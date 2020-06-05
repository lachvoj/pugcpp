#pragma once

#include <any>
#include <string>

using namespace std;

namespace parserNode
{
class Attr
{
  private:
    string name_;
    any value_;
    bool escaped_;

  public:
    Attr(const string &name, const any &value, bool escaped);
    ~Attr();

    const string &getName() const;
    any getValue() const;
    bool isEscaped();
};

} // namespace parserNode
