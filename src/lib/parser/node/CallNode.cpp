#include "./CallNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
CallNode::CallNode() : AttrsNode(e_CallNode)
{
}

CallNode::CallNode(NodeType type) : AttrsNode(type)
{
}

list<string> &CallNode::getArguments()
{
    return arguments_;
}

void CallNode::setArguments(const list<string> &arguments)
{
    arguments_ = arguments;
}

void CallNode::setArguments(const string &arguments)
{
    arguments_.clear();
    ArgumentSplitter::split(arguments_, arguments);
}

bool CallNode::isCall()
{
    return call_;
}

void CallNode::setCall(bool call)
{
    call_ = call;
}

void CallNode::getInjectionPoints(vector<shared_ptr<MixinBlockNode>> &ret, const shared_ptr<Node> &block)
{
    for (auto &node : block->getNodes())
    {
        if (node->getType() == e_MixinBlockNode && !node->hasNodes())
            ret.push_back(static_pointer_cast<MixinBlockNode>(node));
        else if (node->getType() == e_ContionalNode)
        {
            for (auto &condition : static_pointer_cast<ConditionalNode>(node)->getConditions())
            {
                vector<shared_ptr<MixinBlockNode>> injPts;
                getInjectionPoints(injPts, condition->getBlock());
                ret.insert(ret.end(), injPts.begin(), injPts.end());
            }
        }
        else if (node->hasBlock())
        {
            vector<shared_ptr<MixinBlockNode>> injPts;
            getInjectionPoints(injPts, node->getBlock());
            ret.insert(ret.end(), injPts.begin(), injPts.end());
        }
    }
}

void CallNode::writeVariables(PugModel &model, shared_ptr<MixinNode> &mixin, PugTemplate &tmplt)
{
}

void CallNode::writeAttributes(PugModel &model, shared_ptr<MixinNode> &mixin, PugTemplate &tmplt)
{
}

void CallNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    bool dynamic = (name_[0] == '#');
    if (dynamic)
        dynamicMixins_ = true;

    string newname = dynamic ? name_.substr(2) : string(1, '"') + name_ + string(1, '"');
    try
    {
        newname = any_cast<string>(tmplt.getExpressionHandler()->evaluateExpression(newname, model));
    }
    catch (ExpressionException &e)
    {
        e.printStackTrace();
    }

    MixinNode *mixin = dynamic ? model.getMixin(newname) : model.getMixin(name_);
    if (!mixin)
        throw PugCompilerException(*this, tmplt.getTemplateLoader(), "mixin " + name_ + " is not defined");

    // TODO: check why clonning

    if (hasBlock()) {}
}
} // namespace node
} // namespace parser
} // namespace pugcpp
