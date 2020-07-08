#ifndef ClassUtils_hpp
#define ClassUtils_hpp

#include <type_traits>

using namespace std;

namespace pugcpp
{
namespace util
{
template <typename Base, typename T>
inline bool instanceof (const T *)
{
    return is_base_of<Base, T>::value;
}
} // namespace util
} // namespace pugcpp
#endif
