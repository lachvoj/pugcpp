#ifndef BlockNode_hpp
#define BlockNode_hpp

#include <vector>

#include "Node.hpp"
#include "TagNode.hpp"

namespace pugcpp
{
namespace parser
{
// forward declaration
class Parser;

namespace node
{
class BlockNode : public Node
{
  private:
    bool yield_ = false;
    shared_ptr<BlockNode> yieldBlock_;
    string mode_;
    vector<shared_ptr<Node>> prepended_;
    vector<shared_ptr<Node>> appended_;
    shared_ptr<Parser> parser_;
    bool subBlock_;

  public:
    BlockNode();
    bool isYield();
    void setYield(bool yield);
    shared_ptr<BlockNode> getYieldBlock();
    void setYieldBlock(shared_ptr<BlockNode> yieldBlock);
    const string &getMode();
    void setMode(const string &mode);
    vector<shared_ptr<Node>> &getPrepended();
    void setPrepended(vector<shared_ptr<Node>> &prepended);
    vector<shared_ptr<Node>> &getAppended();
    void setAppended(vector<shared_ptr<Node>> &appended);
    shared_ptr<Parser> getParser();
    void setParser(shared_ptr<Parser> parser);
    bool isSubBlock();
    void setSubBlock(bool subBlock);
    
    BlockNode &getIncludeBlock();
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
