#ifndef FilterNode_hpp
#define FilterNode_hpp

#include <memory>
#include <string>
#include <vector>

#include "../../compiler/IndentWriter.hpp"
#include "../../compiler/Utils.hpp"
#include "../../exceptions/ExpressionException.hpp"
#include "../../exceptions/PugCompilerException.hpp"
#include "../../filter/IFilter.hpp"
#include "../../template/PugTemplate.hpp"
#include "../../util/StringUtils.hpp"

#include "Attr.hpp"
#include "Node.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
using namespace filter;
using namespace util;
using namespace compiler;
using namespace exceptions;
using namespace tmpl;

class FilterNode : public Node
{
  private:
    vector<Attr> attributes_;
    shared_ptr<Node> textBlock_;

  public:
    FilterNode();
    vector<Attr> &getAttributes();
    bool hasTextBlock();
    shared_ptr<Node> getTextBlock();
    void setTextBlock(shared_ptr<Node> &textBlock);
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt) override;
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif // FilterNode_hpp
