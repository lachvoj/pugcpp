#ifndef BlockNode_hpp
#define BlockNode_hpp

#include <vector>

#include "../../lexer/token/Block.hpp"

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
using namespace lexer::token;

class BlockNode : public Node
{
  private:
    bool yield_ = false;
    shared_ptr<BlockNode> yieldBlock_;
    Block::E_MODE mode_;
    vector<shared_ptr<Node>> prepended_;
    vector<shared_ptr<Node>> appended_;
    Parser *parser_ = nullptr;
    bool subBlock_;

  public:
    BlockNode();
    bool isYield();
    void setYield(bool yield);
    shared_ptr<BlockNode> getYieldBlock();
    void setYieldBlock(shared_ptr<BlockNode> yieldBlock);
    Block::E_MODE getMode();
    void setMode(Block::E_MODE mode);
    vector<shared_ptr<Node>> &getPrepended();
    void setPrepended(vector<shared_ptr<Node>> &prepended);
    vector<shared_ptr<Node>> &getAppended();
    void setAppended(vector<shared_ptr<Node>> &appended);
    const Parser *getParser() const;
    void setParser(Parser *parser);
    bool isSubBlock();
    void setSubBlock(bool subBlock);

    BlockNode &getIncludeBlock();
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt) override;
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
