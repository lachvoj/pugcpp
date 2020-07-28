#ifndef Parser_hpp
#define Parser_hpp

#include <memory>
#include <regex>
#include <stack>
#include <string>
#include <vector>

#include "../exceptions/PugParserException.hpp"
#include "../expression/IExpressionHandler.hpp"
#include "../lexer/Lexer.hpp"
#include "../lexer/token/AttributeList.hpp"
#include "../lexer/token/Token.hpp"
#include "../template/ITemplateLoader.hpp"
#include "../util/CharacterParser.hpp"

#include "PathHelper.hpp"
#include "node/Attr.hpp"
#include "node/AttrsNode.hpp"
#include "node/BlockCommentNode.hpp"
#include "node/BlockNode.hpp"
#include "node/CaseConditionNode.hpp"
#include "node/CommentNode.hpp"
#include "node/DoctypeNode.hpp"
#include "node/ExpressionNode.hpp"
#include "node/MixinNode.hpp"
#include "node/Node.hpp"
#include "node/TextNode.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
using namespace node;
using namespace lexer;
using namespace tmpl;
using namespace expression;
using namespace exceptions;
using namespace util;
using namespace token;

class Parser
{
  private:
    Lexer lexer_;
    shared_ptr<ITemplateLoader> templateLoader_;
    shared_ptr<IExpressionHandler> expressionHandler_;
    shared_ptr<Parser> extending_;
    const string &fileName_;
    stack<shared_ptr<Parser>> contexts_;
    map<string, shared_ptr<MixinNode>> mixins_;
    int inMixin_ = 0;
    map<string, shared_ptr<BlockNode>> blocks_;
    int inBlock_ = 0;
    PathHelper pathHelper_;
    CharacterParser characterParser_;

  public:
    static const regex FILE_EXTENSION_PATTERN;

    Parser(
        const string &filename,
        shared_ptr<ITemplateLoader> templateLoader,
        shared_ptr<IExpressionHandler> expressionHandler);
    Parser(
        const string &src,
        const string &filename,
        shared_ptr<ITemplateLoader> templateLoader,
        shared_ptr<IExpressionHandler> expressionHandler);

    shared_ptr<Node> parse();
    void setBlocks(const map<string, shared_ptr<BlockNode>> &blocks);
    map<string, shared_ptr<BlockNode>> &getBlocks();
    void setContexts(const stack<shared_ptr<Parser>> &contexts);
    stack<shared_ptr<Parser>> &getContexts();
    void setMixins(const map<string, shared_ptr<MixinNode>> &mixins);

  private:
    void parseExpr(shared_ptr<Node> &ret);
    void parseBlockCode(shared_ptr<Node> &ret);
    void parseComment(shared_ptr<Node> &ret);
    void parseMixin(shared_ptr<Node> &ret);
    void parseCall(shared_ptr<Node> &ret);
    void parseCssClassOrId(shared_ptr<Node> &ret);
    void parseBlock(shared_ptr<Node> &ret);
    void parseMixinBlock(shared_ptr<Node> &ret);
    void parseInclude(shared_ptr<Node> &ret);
    void parseExtends(shared_ptr<Node> &ret);
    void parseInterpolation(shared_ptr<Node> &ret);
    void parseText(shared_ptr<Node> &ret);
    void parseEach(shared_ptr<Node> &ret);
    void parseWhile(shared_ptr<Node> &ret);
    void parseAssignment(shared_ptr<Node> &ret);
    void parseTag(shared_ptr<Node> &ret);
    void tag(shared_ptr<AttrsNode> &tagNode);
    void parseTextBlock(shared_ptr<Node> &ret);
    void parseConditional(shared_ptr<Node> &ret);
    void parseBlockExpansion(shared_ptr<Node> &ret);
    void parseCase(shared_ptr<Node> &ret);
    void parseWhen(shared_ptr<Node> &ret);
    void parseDefault(shared_ptr<Node> &ret);
    void parseCode(shared_ptr<Node> &ret);
    void parseDoctype(shared_ptr<Node> &ret);
    void parseFilter(shared_ptr<Node> &ret);
    void parseASTFilter(shared_ptr<Node> &ret);
    void parseYield(shared_ptr<Node> &ret);

    shared_ptr<Node> blockExpansion();
    void block(shared_ptr<BlockNode> &ret);
    shared_ptr<list<shared_ptr<CaseConditionNode>>> whenBlock();
    void parseInlineTagsInText(vector<shared_ptr<Node>> &ret, const string &str);
    shared_ptr<CaseConditionNode> parseCaseCondition();
    shared_ptr<list<Attr>> convertToNodeAttributes(AttributeList &attr);
    shared_ptr<Token> lookahead(int i);
    shared_ptr<Token> peek();
    shared_ptr<Token> advance();
    shared_ptr<Token> accept(/*clazz*/);
    shared_ptr<Token> expect(TokenType tokenType);
    shared_ptr<Parser> createParser(const string &templateName);
    string ensurePugExtension(const string &templateName);
    int line();
};
} // namespace parser
} // namespace pugcpp
#endif
