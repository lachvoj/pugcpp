#ifndef Containers_hpp
#define Containers_hpp

#include <map>
#include <memory>
#include <vector>

using namespace std;

namespace pugcpp
{
namespace util
{
class Containers
{
  private:
    Containers();

  public:
    template <typename A, typename B>
    static shared_ptr<vector<A>> getMapKeys(map<A, B> &map);
};
} // namespace util
} // namespace pugcpp
#endif
