#include "./V8ExpressionHandler.hpp"

namespace pugcpp
{
namespace expression
{

const regex V8ExpressionHandler::plusplus("([a-zA-Z0-9-_]*[a-zA-Z0-9])\\+\\+\\s*;{0,1}\\s*$");
const regex V8ExpressionHandler::isplusplus("\\+\\+\\s*;{0,1}\\s*$");
const regex V8ExpressionHandler::minusminus("([a-zA-Z0-9-_]*[a-zA-Z0-9])--\\s*;{0,1}\\s*$");
const regex V8ExpressionHandler::isminusminus("--\\s*;{0,1}\\s*$");
const regex V8ExpressionHandler::isAssignment("^([a-zA-Z0-9-_]+)[\\s]?={1}[\\s]?[^=]+$");

V8ExpressionHandler::V8ExpressionHandler() : platform_(v8::platform::NewDefaultPlatform())
{
    v8::V8::InitializeICUDefaultLocation("./");
    v8::V8::InitializeExternalStartupData("./");
    v8::V8::InitializePlatform(platform_.get());
    v8::V8::Initialize();
    createParams_.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    isolate_ = v8::Isolate::New(createParams_);
}

V8ExpressionHandler::~V8ExpressionHandler()
{
    if (isolate_)
        isolate_->Dispose();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    delete createParams_.array_buffer_allocator;
}

void V8ExpressionHandler::saveNonLocalVarAssignmentInModel(const string &expression, PugModel &model)
{
    if (StringUtils::startsWith(expression, "var "))
        return;

    smatch matcher;
    regex_search(expression, matcher, isAssignment);
    if (matcher.empty())
        return;

    any anlv;
    any *nonLocalVars = model.get(PugModel::NON_LOCAL_VARS);
    if (!nonLocalVars)
    {
        anlv = make_any<vector<string>>();
        nonLocalVars = &anlv;
    }
    vector<string> *nlv = any_cast<vector<string>>(nonLocalVars);
    if (!nlv)
        throw ExpressionException("Invalid value type in nonLocalVars element of model.");
    nlv->push_back(matcher.str(1));
    model.put(PugModel::NON_LOCAL_VARS, *nonLocalVars);
}

string &V8ExpressionHandler::removeVar(string &expression)
{
    StringUtils::replaceAll(expression, "var ", ";");
    return expression;
}

Local<v8::Value> V8ExpressionHandler::modelAnyToV8Value(any val)
{
    if (bool *v8Val = any_cast<bool>(&val))
        return v8::Boolean::New(isolate_, *v8Val);

    if (int *v8Val = any_cast<int>(&val))
        return v8::Integer::New(isolate_, *v8Val);

    if (double *v8Val = any_cast<double>(&val))
        return v8::Number::New(isolate_, *v8Val);

    if (string *v8Val = any_cast<string>(&val))
        return v8::String::NewFromUtf8(isolate_, v8Val->c_str()).ToLocalChecked();

    return Local<v8::Value>();
}

bool V8ExpressionHandler::evaluateBooleanExpression(const string &expression, PugModel &model)
{
    return false;
}

any V8ExpressionHandler::evaluateExpression(const string &expression, PugModel &model)
{
    v8::Isolate::Scope isolate_scope(isolate_);
    v8::HandleScope handle_scope(isolate_);
    v8::Local<v8::Context> context;

    shared_ptr<v8::Global<v8::Context>> cntxt =
        static_pointer_cast<v8::Global<v8::Context>>(model.getCurrentScopeContext());
    if (!cntxt)
    {
        context = v8::Context::New(isolate_);
        shared_ptr<v8::Global<v8::Context>> sgContext = make_shared<v8::Global<v8::Context>>();
        sgContext->Reset(isolate_, context);
        model.setCurrentScopeContext(sgContext);

        vector<pair<string, any>> modelEntries;
        model.entrySet(modelEntries);
        v8::Local<v8::Object> global = context->Global();
        for (auto &entry : modelEntries)
        {
            v8::Local<v8::String> key = v8::String::NewFromUtf8(isolate_, entry.first.c_str()).ToLocalChecked();
            v8::Local<v8::Value> val = modelAnyToV8Value(entry.second);
            global->Set(context, key, val);
        }
    }
    else
        context = v8::Local<v8::Context>::New(isolate_, *cntxt);
    v8::Context::Scope context_scope(context);
    v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate_, string(expression).c_str()).ToLocalChecked();
    v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();
    v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();

    v8::MaybeLocal<v8::Array> propsArrayML = context->Global()->GetPropertyNames(context);
    v8::Local<v8::Array> propsArrayL;
    propsArrayML.ToLocal(&propsArrayL);

    v8::MaybeLocal<v8::String> propsArrayStrML = propsArrayL->ToString(context);
    v8::Local<v8::String> propsArrayStrL;
    propsArrayStrML.ToLocal(&propsArrayStrL);

    string propsString(*v8::String::Utf8Value(isolate_, propsArrayStrL));
    any ret;
    if (result->IsNullOrUndefined())
        return ret;
    if (result->IsNumber())
    {
        if (result->IsInt32())
            ret = stoi(*v8::String::Utf8Value(isolate_, result));
        else
            ret = stod(*v8::String::Utf8Value(isolate_, result));
    }
    else
        ret = string(*v8::String::Utf8Value(isolate_, result));

    return ret;
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