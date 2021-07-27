#ifndef EachNode_hpp
#define EachNode_hpp

#include <any>
#include <map>
#include <string>

#include "../../exceptions/ExpressionException.hpp"
#include "../../exceptions/PugCompilerException.hpp"
#include "../../expression/IExpressionHandler.hpp"
#include "../../model/PugModel.hpp"
#include "../../template/PugTemplate.hpp"

#include "Node.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
using namespace exceptions;
using namespace model;
using namespace tmpl;

class EachNode : public Node
{
  private:
    string key_;
    string code_;
    shared_ptr<Node> elseNode_;

    void run(IndentWriter &writer, PugModel &model, any &result, PugTemplate &tmplt);
    void runMap(map<any, any> &result, PugModel &model, IndentWriter &writer, PugTemplate &tmplt);
    void executeElseNode(PugModel &model, IndentWriter &writer, PugTemplate &tmplt);

  public:
    EachNode();

    const string &getCode() const;
    void setCode(const string &code);
    const string &getKey() const;
    void setKey(const string &key);
    shared_ptr<Node> &getElseNode();
    void setElseNode(shared_ptr<Node> &elseNode);

    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt) override;
};
} // namespace node
} // namespace parser
} // namespace pugcpp

#endif // EachNode_hpp
