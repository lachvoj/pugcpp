#pragma once

#include <list>
#include <memory>
#include <stdexcept>
#include <string>

#include "../../compiler/IndentWriter.hpp"
#include "../../model/PugModel.hpp"
#include "../../template/PugTemplate.hpp"

using namespace std;

namespace pugcpp
{
// forward definition.
namespace tmpl
{
class PugTemplate;
}

namespace parser
{
namespace node
{
using namespace compiler;
using namespace model;
using namespace tmpl;

class Node
{
  protected:
    list<shared_ptr<Node>> m_clNodes;
    int m_nLlineNumber;
    string m_sName;
    string m_sValue;
    shared_ptr<Node> m_pBlock = nullptr;
    string m_sFileName;

  public:
    virtual void execute(IndentWriter &writer, PugModel &model, PugTemplate &tmplt);
    void setLineNumber(int lineNumber);
    int getLineNumber() const;
    void setValue(const string &value);
    const string &getValue() const;
    void setName(const string &name);
    const string &getName() const;
    void push(shared_ptr<Node> node);
    void setNodes(list<shared_ptr<Node>> &nodes);
    const list<shared_ptr<Node>> &getNodes();
    shared_ptr<Node> pollNode();
    bool hasNodes();
    bool hasBlock();
    void setBlock(shared_ptr<Node> block);
    shared_ptr<Node> getBlock();
    void setFileName(const string &fileName);
    const string &getFileName() const;
    shared_ptr<Node> clone();
};
} // namespace node
} // namespace parser
} // namespace pugcpp
