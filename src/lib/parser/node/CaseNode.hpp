#ifndef CaseNode_hpp
#define CaseNode_hpp

#include <vector>

#include "../../exceptions/ExpressionException.hpp"
#include "../../exceptions/PugCompilerException.hpp"
#include "../../expression/IExpressionHandler.hpp"
#include "../../model/PugModel.hpp"
#include "../../template/PugTemplate.hpp"

#include "CaseConditionNode.hpp"
#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
class CaseNode : public Node
{
  private:
    vector<shared_ptr<CaseConditionNode>> caseConditionNodes_;

    bool checkCondition(PugModel &model, shared_ptr<Node> &caseConditionNode, IExpressionHandler &expressionHandler);

  public:
    class When : public Node
    {
      public:
        When();
        void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
    };

    CaseNode();
    
    vector<shared_ptr<CaseConditionNode>> &getCaseConditionNodes();
    void setConditions(const vector<shared_ptr<CaseConditionNode>> &caseConditionNodes);

    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp

#endif // CaseNode_hpp
