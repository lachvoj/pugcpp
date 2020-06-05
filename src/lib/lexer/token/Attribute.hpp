#pragma once

#include <any>
#include <string>

using namespace std;

namespace token
{
class Attribute
{
  private:
    string name_;
    any value_;
    bool escaped_;

  public:
    Attribute(const string &name, const any &value, bool escape);
    ~Attribute();

    const string &name() const;
    const any &value() const;
    const bool escaped() const;
};
} // namespace token
