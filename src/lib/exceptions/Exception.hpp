#ifndef Exception_hpp
#define Exception_hpp

#include <exception>
#include <string>

using namespace std;

namespace pugcpp
{
namespace exceptions
{
class Exception : public exception
{
  protected:
    string m_sError;
    std::exception m_clThrowable;

  public:
    Exception(const string &error);
    Exception(const string &error, const std::exception *e);

    const char *what() const noexcept override;
};

} // namespace exceptions
} // namespace pugcpp
#endif
