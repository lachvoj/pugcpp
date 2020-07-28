#ifndef AssigmentNode_hpp
#define AssigmentNode_hpp

#include <any>

#include "../../compiler/IndentWriter.hpp"
#include "../../exceptions/ExpressionException.hpp"
#include "../../exceptions/PugCompilerException.hpp"
#include "../../model/PugModel.hpp"
#include "../../template/ITemplateLoader.hpp"
#include "../../template/PugTemplate.hpp"

#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
class AssigmentNode : public Node
{
  public:
    AssigmentNode();
    void execute(compiler::IndentWriter &writer, model::PugModel &model, tmpl::PugTemplate &tmplt) override;
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
