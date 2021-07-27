#ifndef BlockCommentNode_hpp
#define BlockCommentNode_hpp

#include "../../compiler/IndentWriter.hpp"

#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
class BlockCommentNode : public Node
{
  private:
    bool buffered_;

  public:
    BlockCommentNode();
    bool isBuffered();
    void setBuffered(bool buffered);
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt) override;
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
