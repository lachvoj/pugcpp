#pragma once

#include <map>
#include <string>

using namespace std;

namespace token
{
class Doctypes
{
    typedef map<string, string> PugDocTypeMap_T;

  private:
    static PugDocTypeMap_T m_;

  public:
    static const string &get(const string &pugDocType);
};
} // namespace token