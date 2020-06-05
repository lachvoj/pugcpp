#pragma once

#include <exception>
#include <string>

namespace exceptions
{
class Exception: public exception
{
  private:
    string m_sError;

  public:
    Exception(const string &error);
    ~Exception();

    const char *what() const noexcept override;
};

} // namespace exceptions