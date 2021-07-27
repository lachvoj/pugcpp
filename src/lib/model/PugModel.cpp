#include "./PugModel.hpp"

#include "../parser/node/MixinNode.hpp"

namespace pugcpp
{
namespace model
{
const string PugModel::LOCALS = "locals";
const string PugModel::NON_LOCAL_VARS = "nonLocalVars";

template <class T>
inline void hash_combine(std::size_t &seed, const T &v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

PugModel::PugModel(const map<string, any> *defaults)
{
    scopes_.push_back(baseModel_);
    contexts_.emplace_back();
    if (defaults != nullptr)
    {
        putAll(*defaults);
    }
}

void PugModel::pushScope()
{
    scopes_.emplace_back();
    contexts_.emplace_back();
}

void PugModel::popScope()
{
    // TODO: debug this!!!
    map<string, any> lastScope = scopes_.back();
    map<string, any>::iterator itNonLocalVars = lastScope.find(NON_LOCAL_VARS);
    if (itNonLocalVars != lastScope.end())
    {
        set<string> nonLocalVars = any_cast<set<string>>((*itNonLocalVars).second);
        vector<map<string, any>>::reverse_iterator rIterator = scopes_.rbegin();
        rIterator++;
        size_t countFoundNonLocalVars = 0;
        for (vector<map<string, any>>::reverse_iterator i = (rIterator + 1); (i + 1) != scopes_.rend(); ++i)
        {

            map<string, any> scope = *i;
            for (set<string>::iterator nonLocalVar = nonLocalVars.begin(); nonLocalVar != nonLocalVars.end();
                 nonLocalVar++)
            {
                if (i->find(*nonLocalVar) != i->end())
                {
                    scope.insert(pair<string, any>(*nonLocalVar, static_cast<any>(*(lastScope.find(*nonLocalVar)))));
                    countFoundNonLocalVars++;
                }
            }
            if (nonLocalVars.size() == countFoundNonLocalVars)
                break;
        }
    }
    scopes_.pop_back();
    contexts_.pop_back();
}

shared_ptr<void> PugModel::getCurrentScopeContext()
{
    return contexts_.back();
}

void PugModel::setCurrentScopeContext(shared_ptr<void> context)
{
    contexts_.back() = context;
}

void PugModel::setMixin(const string &name, MixinNode *node)
{
    mixins_.emplace(name, node);
}

MixinNode *PugModel::getMixin(const string &name)
{
    auto found = mixins_.find(name);
    if (found == mixins_.end())
        return nullptr;

    return found->second;
}

void PugModel::clear()
{
    scopes_.clear();
    scopes_.emplace_back();
    contexts_.clear();
    contexts_.emplace_back();
}

bool PugModel::containsKey(const string &key)
{
    for (vector<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
    {
        rIt++;
        if (rIt->find(key) != rIt->end())
        {
            return true;
        }
    }
    return false;
}

bool PugModel::containsValue(const any *value)
{

    for (vector<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
    {
        rIt++;
        for (auto &i : *rIt)
        {
            // TODO: double check this!!!!!!!!!!!!
            if (any_cast<void *>(i.second) == any_cast<void *>(value))
            {
                return true;
            }
        }
    }
    return false;
}

void PugModel::entrySet(vector<pair<string, any>> &entries)
{
    entries.reserve(size());
    for (vector<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
    {
        rIt++;
        for (auto &i : *rIt)
        {
            entries.push_back(i);
        }
    }
}

any *PugModel::get(const string &key)
{
    for (vector<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
    {
        rIt++;
        auto val = rIt->find(key);
        if (val != rIt->end())
        {
            return &(val->second);
        }
    }

    return nullptr;
}

bool PugModel::isEmpty()
{
    return (size() == 0);
}

void PugModel::keySet(vector<string> &keys)
{
    keys.reserve(size());
    for (vector<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
    {
        rIt++;
        for (auto &i : *rIt)
        {
            keys.push_back(i.first);
        }
    }
}

any PugModel::put(const string &key, const any &value)
{
    any currentValue = get(key);
    scopes_.back()[key] = value;

    return currentValue;
}

void PugModel::putAll(const map<string, any> &m)
{
    scopes_.back().insert(m.begin(), m.end());
}

bool PugModel::remove(const string &key)
{
    for (vector<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
    {
        rIt++;
        auto val = rIt->find(key);
        if (val != rIt->end())
        {
            rIt->erase(val);
            return true;
        }
    }
    return false;
}

size_t PugModel::size()
{
    size_t ret = 0;
    for (auto &scope : scopes_)
    {
        ret += scope.size();
    }

    return ret;
}

void PugModel::values(vector<any> &values)
{
    values.reserve(size());
    for (vector<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
    {
        rIt++;
        for (auto &i : *rIt)
        {
            values.push_back(i.second);
        }
    }
}

shared_ptr<IFilter> PugModel::getFilter(const string &name)
{
    return filter_.find(name)->second;
}

void PugModel::addFilter(const string &name, const shared_ptr<IFilter> &filter)
{
    filter_[name] = filter;
}

} // namespace model
} // namespace pugcpp
