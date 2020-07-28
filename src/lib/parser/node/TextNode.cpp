#include "./TextNode.hpp"

#include "../../template/PugTemplate.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
TextNode::TextNode() : Node(e_TextNode)
{
}

const string &TextNode::getValue() const
{
    return value_;
}

void TextNode::setValue(const string &value)
{
    value_ = value;
    prepare();
}

void TextNode::appendText(const string &txt)
{
    value_ += txt;
    prepare();
}

void TextNode::execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt)
{
    try
    {
        string str = Utils::interpolate(preparedValue_, model, tmplt.getExpressionHandler());
        writer.append(str);
    }
    catch (ExpressionException &e)
    {
        throw PugCompilerException(*this, tmplt.getTemplateLoader(), &e);
    }
}

void TextNode::prepare()
{
    Utils::prepareInterpolate(preparedValue_, getValue(), false);
}

} // namespace node
} // namespace parser
} // namespace pugcpp