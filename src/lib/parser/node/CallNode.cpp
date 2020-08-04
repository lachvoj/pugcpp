#include "./CallNode.hpp"

#include "MixinNode.hpp"

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

vector<string> &CallNode::getArguments()
{
    return arguments_;
}

void CallNode::setArguments(const vector<string> &arguments)
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

void CallNode::writeVariables(PugModel &model, MixinNode &mixin, PugTemplate &tmplt)
{
    vector<string> &names = mixin.getArguments();
    vector<string> &values = arguments_;
    if (names.empty())
        return;

    for (size_t i = 0; i < names.size(); i++)
    {
        string &key = names[i];
        string *value = nullptr;
        any eVal;
        if (i < values.size())
            value = &values[i];
        if (value && !value->empty())
        {
            try
            {
                eVal = tmplt.getExpressionHandler()->evaluateExpression(*value, model);
            }
            catch (exception &e)
            {
                throw PugCompilerException(*this, tmplt.getTemplateLoader(), &e);
            }
        }
        if (!key.empty())
            model.put(key, eVal);
    }

    const string &rest = mixin.getRest();
    if (rest.empty())
        return;

    vector<any> restArguments;
    for (size_t i = names.size(); i < arguments_.size(); ++i)
    {
        string *value = nullptr;
        any eVal;
        if (i < values.size())
            value = &values[i];
        if (value && !value->empty())
        {
            try
            {
                eVal = tmplt.getExpressionHandler()->evaluateExpression(*value, model);
            }
            catch (exception &e)
            {
                throw PugCompilerException(*this, tmplt.getTemplateLoader(), &e);
            }
        }
        restArguments.push_back(eVal);
    }
    model.put(rest, restArguments);
}

void CallNode::writeAttributes(PugModel &model, MixinNode &mixin, PugTemplate &tmplt)
{
    vector<Attr> newAttributes;
    if (attiributeBlocks_.size() > 0)
    {
        for (string &attributeBlock : attiributeBlocks_)
        {
            any o;
            try
            {
                o = tmplt.getExpressionHandler()->evaluateExpression(attributeBlock, model);
            }
            catch (ExpressionException &e)
            {
                e.printStackTrace();
            }
            if (o.has_value())
            {
                map<string, string> *val;
                if ((val = any_cast<map<string, string>>(&o)))
                {
                    for (auto &entry : *val)
                    {
                        newAttributes.emplace_back(entry.first, entry.second, false);
                    }
                }
                // else if (string *val = any_cast<string>(&o))
                // {
                //     //TODO:
                // }
            }
        }
    }

    if (newAttributes.size() > 0)
    {
        any atts = make_any<map<string, string, AttrCmp>>();
        map<string, string, AttrCmp> *attrsMap = any_cast<map<string, string, AttrCmp>>(&atts);
        if (!attrsMap)
            throw Exception("IDK why this happen.");
        attrs(*attrsMap, model, tmplt, newAttributes);
        model.put("attributes", atts);
    }
    else
    {
        model.put("attributes", "");
    }
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

    if (hasBlock())
    {
        vector<shared_ptr<MixinBlockNode>> injectionPoints;
        getInjectionPoints(injectionPoints, mixin->getBlock());
        for (auto &injPoint : injectionPoints)
        {
            injPoint->getNodes().push_back(block_);
        }
    }

    if (call_)
    {
        model.pushScope();
        model.put("block", block_);
        writeVariables(model, *mixin, tmplt);
        writeAttributes(model, *mixin, tmplt);
        mixin->getBlock()->execute(writer, model, tmplt);
        model.put("block", any());
        model.popScope();
    }
}
} // namespace node
} // namespace parser
} // namespace pugcpp
