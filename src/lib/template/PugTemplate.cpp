#include "PugTemplate.hpp"

namespace tmpl
{
void PugTemplate::process(model::PugModel model, stringstream &writer)
{
}

void PugTemplate::setPrettyPrint(bool prettyPrint)
{
}

bool PugTemplate::isPrettyPrint()
{
}

shared_ptr<parserNode::Node> PugTemplate::getRootNode()
{
}

void PugTemplate::setRootNode(shared_ptr<parserNode::Node> rootNode)
{
}

bool PugTemplate::isTerese()
{
}

bool PugTemplate::isXml()
{
}

void PugTemplate::setTemplateLoader(shared_ptr<ITemplateLoader> templateLoader)
{
}

shared_ptr<ITemplateLoader> PugTemplate::getTemplateLoader()
{
}

void PugTemplate::setDoctype(const string &name)
{
}

const string &PugTemplate::getDoctypeLine()
{
}

void PugTemplate::setMode(pugcpp::PugCpp::Mode mode)
{
}

void PugTemplate::setExpressionHandler(shared_ptr<expression::IExpressionHandler> expressionHandler)
{
}

shared_ptr<expression::IExpressionHandler> PugTemplate::getExpressionHandler()
{
}

} // namespace tmpl