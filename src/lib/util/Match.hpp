#pragma once

#include <string>

using namespace std;

namespace pugcpp
{
namespace util
{
class Match
{
  private:
    int m_nStart;
    int m_nEnd;
    string m_sSrc;

  public:
    Match(int start, int end, const string &src);
    int getStart();
    int getEnd();
    const string &getSrc() const;
};
} // namespace util
} // namespace pugcpp