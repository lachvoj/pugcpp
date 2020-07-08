#ifndef CallNode_hpp
#define CallNode_hpp

#include "AttrsNode.hpp"
// #include "../../compiler/IndentWriter.hpp"
// #include "../../model/PugModel.hpp"
// #include "../../template/PugTemplate.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
class CallNode : public AttrsNode
{
  private:
    bool m_bDynamicMixins = false;
    bool m_bCall = false;

  protected:
    list<string> m_conArguments;

  public:
    list<string> &getArguments();
    void setArguments(const string &arguments);
    bool isCall();
    void setCall(bool call);
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
