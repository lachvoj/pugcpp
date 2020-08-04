#ifndef AttrsNode_hpp
#define AttrsNode_hpp

#include <any>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../../compiler/Utils.hpp"
#include "../../exceptions/Exception.hpp"
#include "../../exceptions/ExpressionException.hpp"
#include "../../exceptions/PugCompilerException.hpp"
#include "../../util/StringUtils.hpp"

#include "Attr.hpp"
#include "ExpressionString.hpp"
#include "Node.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
using namespace exceptions;
using namespace util;
using namespace compiler;

class AttrsNode : public Node
{
  protected:
    struct AttrCmp
    {
        bool operator()(const string &lhs, const string &rhs) const;
    };

  private:
    static const set<string> selfClosingTags;

    bool textOnly_ = false;

    string attributeValueToString(any value);
    string attrsToString(const map<string, string, AttrCmp> &attrs);
    void addAttributesToMap(
        map<string, string, AttrCmp> &newAttributes,
        vector<string> &classes,
        vector<bool> classEscaping,
        Attr &attribute,
        PugModel &model,
        PugTemplate &tmplt);
    any evaluateExpression(
        ExpressionString &attribute,
        PugModel &model,
        shared_ptr<IExpressionHandler> expressionHandler);
    string getInterpolatedAttributeValue(
        const string &name,
        const string &attributeValue,
        bool escaped,
        PugModel &model,
        PugTemplate &tmplt);
    Attr *getAttributeByName(const string &name);

  protected:
    vector<Attr> attributes_;
    vector<string> attiributeBlocks_;
    bool selfClosing_ = false;
    shared_ptr<Node> codeNode_;

    AttrsNode(NodeType type);
    string visitAttributes(PugModel &model, PugTemplate &tmplt);
    void attrs(map<string, string, AttrCmp> &retAttrs, PugModel &model, PugTemplate &tmplt, vector<Attr> &attrs);

  public:
    AttrsNode() = delete;
    string getAttribute(const string &key);
    void setAttribute(const string &key, any value, bool escaped);
    void addAttributes(const string &src);
    bool isSelfClosing();
    bool isSelfClosing(PugTemplate &tmplt);
    void setSelfClosing(bool selfClosing);
    bool isTextOnly();
    void setTextOnly(bool textOnly);
    shared_ptr<Node> getCodeNode();
    void setCodeNode(shared_ptr<Node> codeNode);
    bool hasCodeNode();
    bool isTerese(PugTemplate &tmplt);
    // shared_ptr<AttrsNode> clone();
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
