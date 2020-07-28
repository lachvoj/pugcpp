#ifndef Options_hpp
#define Options_hpp

namespace pugcpp
{
namespace util
{
class Options
{
  private:
    int start_ = 0;
    int end_ = 0;
    bool includeLineComment_ = false;

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
