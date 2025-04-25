#ifndef PugException_hpp
#define PugException_hpp

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
    string fileName_;
    int lineNumber_ = -1;
    shared_ptr<tmpl::ITemplateLoader> templateLoader_;
    string sPugExceptionError_;

  public:
    PugException(
        const string &message,
        const string &filename,
        int lineNumber,
        shared_ptr<tmpl::ITemplateLoader> templateLoader,
        std::exception *e);
    PugException(const string &message);

    const char *what() const noexcept override;

    const string &getFilename();
    int getLineNumber();
};
} // namespace exceptions
} // namespace pugcpp
#endif
