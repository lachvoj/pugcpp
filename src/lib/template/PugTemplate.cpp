#include "PugTemplate.hpp"

namespace pugcpp
{
namespace tmpl
{
using namespace util;
using namespace lexer::token;

void PugTemplate::process(PugModel &model, stringstream &writer)
{
    compiler::Compiler compiler(m_pRootNode);
    compiler.setPrettyPrint(m_bPrettyPrint);
    compiler.setTemplate(shared_ptr<PugTemplate>(this));
    compiler.setExpressionHandler(m_pclExpressionHandler);
    compiler.compile(model, writer);
}

void PugTemplate::setPrettyPrint(bool prettyPrint)
{
    m_bPrettyPrint = prettyPrint;
}

bool PugTemplate::isPrettyPrint()
{
    return m_bPrettyPrint;
}

shared_ptr<Node> PugTemplate::getRootNode()
{
    return m_pRootNode;
}

void PugTemplate::setRootNode(shared_ptr<Node> rootNode)
{
    m_pRootNode = rootNode;
}

bool PugTemplate::isTerese()
{
    return m_bTerse;
}

bool PugTemplate::isXml()
{
    return m_bXml;
}

void PugTemplate::setTemplateLoader(shared_ptr<ITemplateLoader> templateLoader)
{
    m_pclTemplateLoader = templateLoader;
}

shared_ptr<ITemplateLoader> PugTemplate::getTemplateLoader()
{
    return m_pclTemplateLoader;
}

void PugTemplate::setDoctype(const string &name)
{
    string l_sName = name;
    if (l_sName == "")
    {
        l_sName = "default";
    }
    // TODO: check l_sName unknown
    m_sDoctypeLine = Doctypes::get(l_sName);
    m_bTerse = ("<!doctype html>" == StringUtils::toLowerCase(m_sDoctypeLine));
    m_bXml = StringUtils::startsWith(m_sDoctypeLine, "<?xml");
}

const string &PugTemplate::getDoctypeLine()
{
}

void PugTemplate::setMode(pugcpp::PugCpp::Mode mode)
{
}

void PugTemplate::setExpressionHandler(shared_ptr<IExpressionHandler> expressionHandler)
{
    m_pclExpressionHandler = expressionHandler;
}

shared_ptr<IExpressionHandler> PugTemplate::getExpressionHandler()
{
    return m_pclExpressionHandler;
}

} // namespace tmpl
} // namespace pugcpp