#include "./Containers.hpp"

namespace pugcpp
{
namespace util
{

template <typename A, typename B>
shared_ptr<vector<A>> Containers::getMapKeys(map<A, B> &m)
{
    shared_ptr<vector<A>> ret = make_shared<vector<A>>();
    for (typename map<A, B>::iterator it = m.begin(); it != m.end(); ++it)
    {
        ret->push_back(it->first);
    }

    return ret;
}
} // namespace util
} // namespace pugcpp