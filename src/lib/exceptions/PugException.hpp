#pragma once

#include <memory>
#include <string>

#include "../template/ITemplateLoader.hpp"
#include "Exception.hpp"

using namespace std;

namespace pugcpp
{
namespace exceptions
{
using namespace tmpl;

class PugException : public Exception
{
  private:
    static const long serialVersionUID = -8189536050437574552L;
    string m_sFilename;
    int m_nLineNumber;
    shared_ptr<tmpl::ITemplateLoader> m_pTemplateLoader;

  public:
    PugException(const string &message,
                 const string &filename,
                 int lineNumber,
                 shared_ptr<tmpl::ITemplateLoader> templateLoader,
                 const std::exception *e);
    PugException(const string &message);
    ~PugException()
    {
    }
    const char *what() const noexcept override;

    const string &getFilename();
    int getLienNumber();
};
} // namespace exceptions
} // namespace pugcpp
