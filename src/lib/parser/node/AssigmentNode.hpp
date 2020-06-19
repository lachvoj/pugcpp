#pragma once

#include "../../compiler/IndentWriter.hpp"
#include "../../model/PugModel.hpp"
#include "../../template/ITemplateLoader.hpp"
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
    void execute(compiler::IndentWriter &writer, model::PugModel &model, tmpl::PugTemplate &tmplt) override;
};
} // namespace node
} // namespace parser
} // namespace pugcpp
