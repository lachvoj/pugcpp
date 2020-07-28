#ifndef IExpressionHadler
#define IExpressionHadler

#include <any>
#include <string>

#include "../exceptions/ExpressionException.hpp"
#include "../model/PugModel.hpp"

using namespace std;

namespace pugcpp
{
// forward declarations
namespace model
{
class PugModel;
}

namespace expression
{
using namespace model;

class IExpressionHandler
{
  public:
    virtual bool evaluateBooleanExpression(const string &expression, PugModel &model) = 0;
    virtual any evaluateExpression(const string &expression, PugModel &model) = 0;
    virtual string evaluateStringExpression(const string &expression, PugModel &model) = 0;
    virtual void assertExpression(string expression) = 0;
    virtual void setCache(bool cache) = 0;
    virtual void clearCache() = 0;
};
} // namespace expression
} // namespace pugcpp
#endif
