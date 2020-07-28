#include "Options.hpp"

namespace pugcpp
{
namespace util
{
int Options::getStart()
{
    return start_;
}

void Options::setStart(int start)
{
    start_ = start;
}

int Options::getEnd()
{
    return end_;
}

void Options::setEnd(int end)
{
    end_ = end;
}

bool Options::isIncludeLineComment()
{
    return includeLineComment_;
}

void Options::setIncludeLineComment(bool includeLineCommnet)
{
    includeLineComment_ = includeLineCommnet;
}

} // namespace util
} // namespace pugcpp