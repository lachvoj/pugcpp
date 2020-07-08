#include "Compiler.hpp"

namespace pugcpp
{
namespace compiler
{
Compiler::Compiler(shared_ptr<Node> rootNode) : m_pRootNode(rootNode)
{
}

string Compiler::compileToString(PugModel &model)
{
    stringstream writer;
    compile(model, writer);

    return writer.str();
}

void Compiler::compile(PugModel &model, stringstream &w)
{
    IndentWriter writer(w);
    writer.setUseIndent(m_bPrettyPrint);
    m_pRootNode->execute(writer, model, *m_pTemplate);
}

void Compiler::setPrettyPrint(bool prettyPrint)
{
    m_bPrettyPrint = prettyPrint;
}

void Compiler::setTemplate(shared_ptr<PugTemplate> pugTemplate)
{
    m_pTemplate = pugTemplate;
}

void Compiler::setExpressionHandler(shared_ptr<expression::IExpressionHandler> expressionHandler)
{
    m_pExpressionHandler = expressionHandler;
}

} // namespace compiler
} // namespace pugcpp
