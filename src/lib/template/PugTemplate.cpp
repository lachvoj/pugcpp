#include "PugTemplate.hpp"

namespace pugcpp
{
namespace tmpl
{
using namespace util;
using namespace lexer::token;

void PugTemplate::process(PugModel &model, ostringstream &writer)
{
    compiler::Compiler compiler(rootNode_, this, prettyPrint_);

    compiler.compile(model, writer);
}

void PugTemplate::setPrettyPrint(bool prettyPrint)
{
    prettyPrint_ = prettyPrint;
}

bool PugTemplate::isPrettyPrint()
{
    return prettyPrint_;
}

shared_ptr<Node> PugTemplate::getRootNode()
{
    return rootNode_;
}

void PugTemplate::setRootNode(shared_ptr<Node> rootNode)
{
    rootNode_ = rootNode;
}

bool PugTemplate::isTerese()
{
    return terse_;
}

bool PugTemplate::isXml()
{
    return xml_;
}

void PugTemplate::setTemplateLoader(shared_ptr<ITemplateLoader> templateLoader)
{
    templateLoader_ = templateLoader;
}

shared_ptr<ITemplateLoader> PugTemplate::getTemplateLoader()
{
    return templateLoader_;
}

void PugTemplate::setDoctype(const string &name)
{
    string l_sName = name;
    if (l_sName.empty())
    {
        l_sName = "default";
    }
    doctypeLine_ = Doctypes::get(l_sName);
    if (doctypeLine_.empty())
        doctypeLine_ = "<!DOCTYPE " + l_sName + ">";

    terse_ = ("<!doctype html>" == StringUtils::toLowerCase(doctypeLine_));
    xml_ = StringUtils::startsWith(doctypeLine_, "<?xml");
}

const string &PugTemplate::getDoctypeLine()
{
    return doctypeLine_;
}

void PugTemplate::setMode(pugcpp::PugCpp::Mode mode)
{
    terse_ = false;
    xml_ = false;
    switch (mode)
    {
    case PugCpp::Mode::HTML: terse_ = true; break;
    case PugCpp::Mode::XML: xml_ = true; break;
    default: break;
    }
}

void PugTemplate::setExpressionHandler(shared_ptr<IExpressionHandler> expressionHandler)
{
    expressionHandler_ = expressionHandler;
}

shared_ptr<IExpressionHandler> PugTemplate::getExpressionHandler()
{
    return expressionHandler_;
}

} // namespace tmpl
} // namespace pugcpp