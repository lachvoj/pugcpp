#pragma once

#include <any>
#include <string>
#include <vector>

#include "../parser/node/Attr.hpp"

using namespace std;

namespace filter
{
class IFilter
{
  public:
    virtual string convert(const string &source, const vector<parserNode::Attr> &attributes,
                           const map<string, any> &model) = 0;
};
} // namespace filter
