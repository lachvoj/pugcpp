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
    if (defaults != nullptr)
    {
        putAll(*defaults);
    }
}

void PugModel::pushScope()
{
    scopes_.emplace_back();
}

void PugModel::popScope()
{
    // TODO: debug this!!!
    map<string, any> lastScope = scopes_.back();
    map<string, any>::iterator itNonLocalVars = lastScope.find(NON_LOCAL_VARS);
    if (itNonLocalVars != lastScope.end())
    {
        set<string> nonLocalVars = any_cast<set<string>>((*itNonLocalVars).second);
        deque<map<string, any>>::reverse_iterator rIterator = scopes_.rbegin();
        rIterator++;
        int countFoundNonLocalVars = 0;
        for (deque<map<string, any>>::reverse_iterator i = (rIterator + 1); (i + 1) != scopes_.rend(); ++i)
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
}

void PugModel::setMixin(const string &name, const MixinNode &node)
{
    mixins_.insert(pair<string, MixinNode>(name, node));
}

MixinNode *PugModel::getMixin(const string &name)
{
    auto found  = mixins_.find(name);
    if (found == mixins_.end())
        return nullptr;
    
    return &(found->second);
}

void PugModel::clear()
{
    scopes_.clear();
    scopes_.emplace_back();
}

bool PugModel::containsKey(const string &key)
{
    for (deque<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
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

    for (deque<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
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

list<pair<string, any>> PugModel::entrySet()
{
    list<pair<string, any>> entries;
    for (deque<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
    {
        rIt++;
        for (auto &i : *rIt)
        {
            // TODO: double check this!!!!!!!!!!!!
            entries.push_back(i);
        }
    }
    return entries;
}

any PugModel::get(const string &key)
{
    for (deque<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
    {
        rIt++;
        auto val = rIt->find(key);
        if (val != rIt->end())
        {
            return *val;
        }
    }

    return nullptr;
}

bool PugModel::isEmpty()
{
    return (keySet().size() == 0);
}

list<string> PugModel::keySet()
{
    list<string> keys;
    for (deque<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
    {
        rIt++;
        for (auto &i : *rIt)
        {
            // TODO: double check this!!!!!!!!!!!!
            keys.push_back(i.first);
        }
    }
    return keys;
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
    for (deque<map<string, any>>::reverse_iterator rIt = scopes_.rbegin(); (rIt + 1) != scopes_.rend();)
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

int PugModel::size()
{
    return keySet().size();
}

list<any> PugModel::values()
{
    list<string> ks = keySet();
    list<any> ret(ks.size());
    for (string &key : ks)
    {
        ret.push_back(get(key));
    }
    return ret;
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
