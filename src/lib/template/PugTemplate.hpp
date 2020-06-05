#pragma once

#include <memory>
#include <sstream>

#include "../parser/node/Node.hpp"
#include "ITemplateLoader.hpp"
#include "../expression/IExpressionHandler.hpp"
#include "../model/PugModel.hpp"
#include "../PugCpp.hpp"

using namespace std;

// forward definition.
namespace parserNode
{
  class Node;
}

namespace tmpl
{
class PugTemplate
{
  private:
    bool m_bPrettyPrint = false;
    shared_ptr<parserNode::Node> m_pRootNode;
    bool m_bTerse = false;
    bool m_bXml = false;
    shared_ptr<ITemplateLoader> m_pTemplateLoader;
    shared_ptr<expression::IExpressionHandler> m_pExpressionHandler;
    string m_sDoctypeLine;

  public:
    void process(model::PugModel model, stringstream &writer);
    void setPrettyPrint(bool prettyPrint);
    bool isPrettyPrint();
    shared_ptr<parserNode::Node> getRootNode();
    void setRootNode(shared_ptr<parserNode::Node> rootNode);
    bool isTerese();
    bool isXml();
    void setTemplateLoader(shared_ptr<ITemplateLoader> templateLoader);
    shared_ptr<ITemplateLoader> getTemplateLoader();
    void setDoctype(const string &name);
    const string &getDoctypeLine();
    void setMode(pugcpp::PugCpp::Mode mode);
    void setExpressionHandler(shared_ptr<expression::IExpressionHandler> expressionHandler);
    shared_ptr<expression::IExpressionHandler> getExpressionHandler();
};
} // namespace tmpl
