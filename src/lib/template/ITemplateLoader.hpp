#ifndef ITemplateLoader_hpp
#define ITemplateLoader_hpp

#include <exception>
#include <istream>
#include <memory>
#include <string>

using namespace std;

namespace pugcpp
{
namespace tmpl
{
class ITemplateLoader
{
  protected:
    ITemplateLoader(){};

  public:
    virtual ~ITemplateLoader(){};
    virtual long getLastModified(const string &name) = 0;
    virtual unique_ptr<istream> getReader(const string &name) = 0;
    virtual const string &getExtension() const = 0;
};
} // namespace tmpl
} // namespace pugcpp
#endif
