#pragma once

#include <any>
#include <list>
#include <map>
#include <memory>
#include <string>

#include "../../model/PugModel.hpp"
#include "../../template/PugTemplate.hpp"
#include "Attr.hpp"
#include "Node.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
class AttrsNode : public Node
{
  private:
    static const string selfClosingTags[];
    bool textOnly;

    string attributeValueToString(any value);

  protected:
    list<Attr> m_lclAttributes;
    list<string> m_lsAttiributeBlocks;
    list<string> m_lsAttributeNames;
    bool m_bSelfClosing = false;
    shared_ptr<Node> m_pclCodeNode;

  public:
    AttrsNode &setAttribute(const string &key, any value, bool escaped);
    string getAttribute(const string &key);
    shared_ptr<AttrsNode> clone();
    void addAttributes(string src);
    void setSelfClosing(bool selfClosing);
    bool isSelfClosing();
    void setTextOnly(bool textOnly);
    bool isTextOnly();
    void setCodeNode(shared_ptr<Node> codeNode);
    shared_ptr<Node> getCodeNode();
    bool hasCodeNode();
    string visitAttributes(model::PugModel &model, tmpl::PugTemplate &tmpl);
    string attrsToString(map<string, string> &attrs, tmpl::PugTemplate &tmpl);
};
} // namespace node
} // namespace parser
} // namespace pugcpp
