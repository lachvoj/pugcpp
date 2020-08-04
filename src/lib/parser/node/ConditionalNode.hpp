#ifndef ConditionalNode_hpp
#define ConditionalNode_hpp

#include <memory>
#include <vector>

#include "../../exceptions/ExpressionException.hpp"
#include "../../exceptions/PugCompilerException.hpp"
#include "../../expression/IExpressionHandler.hpp"
#include "../../model/PugModel.hpp"
#include "../../template/PugTemplate.hpp"

#include "IfConditionNode.hpp"
#include "Node.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
using namespace model;
using namespace expression;
using namespace exceptions;
using namespace tmpl;

class ConditionalNode : public Node
{
  private:
    vector<shared_ptr<IfConditionNode>> conditions_;

    bool checkCondition(PugModel &model, const string &condition, shared_ptr<IExpressionHandler> expressionHandler);

  public:
    ConditionalNode();

    vector<shared_ptr<IfConditionNode>> &getConditions();
    void setConditions(const vector<shared_ptr<IfConditionNode>> &conditions);

    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp

#endif // ConditionalNode_hpp