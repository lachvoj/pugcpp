#ifndef DummyExpressionHandler_hpp
#define DummyExpressionHandler_hpp

#include "IExpressionHandler.hpp"

namespace pugcpp
{
namespace expression
{
using namespace model;

class DummyExpressionHandler : public IExpressionHandler
{
  private:
  public:
    bool evaluateBooleanExpression(const string &expression, PugModel model);
    any evaluateExpression(const string &expression, PugModel model);
    string evaluateStringExpression(const string &expression, PugModel model);
    void assertExpression(string expression);
    void setCache(bool cache);
    void clearCache();
};
} // namespace expression
} // namespace pugcpp
#endif
