#ifndef ExpressionNode_hpp
#define ExpressionNode_hpp

#include <any>
#include <string>

#include "../../exceptions/ExpressionException.hpp"
#include "../../exceptions/PugCompilerException.hpp"
#include "../../util/StringUtils.hpp"

#include "Node.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
namespace node
{
using namespace exceptions;
using namespace util;

class ExpressionNode : public Node
{
  private:
    bool escape_;
    bool buffer_;

  public:
    ExpressionNode();
    void setEscape(bool escape);
    void setBuffer(bool buffer);
    void setValue(const string &value);
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp
#endif
