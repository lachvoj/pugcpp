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
void MixinNode::setRest(const string &rest)
{
    m_sRest = rest;
}

const string &MixinNode::getRest() const
{
    return m_sRest;
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
