#pragma once

#include <any>
#include <string>

#include "../exceptions/ExpressionException.hpp"
#include "../model/PugModel.hpp"

using namespace std;

namespace expression
{
class IExpressionHandler
{
  public:
    ~IExpressionHandler(){};
    virtual bool evaluateBooleanExpression(string expression, model::PugModel model);
    virtual any evaluateExpression(string expression, model::PugModel model);
    virtual string evaluateStringExpression(string expression, model::PugModel model);
    virtual void assertExpression(string expression);
    virtual void setCache(bool cache);
    virtual void clearCache();
};
} // namespace expression