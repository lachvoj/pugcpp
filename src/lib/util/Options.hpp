#ifndef Options_hpp
#define Options_hpp

namespace pugcpp
{
namespace util
{
class Options
{
  private:
    int m_nStart = 0;
    int m_nEnd = 0;
    bool m_bIncludeLineComment = false;

  public:
    int getStart();
    void setStart(int start);
    int getEnd();
    void setEnd(int end);
    bool isIncludeLineComment();
    void setIncludeLineComment(bool includeLineCommnet);
};
} // namespace util
} // namespace pugcpp
#endif
