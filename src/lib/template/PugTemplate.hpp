#ifndef PugTemplate_hpp
#define PugTemplate_hpp

#include <memory>
#include <sstream>

#include "../compiler/Compiler.hpp"
#include "../include/PugCpp.hpp"
#include "../lexer/token/Doctypes.hpp"
#include "../util/StringUtils.hpp"

#include "ITemplateLoader.hpp"

using namespace std;

namespace pugcpp
{
// forward declaration
namespace expression
{
class IExpressionHandler;
}
namespace model
{
class PugModel;
}
namespace parser
{
namespace node
{
class Node;
}
} // namespace parser

namespace tmpl
{
using namespace expression;
using namespace parser::node;
using namespace model;

class PugTemplate
{
  private:
    bool prettyPrint_ = false;
    shared_ptr<Node> rootNode_;
    bool terse_ = false;
    bool xml_ = false;
    shared_ptr<ITemplateLoader> templateLoader_;
    shared_ptr<IExpressionHandler> expressionHandler_;
    string doctypeLine_;

  public:
    void process(PugModel &model, ostringstream &writer);
    void setPrettyPrint(bool prettyPrint);
    bool isPrettyPrint();
    shared_ptr<Node> getRootNode();
    void setRootNode(shared_ptr<Node> rootNode);
    bool isTerese();
    bool isXml();
    void setTemplateLoader(shared_ptr<ITemplateLoader> templateLoader);
    shared_ptr<ITemplateLoader> getTemplateLoader();
    void setDoctype(const string &name);
    const string &getDoctypeLine();
    void setMode(PugCpp::Mode mode);
    void setExpressionHandler(shared_ptr<IExpressionHandler> expressionHandler);
    shared_ptr<IExpressionHandler> getExpressionHandler();
};
} // namespace tmpl
} // namespace pugcpp
#endif
