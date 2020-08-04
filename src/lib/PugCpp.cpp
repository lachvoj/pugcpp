#include "./PugCppP.hpp"

#include "include/PugCpp.hpp"

namespace pugcpp
{
// PugCpp
string PugCpp::render(const string &filename, map<string, any> *model, bool prettyPrint, Mode mode)
{
    PugTemplate tmpl;
    PugCppP::getTemplate(tmpl, filename);
    tmpl.setPrettyPrint(prettyPrint);
    tmpl.setMode(mode);

    return PugCppP::templateToString(tmpl, model);
}

// PugCppP
const string PugCppP::encodingUTF8 = "UTF-8";

void PugCppP::getTemplate(PugTemplate &ret, const string &filename)
{
    return createTemplate(
        ret, filename, make_shared<FileTemplateLoader>(".", encodingUTF8), make_shared<DummyExpressionHandler>());
}

void PugCppP::getTemplate(PugTemplate &ret, const string &filename, const string &extension)
{
    return createTemplate(
        ret,
        filename,
        make_shared<FileTemplateLoader>(".", encodingUTF8, extension),
        make_shared<DummyExpressionHandler>());
}

void PugCppP::getTemplate(PugTemplate &ret, istream &reader, const string &name)
{
}

void PugCppP::getTemplate(PugTemplate &ret, istream &reader, const string &name, const string &extension)
{
}

string PugCppP::templateToString(PugTemplate &tmplt, map<string, any> *model)
{
    model::PugModel pugModel(model);
    ostringstream writer(ios_base::out | ios_base::ate);

    tmplt.process(pugModel, writer);

    return writer.str();
}

void PugCppP::createTemplate(
    PugTemplate &ret,
    const string &filename,
    shared_ptr<ITemplateLoader> loader,
    shared_ptr<IExpressionHandler> expressionHandler)
{
    parser::Parser parser(filename, loader, expressionHandler);
    shared_ptr<Node> root = parser.parse();
    ret.setExpressionHandler(expressionHandler);
    ret.setTemplateLoader(loader);
    ret.setRootNode(root);
}
} // namespace pugcpp