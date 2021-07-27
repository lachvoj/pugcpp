#ifndef Utils_hpp
#define Utils_hpp

#include <any>
#include <map>
#include <memory>
#include <regex>
#include <sstream>
#include <string>

#include "../expression/IExpressionHandler.hpp"
#include "../parser/node/ExpressionString.hpp"
#include "../util/CharacterParser.hpp"

using namespace std;

namespace pugcpp
{
// forward declarations
namespace model
{
class PugModel;
}

namespace compiler
{
using namespace util;
using namespace model;
using namespace expression;
using namespace parser::node;

class Utils
{
  private:
    static const regex interpolationPattern;

  public:
    Utils() = delete;
    static void prepareInterpolate(vector<any> &ret, const string &str, bool xmlEscape);
    static string interpolate(vector<any> &prepared, PugModel &model, shared_ptr<IExpressionHandler> expressionHandler);
    static string interpolate(
        const string &str,
        PugModel &model,
        bool escape,
        shared_ptr<IExpressionHandler> expressionHandler);
};
} // namespace compiler
} // namespace pugcpp

#endif
