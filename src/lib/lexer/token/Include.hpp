#ifndef Include_hpp
#define Include_hpp

#include <memory>

#include "Token.hpp"

using namespace std;

namespace pugcpp
{
namespace lexer
{
namespace token
{
class Include : public Token
{
  private:
    string filter_;
    shared_ptr<Token> attrs_;

  public:
    Include(const string &value, int lineNumber);

    const string &getFilter() const;
    void setFilter(const string &filter);
    shared_ptr<Token> getAttrs();
    void setAttrs(shared_ptr<Token> attrs);
};
} // namespace token
} // namespace lexer
} // namespace pugcpp
#endif
