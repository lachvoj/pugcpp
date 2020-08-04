#include "FilterNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
FilterNode::FilterNode() : Node(e_FilterNode)
{
}

vector<Attr> &FilterNode::getAttributes()
{
    return attributes_;
}

bool FilterNode::hasTextBlock()
{
    return bool(textBlock_);
}

shared_ptr<Node> FilterNode::getTextBlock()
{
    return textBlock_;
}

void FilterNode::setTextBlock(shared_ptr<Node> &textBlock)
{
    textBlock_ = textBlock;
}

void FilterNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    shared_ptr<IFilter> filter = model.getFilter(value_);
    vector<string> values;
    vector<shared_ptr<Node>> &nodes = textBlock_->getNodes();
    values.reserve(nodes.size());
    for (auto &node : nodes)
    {
        values.push_back(node->getValue());
    }
    string result = StringUtils::join(values, "\n");
    if (filter)
        result = filter->convert(result, attributes_, model);

    try
    {
        result = Utils::interpolate(result, model, false, tmplt.getExpressionHandler());
    }
    catch (ExpressionException &e)
    {
        throw PugCompilerException(*this, tmplt.getTemplateLoader(), &e);
    }
    writer.append(result);
}

} // namespace node
} // namespace parser
} // namespace pugcpp