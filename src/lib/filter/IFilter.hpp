#ifndef IFilter_hpp
#define IFilter_hpp

#include <any>
#include <string>
#include <vector>

#include "../parser/node/Attr.hpp"

using namespace std;

namespace pugcpp
{
namespace filter
{
using namespace parser::node;

class IFilter
{
  public:
    virtual string convert(const string &source, const vector<Attr> &attributes, const map<string, any> &model) = 0;
};
} // namespace filter
} // namespace pugcpp
#endif
