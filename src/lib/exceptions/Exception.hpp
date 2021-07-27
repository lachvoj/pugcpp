#ifndef Exception_hpp
#define Exception_hpp

#include <exception>
#include <iostream>
#include <string>

#ifdef __linux__
#include <execinfo.h>
#endif

using namespace std;

namespace pugcpp
{
namespace exceptions
{
class Exception : public exception
{
  private:
  protected:
    string error_;
    std::exception *throwable_;
    bool printStack_ = true;

  public:
    Exception(const string &error, bool printStack = true);
    Exception(const string &error, std::exception *e);

    const char *what() const noexcept override;
    const string &getMessage() const noexcept;
    string getStackTrace();
    void printStackTrace();
};

} // namespace exceptions
} // namespace pugcpp
#endif
