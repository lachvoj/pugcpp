#include "Compiler.hpp"

namespace pugcpp
{
namespace compiler
{
Compiler::Compiler(shared_ptr<Node> rootNode) : rootNode_(rootNode)
{
}

Compiler::Compiler(shared_ptr<Node> rootNode, PugTemplate *tmplt) : rootNode_(rootNode), template_(tmplt)
{
}

Compiler::Compiler(shared_ptr<Node> rootNode, PugTemplate *tmplt, bool prettyPrint)
: rootNode_(rootNode), template_(tmplt), prettyPrint_(prettyPrint)
{
}

string Compiler::compileToString(PugModel &model)
{
    ostringstream writer;
    compile(model, writer);

    return writer.str();
}

void Compiler::compile(PugModel &model, ostringstream &w)
{
    if (template_ == nullptr)
        throw Exception("Compiler: Template is not set!");
    IndentWriter writer(w);
    writer.setUseIndent(prettyPrint_);
    rootNode_->execute(writer, model, *template_);
}

void Compiler::setPrettyPrint(bool prettyPrint)
{
    prettyPrint_ = prettyPrint;
}

void Compiler::setTemplate(PugTemplate *pugTemplate)
{
    template_ = pugTemplate;
}
} // namespace compiler
} // namespace pugcpp
