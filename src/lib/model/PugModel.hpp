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

#include "../../../3d/v8/include/libplatform/libplatform.h"
#include "../../../3d/v8/include/v8.h"

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
    vector<map<string, any>> scopes_;
    vector<shared_ptr<void>> contexts_;
    map<string, MixinNode *> mixins_;
    map<string, shared_ptr<IFilter>> filter_;

  public:
    static const string NON_LOCAL_VARS;
    static const string CONTEXT_VAR_NAME;

    PugModel(const map<string, any> *defaults);

    void pushScope();
    void popScope();
    shared_ptr<void> getCurrentScopeContext();
    void setCurrentScopeContext(shared_ptr<void> context);
    void setMixin(const string &name, MixinNode *node);
    MixinNode *getMixin(const string &name);
    void clear();
    bool containsKey(const string &key);
    bool containsValue(const any *value);
    void entrySet(vector<pair<string, any>> &entries);
    any *get(const string &key);
    bool isEmpty();
    void keySet(vector<string> &keys);
    any put(const string &key, const any &value);
    void putAll(const map<string, any> &m);
    bool remove(const string &key);
    size_t size();
    void values(vector<any> &values);
    shared_ptr<IFilter> getFilter(const string &name);
    void addFilter(const string &name, const shared_ptr<IFilter> &filter);
};
} // namespace model
} // namespace pugcpp
#endif
