#include "./V8ExpressionHandler.hpp"

namespace pugcpp
{
namespace expression
{

V8ExpressionHandler::V8ExpressionHandler() : platform_(v8::platform::NewDefaultPlatform())
{
    v8::V8::InitializePlatform(platform_.get());
    v8::V8::Initialize();
}

bool V8ExpressionHandler::evaluateBooleanExpression(const string &expression, PugModel &model)
{
    return false;
}

any V8ExpressionHandler::evaluateExpression(const string &expression, PugModel &model)
{
    return any();
}

string V8ExpressionHandler::evaluateStringExpression(const string &expression, PugModel &model)
{
    return "";
}

void V8ExpressionHandler::assertExpression(string expression)
{
}

void V8ExpressionHandler::setCache(bool cache)
{
}

void V8ExpressionHandler::clearCache()
{
}

} // namespace expression
} // namespace pugcpp