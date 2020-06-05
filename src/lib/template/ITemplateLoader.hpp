#pragma once

#include <exception>
#include <fstream>
#include <string>

using namespace std;

namespace tmpl
{
class ITemplateLoader
{
  public:
    ~ITemplateLoader(){};
    virtual long getLastModified(const string &name) = 0;
    virtual ifstream getReader(const string &name) = 0;
    virtual const string &getExtension() const = 0;
};
} // namespace tmpl
