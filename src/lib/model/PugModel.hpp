#ifndef PugModel_hpp
#define PugModel_hpp

#include <any>
#include <deque>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "../filter/IFilter.hpp"
#include "../util/HashUtils.hpp"

using namespace std;

namespace pugcpp
{
// forward declaration
namespace parser
{
namespace node
{
class MixinNode;
} // namespace node
} // namespace parser

namespace model
{
using namespace filter;
using namespace parser::node;

class PugModel : public map<string, any>
{
  private:
    static const string LOCALS;

    map<string, any> baseModel_;
    deque<map<string, any>> scopes_;
    map<string, MixinNode> mixins_;
    map<string, shared_ptr<IFilter>> filter_;

  public:
    static const string NON_LOCAL_VARS;

    PugModel(const map<string, any> *defaults);

    void pushScope();
    void popScope();
    void setMixin(const string &name, const MixinNode &node);
    MixinNode *getMixin(const string &name);
    void clear();
    bool containsKey(const string &key);
    bool containsValue(const any *value);
    list<pair<string, any>> entrySet();
    any get(const string &key);
    bool isEmpty();
    vector<string> keySet();
    any put(const string &key, const any &value);
    void putAll(const map<string, any> &m);
    bool remove(const string &key);
    int size();
    list<any> values();
    shared_ptr<IFilter> getFilter(const string &name);
    void addFilter(const string &name, const shared_ptr<IFilter> &filter);
};
} // namespace model
} // namespace pugcpp
#endif
