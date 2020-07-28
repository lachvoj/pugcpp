#ifndef TextNode_hpp
#define TextNode_hpp

#include "../../compiler/Utils.hpp"
#include "../../exceptions/ExpressionException.hpp"
#include "../../exceptions/PugCompilerException.hpp"

#include "Node.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
using namespace compiler;
using namespace exceptions;

class TextNode : public Node
{
  private:
    string value_ = "";
    vector<any> preparedValue_;
    void prepare();

  public:
    TextNode();
    const string &getValue() const;
    void setValue(const string &value);
    void appendText(const string &txt);
    void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
};
} // namespace node
} // namespace parser
} // namespace pugcpp

#endif
