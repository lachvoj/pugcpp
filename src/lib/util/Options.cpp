#include "Options.hpp"

namespace pugcpp
{
namespace util
{
int Options::getStart()
{
    return m_nStart;
}

void Options::setStart(int start)
{
    m_nStart = start;
}

int Options::getEnd()
{
    return m_nEnd;
}

void Options::setEnd(int end)
{
    m_nEnd = end;
}

bool Options::isIncludeLineComment()
{
    return m_bIncludeLineComment;
}

void Options::setIncludeLineComment(bool includeLineCommnet)
{
    m_bIncludeLineComment = includeLineCommnet;
}

} // namespace util
} // namespace pugcpp