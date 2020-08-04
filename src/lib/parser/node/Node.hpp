#ifndef Node_hpp
#define Node_hpp

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// #include "../../compiler/IndentWriter.hpp"
// #include "../../model/PugModel.hpp"
// #include "../../template/PugTemplate.hpp"

using namespace std;

namespace pugcpp
{
// forward declarations
namespace compiler
{
class IndentWriter;
}
namespace model
{
class PugModel;
}
namespace tmpl
{
class PugTemplate;
}

namespace parser
{
namespace node
{
using namespace compiler;
using namespace model;
using namespace tmpl;

enum NodeType
{
    e_Default = 0,
    e_AssignmentNode,
    e_AttrsNode,
    e_BlockCommentNode,
    e_BlockNode,
    e_CallNode,
    e_CaseConditionNode,
    e_CaseNode,
    e_CondeNode,
    e_CommentNode,
    e_ContionalNode,
    e_DoctypeNode,
    e_EachNode,
    e_ExpressionNode,
    e_FilterNode,
    e_IfConditionNode,
    e_InterpolationNode,
    e_LiteralNode,
    e_MixinBlockNode,
    e_MixinNode,
    e_TagNode,
    e_TextNode,
    e_WhileNode,
    e_WhenNode
};

class Node
{
  protected:
    NodeType type_;
    vector<shared_ptr<Node>> nodes_;
    int lineNumber_;
    string name_;
    string value_;
    shared_ptr<Node> block_;
    string const *fileName_;
    Node(NodeType type);

  public:
    virtual void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt) = 0;
    const NodeType getType() const;
    void setLineNumber(int lineNumber);
    int getLineNumber() const;
    void setValue(const string &value);
    const string &getValue() const;
    void setName(const string &name);
    const string &getName() const;
    void push(const shared_ptr<Node> &node);
    void setNodes(vector<shared_ptr<Node>> &nodes);
    vector<shared_ptr<Node>> &getNodes();
    shared_ptr<Node> pollNode();
    bool hasNodes();
    bool hasBlock();
    void setBlock(const shared_ptr<Node> &block);
    shared_ptr<Node> getBlock();
    void setFileName(const string &fileName);
    void setFileName(string const *fileName);
    const string &getFileName() const;
    // shared_ptr<Node> clone();
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
