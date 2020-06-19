#include "DummyExpressionHandler.hpp"

namespace pugcpp
{
namespace expression
{

bool DummyExpressionHandler::evaluateBooleanExpression(const string &expression, PugModel model)
{
}

any DummyExpressionHandler::evaluateExpression(const string &expression, PugModel model)
{
}

string DummyExpressionHandler::evaluateStringExpression(const string &expression, PugModel model)
{
}

void DummyExpressionHandler::assertExpression(string expression)
{
}

void DummyExpressionHandler::setCache(bool cache)
{
}

void DummyExpressionHandler::clearCache()
{
}

} // namespace expression
} // namespace pugcpp