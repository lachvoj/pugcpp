#include "./MixinNode.hpp"

#include "../../compiler/IndentWriter.hpp"
#include "../../model/PugModel.hpp"
#include "../../template/PugTemplate.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
MixinNode::MixinNode() : CallNode(e_MixinNode)
{
}

void MixinNode::setRest(const string &rest)
{
    rest_ = rest;
}

const string &MixinNode::getRest() const
{
    return rest_;
}

void MixinNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    if (isCall())
    {
        CallNode::execute(writer, model, tmplt);
    }
    else
    {
        model.setMixin(getName(), *this);
    }
}
} // namespace node
} // namespace parser
} // namespace pugcpp
