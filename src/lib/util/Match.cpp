#include "Match.hpp"

namespace pugcpp
{
namespace util
{
Match::Match(int start, int end, const string &src) : m_nStart(start), m_nEnd(end), m_sSrc(src)
{
}

int Match::getStart()
{
    return m_nStart;
}

int Match::getEnd()
{
    return m_nEnd;
}

const string &Match::getSrc() const
{
    return m_sSrc;
}
} // namespace util
} // namespace pugcpp