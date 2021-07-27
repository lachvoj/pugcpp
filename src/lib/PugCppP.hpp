#ifndef PugCppP_hpp
#define PugCppP_hpp

#include <any>
#include <istream>
#include <memory>
#include <ostream>
#include <string>

#include "expression/IExpressionHandler.hpp"
#include "expression/V8ExpressionHandler.hpp"
#include "parser/Parser.hpp"
#include "parser/node/MixinNode.hpp"
#include "parser/node/Node.hpp"
#include "template/FileTemplateLoader.hpp"
#include "template/ITemplateLoader.hpp"
#include "template/PugTemplate.hpp"

using namespace std;

namespace pugcpp
{
using namespace parser::node;
using namespace tmpl;
using namespace expression;

class PugCppP
{
  public:
    static void getTemplate(PugTemplate &ret, const string &filename);
    static void getTemplate(PugTemplate &ret, const string &filename, const string &extension);
    static void getTemplate(PugTemplate &ret, istream &reader, const string &name);
    static void getTemplate(PugTemplate &ret, istream &reader, const string &name, const string &extension);
    static string templateToString(PugTemplate &tmplt, map<string, any> *model);

  private:
    static const string encodingUTF8;
    static void createTemplate(
        PugTemplate &ret,
        const string &filename,
        shared_ptr<ITemplateLoader> loader,
        shared_ptr<IExpressionHandler> expressionHandler);
};
} // namespace pugcpp
#endif
