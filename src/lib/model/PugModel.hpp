#pragma once

#include <any>
#include <deque>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "../util/HashUtils.hpp"

#include "../filter/IFilter.hpp"
#include "../parser/node/MixinNode.hpp"

using namespace std;

namespace model
{
class PugModel
{
  private:
    static const string LOCALS;

    map<string, any> baseModel_;
    deque<map<string, any>> scopes_;
    map<string, parserNode::MixinNode> mixins_;
    map<string, shared_ptr<filter::IFilter>> filter_;

  public:
    static const string NON_LOCAL_VARS;

    PugModel(const map<string, any> *defaults);
    ~PugModel();

    void pushScope();
    void popScope();
    void setMixin(const string &name, const parserNode::MixinNode &node);
    parserNode::MixinNode &getMixin(const string &name);
    void clear();
    bool containsKey(const string &key);
    bool containsValue(const any *value);
    list<pair<string, any>> entrySet();
    any get(const string &key);
    bool isEmpty();
    list<string> keySet();
    any put(const string &key, const any &value);
    void putAll(const map<string, any> &m);
    bool remove(const string &key);
    int size();
    list<any> values();
    shared_ptr<filter::IFilter> getFilter(const string &name);
    void addFilter(const string &name, const shared_ptr<filter::IFilter> &filter);
};
} // namespace model
