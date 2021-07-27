#ifndef V8ExpressionHandler_hpp
#define V8ExpressionHandler_hpp

#include <memory>
#include <regex>
#include <string>

#include "../exceptions/ExpressionException.hpp"
#include "../util/StringUtils.hpp"

#include "../../../3d/v8/include/libplatform/libplatform.h"
#include "../../../3d/v8/include/v8.h"
#include "IExpressionHandler.hpp"

using namespace std;

namespace pugcpp
{
namespace expression
{
using namespace exceptions;
using namespace model;
using namespace v8;
using namespace util;

class V8ExpressionHandler : public IExpressionHandler
{
  private:
    static const regex plusplus;
    static const regex isplusplus;
    static const regex minusminus;
    static const regex isminusminus;
    static const regex isAssignment;

    unique_ptr<v8::Platform> platform_;
    v8::Isolate *isolate_;
    v8::Isolate::CreateParams createParams_;

    void saveNonLocalVarAssignmentInModel(const string &expression, PugModel &model);
    string &removeVar(string &expression);
    Local<v8::Value> modelAnyToV8Value(any val);

  public:
    V8ExpressionHandler();
    ~V8ExpressionHandler();
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
