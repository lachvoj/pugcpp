#ifndef CommentNode_hpp
#define CommentNode_hpp

#include "../../compiler/IndentWriter.hpp"

#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
class CommentNode : public Node
{
  private:
    bool buffered_;

  public:
    CommentNode();
    bool isBuffered();
    void setBuffered(bool buffered);
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
