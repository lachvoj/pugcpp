#ifndef V8ExpressionHandler_hpp
#define V8ExpressionHandler_hpp

#include <memory>
#include <string>

#include "../../../3d/v8/include/v8.h"
#include "../../../3d/v8/include/libplatform/libplatform.h"
#include "IExpressionHandler.hpp"

using namespace std;

namespace pugcpp
{
namespace expression
{
using namespace model;
using namespace v8;

class V8ExpressionHandler : public IExpressionHandler
{
  private:
    unique_ptr<v8::Platform> platform_;
  public:
    V8ExpressionHandler();
    bool evaluateBooleanExpression(const string &expression, PugModel &model);
    any evaluateExpression(const string &expression, PugModel &model);
    string evaluateStringExpression(const string &expression, PugModel &model);
    void assertExpression(string expression);
    void setCache(bool cache);
    void clearCache();
};
} // namespace expression
} // namespace pugcpp
#endif
