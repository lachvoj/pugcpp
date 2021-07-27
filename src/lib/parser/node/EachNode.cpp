#include "./EachNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
EachNode::EachNode() : Node(e_EachNode)
{
}

const string &EachNode::getCode() const
{
    return code_;
}

void EachNode::setCode(const string &code)
{
    code_ = code;
}

const string &EachNode::getKey() const
{
    return key_;
}

void EachNode::setKey(const string &key)
{
    key_ = key;
}

shared_ptr<Node> &EachNode::getElseNode()
{
    return elseNode_;
}

void EachNode::setElseNode(shared_ptr<Node> &elseNode)
{
    elseNode_ = elseNode;
}

void EachNode::run(IndentWriter &writer, PugModel &model, any &result, PugTemplate &tmplt)
{
    if (map<any, any> *val = any_cast<map<any, any>>(&result))
    {
        runMap(*val, model, writer, tmplt);
    }
    // TODO: other types
}

void EachNode::runMap(map<any, any> &result, PugModel &model, IndentWriter &writer, PugTemplate &tmplt)
{
    if (result.empty())
    {
        executeElseNode(model, writer, tmplt);
    }

    for (auto &item : result)
    {
        model.put(value_, item.second);
        model.put(key_, item.first);
        block_->execute(writer, model, tmplt);
    }
}

void EachNode::executeElseNode(PugModel &model, IndentWriter &writer, PugTemplate &tmplt)
{
    if (elseNode_)
        elseNode_->execute(writer, model, tmplt);
}

void EachNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    any result;
    try
    {
        result = tmplt.getExpressionHandler()->evaluateExpression(code_, model);
    }
    catch (ExpressionException &e)
    {
        throw PugCompilerException(*this, tmplt.getTemplateLoader(), &e);
    }
    if (!result.has_value())
        throw PugCompilerException(*this, tmplt.getTemplateLoader(), "[" + code_ + "] has to be iterable but was null");

    model.pushScope();
    run(writer, model, result, tmplt);
    model.popScope();
}
} // namespace node
} // namespace parser
} // namespace pugcpp