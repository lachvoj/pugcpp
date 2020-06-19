#include "include/PugCpp.hpp"

#include "PugCppP.hpp"
#include "expression/DummyExpressionHandler.hpp"
#include "parser/Parser.hpp"
#include "parser/node/Node.hpp"
#include "template/FileTemplateLoader.hpp"
#include "template/PugTemplate.hpp"

namespace pugcpp
{
// PugCpp
string PugCpp::render(const string &filename, map<string, any> *model)
{
    return render(filename, model, false);
}

string PugCpp::render(const string &filename, map<string, any> *model, bool prettyPrint)
{
    shared_ptr<PugTemplate> tmpl = PugCppP::getTemplate(filename);
    tmpl->setPrettyPrint(prettyPrint);

    return PugCppP::templateToString(*tmpl, model);
}

// PugCppP
const string PugCppP::encodingUTF8 = "UTF-8";

shared_ptr<PugTemplate> PugCppP::getTemplate(const string &filename)
{
    return createTemplate(
        filename, make_shared<FileTemplateLoader>("", encodingUTF8), make_shared<DummyExpressionHandler>());
}

shared_ptr<PugTemplate> PugCppP::getTemplate(const string &filename, const string &extension)
{
    return createTemplate(
        filename, make_shared<FileTemplateLoader>("", encodingUTF8, extension), make_shared<DummyExpressionHandler>());
}

shared_ptr<PugTemplate> PugCppP::getTemplate(istream &reader, const string &name)
{
}

shared_ptr<PugTemplate> PugCppP::getTemplate(istream &reader, const string &name, const string &extension)
{
}

string PugCppP::templateToString(PugTemplate &tmpl, map<string, any> *model)
{
    model::PugModel pugModel(model);
    stringstream writer;

    tmpl.process(pugModel, writer);

    return writer.str();
}

shared_ptr<PugTemplate> PugCppP::createTemplate(const string &filename,
                                                shared_ptr<ITemplateLoader> loader,
                                                shared_ptr<IExpressionHandler> expressionHandler)
{
    parser::Parser parser(filename, loader, expressionHandler);
    shared_ptr<Node> root = parser.parse();
    shared_ptr<PugTemplate> tmpl = make_shared<PugTemplate>();
    tmpl->setExpressionHandler(expressionHandler);
    tmpl->setTemplateLoader(loader);
    tmpl->setRootNode(root);

    return tmpl;
}
} // namespace pugcpp