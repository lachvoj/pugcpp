#ifndef WhileNode_hpp
#define WhileNode_hpp

#include "../../exceptions/ExpressionException.hpp"
#include "../../exceptions/PugCompilerException.hpp"
#include "../../expression/IExpressionHandler.hpp"
#include "../../model/PugModel.hpp"
#include "../../template/PugTemplate.hpp"

#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
using namespace exceptions;
using namespace tmpl;

class WhileNode : public Node
{
  public:
    WhileNode();
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp

#endif // WhileNode_hpp
