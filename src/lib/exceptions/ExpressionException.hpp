#pragma once

#include "Exception.hpp"

using namespace std;

namespace exceptions
{
class ExpressionException: public Exception
{
  private:
    static const long serialVersionUID = 1201110801125266239L;

  public:
    ExpressionException(const string &expression);
    ~ExpressionException();
};

} // namespace exceptions